#include "charparamframe.h"


CharParamFrame::CharParamFrame(PakControls* pak)
    : ui(new Ui_CharParamFrame), pak(pak)
{
    ui->setupUi(this);

    if(pak != NULL && pak->HasFailed()) {
        Debug::Log("Pak failed to load, CharParamFrame disconnected from pak.", Debug::ERROR);
        return;
    }

    generalWindow = new GeneralFrame(pak->GetParamData(SECTION_OFFSET_GENERAL), this);
    ui->GeneralScrollArea->setWidget(generalWindow);
    ui->ParameterTabs->setCurrentIndex(PARAM_TYPE_GENERAL);
}

CharParamFrame::CharParamFrame(ParameterType type, QByteArray* dat)
    : ui(new Ui::CharParamFrame), datType(type), dat(dat)
{
    ui->setupUi(this);

    if(dat == NULL || dat->data() == NULL) {
        Debug::Log("NULL pointer passed to CharParamFrame, editor is disconnected.", Debug::ERROR);
        return;
    }

    for(int i=0;i<PARAM_TYPE_NEXT;i++) {
        if(i != type) ui->ParameterTabs->setTabEnabled(i, false);
    }

    switch(type) {
        case PARAM_TYPE_GENERAL:
            generalWindow = new GeneralFrame(*dat, this);
            ui->GeneralScrollArea->setWidget(generalWindow);
            break;
        case PARAM_TYPE_MELEE:
            meleeWindow = new MeleeFrame(*dat, this);
            ui->MeleeScrollArea->setWidget(meleeWindow);
            break;
        case PARAM_TYPE_KI_BLAST:
            kiWindow = new KiFrame(*dat, this);
            ui->KiBlastScrollArea->setWidget(kiWindow);
            break;
        case PARAM_TYPE_MOVEMENT:
            moveWindow = new MovementFrame(*dat, this);
            ui->MovementScrollArea->setWidget(moveWindow);
            break;
        default:
            Debug::Log("Parameter Type does not have a dedicated tab yet.", Debug::ERROR);
            return;
    }
    ui->ParameterTabs->setCurrentIndex(type);
}

void CharParamFrame::SelectTab(int tabId)
{
    // This means the tab was selected by the code, not by the user.
    if(datType != PARAM_TYPE_INVALID) return;

    if(pak == NULL) {
        Debug::Log("SelectTab - pak == NULL.", Debug::ERROR);
        return;
    }

    switch(tabId) {
        case PARAM_TYPE_GENERAL:
            if(generalWindow == NULL) {
                generalWindow = new GeneralFrame(pak->GetParamData(SECTION_OFFSET_GENERAL), this);
                ui->GeneralScrollArea->setWidget(generalWindow);
            }
            break;
        case PARAM_TYPE_MELEE:
            if(meleeWindow == NULL) {
                meleeWindow = new MeleeFrame(pak->GetParamData(SECTION_OFFSET_MELEE), this);
                ui->MeleeScrollArea->setWidget(meleeWindow);
            }
            break;
        case PARAM_TYPE_KI_BLAST:
            if(kiWindow == NULL) {
                kiWindow = new KiFrame(pak->GetParamData(SECTION_OFFSET_KI_BLAST), this);
                ui->KiBlastScrollArea->setWidget(kiWindow);
            }
            break;
        case PARAM_TYPE_MOVEMENT:
            if(moveWindow == NULL) {
                moveWindow = new MovementFrame(pak->GetParamData(SECTION_OFFSET_MOVEMENT), this);
                ui->MovementScrollArea->setWidget(moveWindow);
            }
            break;
        default:
            Debug::Log(QString("SelectTab(%d) is an invalid tab. Selection aborted.").arg(tabId), Debug::WARNING);
            return;
            break;
    }
    ui->ParameterTabs->setCurrentIndex(tabId);
}

void CharParamFrame::CloseFile()
{
    for(int i=0;i<PARAM_TYPE_NEXT;i++) {
        ui->ParameterTabs->setTabEnabled(i, true);
    }

    if(generalWindow != NULL) {
        generalWindow->close();
        delete generalWindow;
        generalWindow = NULL;
    }
    if(meleeWindow != NULL) {
        meleeWindow->close();
        delete meleeWindow;
        meleeWindow = NULL;
    }
    if(kiWindow != NULL) {
        kiWindow->close();
        delete kiWindow;
        kiWindow = NULL;
    }
    if(moveWindow != NULL) {
        moveWindow->close();
        delete moveWindow;
        moveWindow = NULL;
    }
}

void CharParamFrame::UpdatePak()
{
    if(ui->GeneralTab->isEnabled())
        pak->UpdateParamData(SECTION_OFFSET_GENERAL, generalWindow->gp->GetParameterData());
    if(ui->MeleeTab->isEnabled())
        pak->UpdateParamData(SECTION_OFFSET_MELEE, meleeWindow->mp->GetParameterData());
    if(ui->KiBlastTab->isEnabled())
        pak->UpdateParamData(SECTION_OFFSET_KI_BLAST, kiWindow->kp->GetParameterData());
    if(ui->MovementTab->isEnabled())
        pak->UpdateParamData(SECTION_OFFSET_MOVEMENT, moveWindow->mp->GetParameterData());
}

ParameterType CharParamFrame::GetCurrentParameterType()
{
    return (ParameterType)ui->ParameterTabs->currentIndex();
}
void CharParamFrame::ImportParameterData(ParameterType type, QByteArray dat)
{
    switch(type) {
        case PARAM_TYPE_GENERAL:
            return generalWindow->gp->SetParameterData(dat);
        case PARAM_TYPE_MELEE:
            return meleeWindow->mp->SetParameterData(dat);
        case PARAM_TYPE_KI_BLAST:
            return kiWindow->kp->SetParameterData(dat);
        case PARAM_TYPE_MOVEMENT:
            return moveWindow->mp->SetParameterData(dat);
        default:
            Debug::Log("ImportParameterData - Invalid Parameter Section.", Debug::ERROR);
    }
}


QByteArray * CharParamFrame::GetCurrentParameterData()
{
    ParameterType curType = (ParameterType)ui->ParameterTabs->currentIndex();
    switch(curType) {
        case PARAM_TYPE_GENERAL:
            return generalWindow->gp->GetParameterData();
        case PARAM_TYPE_MELEE:
            return meleeWindow->mp->GetParameterData();
        case PARAM_TYPE_KI_BLAST:
            return kiWindow->kp->GetParameterData();
        case PARAM_TYPE_MOVEMENT:
            return moveWindow->mp->GetParameterData();
        default:
            Debug::Log("GetSelectedParameterData - Invalid Parameter Section, returning NULL.", Debug::ERROR);
            return NULL;
    }
}


void CharParamFrame::ResetUiMode()
{
    this->setStyleSheet(FileParse::ReadWholeFile("./assets/ui/" + g_Options.uiMode + ".qss"));

    if(generalWindow != NULL)
        generalWindow->ResetUiMode();
    if(meleeWindow != NULL)
        meleeWindow->ResetUiMode();
    if(kiWindow != NULL)
        kiWindow->ResetUiMode();
    if(moveWindow != NULL)
        moveWindow->ResetUiMode();
}
