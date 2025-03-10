#include "skilllistframe.h"

SkillListFrame::SkillListFrame(PakControls* pak)
    : ui(new Ui::SkillListFrame), pak(pak)
{
    isInitializing = true;
    ui->setupUi(this);
    ResetUiMode();

    initPixmaps();

    // Reading Skill Lists from the .pak
    for(int i=0;i<PAK_SKILL_LIST_COUNT;i++) {
        QByteArray data = pak->GetParamData(SECTION_OFFSET_SKILL_LIST_DE + i);
        skillListSizes[i] = data.length();
        skillListText[i] = QString::fromUtf16((ushort*)(data.data()));
    }

    int curLang = ui->LanguageBox->currentIndex();
    isInitializing = false;
    ui->SkillListEdit->setText(skillListText[curLang]);
    ui->SkillListPreview->clear();
    SkillListTextChanged();
}

SkillListFrame::SkillListFrame(int sectionID, QByteArray* data) : ui(new Ui::SkillListFrame), dat(data)
{
    isInitializing = true;
    ui->setupUi(this);
    ResetUiMode();
    int language = sectionID - SECTION_OFFSET_SKILL_LIST_DE;
    if(language < 0 || language > 8) {
        Debug::Log("Language of imported .dat invalid.", Debug::ERROR);
        return;
    }
    ui->LanguageBox->setCurrentIndex(language);
    ui->LanguageBox->setEnabled(false);
    skillListText[language] = QString::fromUtf16((ushort*)(dat->data()));
    skillListSizes[language] = dat->length();
    lastLang = language;
    isInitializing = false;
    ui->SkillListEdit->setText(skillListText[language]);
    ui->SkillListPreview->clear();
    SkillListTextChanged();
}

SectionOffset SkillListFrame::GetCurrentSection()
{
    return (SectionOffset)(SECTION_OFFSET_SKILL_LIST_DE + lastLang);
}

