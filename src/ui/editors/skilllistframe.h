#ifndef SKILLLISTFRAME_H
#define SKILLLISTFRAME_H

#include "src/external/qt_includes.h"
#include "src/external/fileparse.h"
#include "src/external/debug.h"

#include "ui_skilllistframe.h"

#include "src/pak_filesystem/pakcontrols.h"
#include "src/neo_info.h"

namespace Ui
{
class SkillListFrame;
}

/**
 * @todo write docs
 */
class SkillListFrame : public QFrame
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    SkillListFrame(PakControls* pak);
    SkillListFrame(int sectionID, QByteArray* data);

    void UpdatePak();
    QByteArray* GetCurrentSkillList();
    SectionOffset GetCurrentSection();
    void ImportSkillList(SectionOffset type, QByteArray dat);

    void ResetUiMode();
private:
    QScopedPointer<Ui::SkillListFrame> ui;

    bool isInitializing;

    QString skillListText[PAK_SKILL_LIST_COUNT];
    int skillListSizes[PAK_SKILL_LIST_COUNT];

    ushort inputSpecials[4] = {
        0xFF08, // (
        0xFF09, // )
        0xFF0B, // +
        0xFF0F  // /
    };
    QPixmap specialPixmaps[4];

    typedef enum {
        BUTTON_L1,
        BUTTON_L2,
        BUTTON_L3,
        BUTTON_R1,
        BUTTON_R2,
        BUTTON_R3,
        BUTTON_LEFT,
        BUTTON_UP,
        BUTTON_RIGHT,
        BUTTON_DOWN,
        BUTTON_SQUARE,
        BUTTON_TRIANGLE,
        BUTTON_CIRCLE,
        BUTTON_CROSS,

        BUTTON_COUNT
    } ButtonsPS;

    ushort l_code = 0xFF2C;
    ushort r_code = 0xFF32;

    ushort buttonCodes[BUTTON_COUNT] = {
        0xFF11,
        0xFF12,
        0xFF13,
        0x2190,
        0x2191,
        0x2192,
        0x2193,
        0x25A1,
        0x25B3,
        0x25CB,
        0x00D7
    };
    ushort repeatingCode = 0xFF0A;

    QPixmap buttonPixmaps[BUTTON_COUNT];

    #define HEADER_COUNT 9
    QPixmap headerPixmaps[HEADER_COUNT];
    QPixmap transformPixmaps[2];
    QPixmap textBackgrounds[2];
    QPixmap starPixmap;
    QPixmap repeatingSquarePixmap;

    int lineHeight = 60;

    PakControls* pak = NULL;
    QByteArray* dat = NULL;

    typedef enum {
        SKILL_LIST_ITEM_INVALID = -1,
        SKILL_LIST_ITEM_HEADER,
        SKILL_LIST_ITEM_TEXT,
        SKILL_LIST_ITEM_INPUT,
        SKILL_LIST_ITEM_UNKNOWN_PREFIX,
        SKILL_LIST_ITEM_TERMINATOR,

        SKILL_LIST_ITEM_TYPE_COUNT
    } SkillListItemType;
    QString identifiers = "$%#&@";

    void initPixmaps();

    void addSkillListItem(SkillListItemType type, QChar cid, QString text);

    QLabel* makeInputLabel(QPixmap* pixmap);

    int lastLang = 6;
private slots:
    void ChangeLanguage(int langIdx);
    void SkillListTextChanged();
    void ListItemHeightChanged(int newHeight);
    void ButtonPressed();
};

#endif // SKILLLISTFRAME_H
