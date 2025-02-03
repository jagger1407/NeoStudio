#ifndef CHARPARAMFRAME_H
#define CHARPARAMFRAME_H

#include "ui_charparamframe.h"

#include "src/external/qt_includes.h"
#include "src/external/fileparse.h"
#include "src/external/debug.h"
// Parameter Tabs
#include "src/ui/paramSections/generalframe.h"
#include "src/ui/paramSections/meleeframe.h"
#include "src/ui/paramSections/kiframe.h"
#include "src/ui/paramSections/movementframe.h"

namespace Ui
{
class CharParamFrame;
}

/**
 * @todo write docs
 */
class CharParamFrame : public QFrame
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    CharParamFrame(PakControls* pak);
    CharParamFrame(ParameterType type, QByteArray* dat);
    void CloseFile();
    void UpdatePak();
    ParameterType GetCurrentParameterType();
    QByteArray* GetCurrentParameterData();
    void ImportParameterData(ParameterType type, QByteArray dat);
    void ResetUiMode();
private:
    Ui_CharParamFrame* ui;

    /**The UI for the General Parameter editing tab.*/
    GeneralFrame* generalWindow = NULL;
    /**The UI for the Melee Parameter editing tab.*/
    MeleeFrame* meleeWindow = NULL;
    /**The UI for the Ki Blast Parameter editing tab.*/
    KiFrame* kiWindow = NULL;
    /**The UI for the Movement Parameter editing tab.*/
    MovementFrame* moveWindow = NULL;

    PakControls* pak = NULL;
    /**If .dat file was opened, this shows which parameter type the file is.*/
    ParameterType datType = PARAM_TYPE_INVALID;
    QByteArray* dat = NULL;


private slots:
    void SelectTab(int tabId);
};

#endif // CHARPARAMFRAME_H