void SkillListFrame::initPixmaps()
{
    // Input Icons
    for(int i=0;i<BUTTON_COUNT;i++) {
        QImage img = QImage(QString("./assets/SkillList/input_%1.png").arg(QString::number(i))).scaled(lineHeight, lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        buttonPixmaps[i] = QPixmap::fromImage(img);
    }
    // Header Icons
    for(int i=0;i<HEADER_COUNT;i++) {
        QImage img = QImage(QString("./assets/SkillList/header_%1.png").arg(QString::number(i))).scaled(lineHeight, lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        headerPixmaps[i] = QPixmap::fromImage(img);
    }
    // Text Icons
    for(int i=0;i<2;i++) {
        QImage transformImg = QImage(QString("./assets/SkillList/header_%1_input.png").arg(QString::number(i+7))).scaled(lineHeight * 2.25, lineHeight * 1.225, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        transformPixmaps[i] = QPixmap::fromImage(transformImg);

        QImage textImg = QImage(QString("./assets/SkillList/text_%1.png").arg(QString::number(i))).scaled(lineHeight * 0.625, lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        textBackgrounds[i] = QPixmap::fromImage(textImg);
    }
    starPixmap = QPixmap::fromImage(QImage("./assets/SkillList/star.png").scaled(lineHeight * 0.625,lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // Special Input Icons
    for(int i=0;i<4;i++) {
        QImage img = QImage(QString("./assets/SkillList/special_%1.png").arg(QString::number(i))).scaled(lineHeight, lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        specialPixmaps[i] = QPixmap::fromImage(img);
    }
    repeatingSquarePixmap = QPixmap::fromImage(QImage("./assets/SkillList/input_14.png").scaled(lineHeight * 2, lineHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QLabel * SkillListFrame::makeInputLabel(QPixmap* pixmap)
{
    QLabel* lbl = new QLabel();
    lbl->setMaximumHeight(lineHeight);
    lbl->setMaximumWidth(pixmap->width());
    lbl->setPixmap(*pixmap);
    lbl->setStyleSheet("background-color: rgb(1, 1, 71);");
    return lbl;
}

void SkillListFrame::addSkillListItem(SkillListItemType type, QChar cid, QString text)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(20, 2, 0, 0);
    layout->setSpacing(0);
    switch(type) {
        case SKILL_LIST_ITEM_HEADER: {
            int id = cid.digitValue();
            if(id < 0 || id > 8) {
                id = 0;
            }
            // Dragon Ball Icon
            QLabel* headerIcon = new QLabel();
            headerIcon->setPixmap(headerPixmaps[id]);
            headerIcon->setMaximumWidth(lineHeight);
            headerIcon->setMaximumHeight(lineHeight);
            headerIcon->setStyleSheet("background-color: rgb(1, 1, 71);");
            layout->addWidget(headerIcon);

            QString stylesheet = QString("background-color: rgb(76, 36, 59); border-bottom: %1px solid rgb(237, 237, 252);").arg(lineHeight * 0.08);
            // Text Label
            QLabel* textLbl = new QLabel();
            textLbl->setText(text);
            QFont font = textLbl->font();
            font.setFamily("Tahoma");
            font.setBold(true);
            font.setPointSize(lineHeight * 0.4);
            textLbl->setFont(font);
            textLbl->setStyleSheet(stylesheet);
            textLbl->setMaximumHeight(lineHeight * 0.85);
            layout->addWidget(textLbl);

            // Transformation Icon
            if(id == 7 || id == 8) {
                QLabel* transformIcon = new QLabel();
                transformIcon->setPixmap(transformPixmaps[id - 7]);
                transformIcon->setStyleSheet(stylesheet);
                transformIcon->setMaximumHeight(lineHeight * 0.85);
                transformIcon->setMaximumWidth(lineHeight * 2.25);
                layout->addWidget(transformIcon);
            }
        } break;
        case SKILL_LIST_ITEM_TEXT: {
            int id = cid.digitValue();
            QString stylesheets[4] = {
                "background-color: rgb(100, 100, 30); color: rgb(250, 250, 1); margin-bottom: 1px;",
                "background-color: rgb(54, 54, 108); color: rgb(35, 200, 200); margin-bottom: 1px;",
                "background-color: rgb(54, 54, 108); color: rgb(234, 87, 87); margin-bottom: 1px;",
                "background-color: rgb(54, 54, 108); color: rgb(234, 234, 234); margin-bottom: 1px;"
            };
            if(id == 0) {
                // Star front sprite
                // (Needs to combine text_0.png and star.png)
                QGraphicsView* frontSprite = new QGraphicsView();
                frontSprite->setStyleSheet("background-color: rgb(1, 1, 71);");
                frontSprite->setMaximumHeight(lineHeight);
                frontSprite->setMaximumWidth(lineHeight * 0.625);
                frontSprite->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
                frontSprite->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
                QGraphicsScene* s = new QGraphicsScene();
                s->addPixmap(textBackgrounds[0]);
                s->addPixmap(starPixmap);
                frontSprite->setScene(s);
                layout->addWidget(frontSprite);
                // Text
                QLabel* textLbl = new QLabel();
                textLbl->setText(text);
                QFont font = textLbl->font();
                font.setBold(true);
                font.setFamily("Tahoma");
                font.setPointSize(lineHeight * 0.4);
                textLbl->setFont(font);
                textLbl->setStyleSheet(stylesheets[0]);
                textLbl->setMaximumHeight(lineHeight * 0.75);
                layout->addWidget(textLbl);
            }
            else if(id == 1 || id == 2 || id == 3) {
                // Left Padding
                QLabel* padding = new QLabel();
                padding->setMaximumHeight(lineHeight);
                padding->setMaximumWidth(lineHeight * 0.75);
                padding->setText("  ");
                padding->setStyleSheet("background-color: rgb(1, 1, 71);");
                QFont font = padding->font();
                font.setBold(true);
                font.setPointSize(lineHeight * 0.4);
                padding->setFont(font);
                layout->addWidget(padding);
                // Front sprite
                QLabel* frontLbl = new QLabel();
                frontLbl->setStyleSheet("background-color: rgb(1, 1, 71);");
                frontLbl->setMaximumHeight(lineHeight);
                frontLbl->setMaximumWidth(lineHeight * 0.625);
                frontLbl->setPixmap(textBackgrounds[1]);
                layout->addWidget(frontLbl);
                // Text
                QLabel* textLbl = new QLabel();
                textLbl->setText(text);
                font = textLbl->font();
                font.setFamily("Tahoma");
                font.setBold(true);
                font.setPointSize(lineHeight * 0.4);
                textLbl->setFont(font);
                textLbl->setMaximumHeight(lineHeight * 0.75);
                textLbl->setStyleSheet(stylesheets[id]);
                layout->addWidget(textLbl);
            }
            else {
                // In-game, there will just be an empty line break
                QLabel* lbl = new QLabel();
                lbl->setMaximumHeight(lineHeight);
                lbl->setStyleSheet("background-color: rgb(1, 1, 71);");
                layout->addWidget(lbl);
            }
        } break;
        case SKILL_LIST_ITEM_INPUT: {
            // Left Padding
            QLabel* leftPad = new QLabel();
            leftPad->setMaximumHeight(lineHeight);
            leftPad->setMaximumWidth(lineHeight * 1.5);
            leftPad->setText("     ");
            leftPad->setStyleSheet("background-color: rgb(1, 1, 71);");
            QFont font = leftPad->font();
            font.setBold(true);
            font.setPointSize(lineHeight * 0.4);
            leftPad->setFont(font);
            layout->addWidget(leftPad);
            int curChar = 0;
            // Input
            bool repeating = false;
            QPixmap* pm = NULL;
            while(curChar < text.length()) {
                ushort curCode = text.at(curChar).unicode();

                if(repeating) {
                    layout->addWidget(makeInputLabel(pm));
                    curChar++;
                    continue;
                }

                // Check if the input is L1, L2, L3, R1, R2 or R3.
                if(curCode == l_code || curCode == r_code) {
                    bool isRcode = curCode == r_code;
                    if(++curChar >= text.length()) {
                        continue;
                    }
                    for(int i=0;i<3;i++) {
                        if(text.at(curChar).unicode() == buttonCodes[i]) {
                            pm = buttonPixmaps + (isRcode * 3 + i);
                            layout->addWidget(makeInputLabel(pm));
                            break;
                        }
                    }
                    curChar++;
                    continue;
                }
                bool found = false;
                // Check if the input is one of the buttons/directions
                for(int i=3;i<BUTTON_COUNT;i++) {
                    if(curCode == buttonCodes[i]) {
                        if(i == (BUTTON_SQUARE-3) && curChar + 1 < text.length() && text.at(curChar+1).unicode() == repeatingCode) {
                            pm = &repeatingSquarePixmap;
                            curChar++;
                        }
                        else {
                            pm = buttonPixmaps + 3 + i;
                        }
                        layout->addWidget(makeInputLabel(pm));
                        found = true;
                        break;
                    }
                }
                if(found) {
                    curChar++;
                    continue;
                }
                // Check if the input is a special char ( ) + /
                for(int i=0;i<4;i++) {
                    if(curCode == inputSpecials[i]) {
                        pm = specialPixmaps + i;
                        layout->addWidget(makeInputLabel(pm));
                        found = true;
                        break;
                    }
                }
                if(found) {
                    curChar++;
                    continue;
                }
                // Check if the input is a repeating wildcard
                if(curCode == repeatingCode) {
                    if(curChar == 0) {
                        pm = specialPixmaps + 2;
                        repeating = true;
                        continue;
                    }
                    repeating = true;
                    continue;
                }

                curChar++;
            }
            QLabel* rightPad = new QLabel();
            rightPad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            rightPad->setMaximumHeight(lineHeight);
            rightPad->setStyleSheet("background-color: rgb(1, 1, 71);");
            layout->addWidget(rightPad);
        } break;
        default: {
            QLabel* textLbl = new QLabel();
            textLbl->setText(QString("%1%2%3").arg(QChar(type), cid, text));
            textLbl->setStyleSheet("background-color: rgb(1, 1, 71);");
            QFont font = textLbl->font();
            font.setBold(true);
            font.setFamily("Tahoma");
            font.setPointSize(lineHeight * 0.4);
            textLbl->setFont(font);
            textLbl->setMaximumHeight(68);
            layout->addWidget(textLbl);
        } break;

    }
    widget->setLayout(layout);
    QListWidgetItem* item = new QListWidgetItem();
    ui->SkillListPreview->addItem(item);
    ui->SkillListPreview->setItemWidget(item, widget);
    item->setSizeHint(widget->sizeHint());
}

void SkillListFrame::SkillListTextChanged()
{
    if(isInitializing) return;

    // store new skill list text
    int curLang = ui->LanguageBox->currentIndex();

    ui->SkillListPreview->clear();
    // Add top spacing
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(20,20));
    ui->SkillListPreview->addItem(item);

    QStringList lines = ui->SkillListEdit->toPlainText().split("\n");

    for(int l=0;l<lines.length();l++) {
        QString line = lines[l];
        if(line.length() <= 0) {
            continue;
        }

        if(identifiers.indexOf(line.at(0)) == SKILL_LIST_ITEM_UNKNOWN_PREFIX) {
            Debug::Log(QString("Line %1 contains an unknown prefix \"%2\".").arg(l).arg(line.left(4)), Debug::WARNING);
            line = line.mid(4);
        }

        SkillListItemType lineType = (SkillListItemType)identifiers.indexOf(line.at(0));

        if(lineType == SKILL_LIST_ITEM_TERMINATOR) {
            break;
        }

        else if(lineType == SKILL_LIST_ITEM_INPUT) {
            addSkillListItem(lineType, ' ', line.mid(1));
            continue;
        }
        if(line.length() == 1 || line.length() == 2) {
            addSkillListItem(lineType, ' ', "");
        }
        else {
            addSkillListItem(lineType, line.at(1), line.mid(2));
        }
    }
}

void SkillListFrame::ListItemHeightChanged(int newHeight)
{
    lineHeight = newHeight;
    initPixmaps();
    SkillListTextChanged();
}


void SkillListFrame::ChangeLanguage(int langIdx)
{
    if(isInitializing) {
        return;
    }

    QString curText = ui->SkillListEdit->toPlainText();

    if(curText.length() > skillListSizes[lastLang]) {
        Debug::Log("contents of SkillListEdit bigger than reserved space. Truncating.", Debug::WARNING);
        curText.truncate(skillListSizes[lastLang]);
    }
    skillListText[lastLang] = curText;

    ui->SkillListEdit->setText(skillListText[langIdx]);
    lastLang = langIdx;
}

void SkillListFrame::UpdatePak()
{
    QString curText = ui->SkillListEdit->toPlainText();
    skillListText[lastLang] = curText;

    for(int i=SECTION_OFFSET_SKILL_LIST_DE;i<SECTION_OFFSET_SKILL_LIST_DE + PAK_SKILL_LIST_COUNT;i++) {
        QString text = skillListText[i-SECTION_OFFSET_SKILL_LIST_DE];
        QByteArray ba = QByteArray((char*)(text.utf16()), text.length()*2);
        pak->UpdateParamData(i, &ba);
    }
}

QByteArray * SkillListFrame::GetCurrentSkillList()
{
    QString curText = skillListText[ui->LanguageBox->currentIndex()];
    QByteArray* out = new QByteArray((char*)curText.utf16(), curText.length()*2);
    if(out->length() > skillListSizes[ui->LanguageBox->currentIndex()]) {
        Debug::Log("Current Skill List is bigger than it was before.", Debug::ERROR);
    }
    return out;
}

void SkillListFrame::ImportSkillList(SectionOffset type, QByteArray dat)
{
    if(type < SECTION_OFFSET_SKILL_LIST_DE || type > SECTION_OFFSET_SKILL_LIST_UK) {
        return;
    }
    int language = type - SECTION_OFFSET_SKILL_LIST_DE;
    if(dat.length() > skillListSizes[language])
    {
        Debug::Log("Imported Skill List is greater than allocated space in the pak.\n" \
            "Import Size: " + QString::number(dat.length()) + " Bytes\t- Original Size: " + QString::number(skillListSizes[language]) + " Bytes", Debug::ERROR);
    }
    skillListText[language] = QString::fromUtf16((ushort*)(dat.data()));
    if(ui->LanguageBox->currentIndex() == language) {
        ui->SkillListEdit->setText(skillListText[language]);
    }
}

void SkillListFrame::ButtonPressed()
{
    int n = 2;
    QString text = ((QPushButton*)sender())->text();
    ui->SkillListEdit->insertPlainText(text);
}


void SkillListFrame::ResetUiMode()
{
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    ui->SkillListPreview->setStyleSheet("QListWidget { background-color: rgb(1, 1, 71); border: 7px solid white; border-radius: 20px; }");
}
