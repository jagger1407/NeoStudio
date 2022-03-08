#ifndef GENERALFRAME_H
#define GENERALFRAME_H

#include "src/qt_includes.h"
#include "src/debug.h"
#include "src/neo_info.h"
#include "src/pakcontrols.h"
#include "src/flagbyte.h"
#include "ui_generalframe.h"

namespace Ui
{
class GeneralFrame;
}

/**
 * The General Parameter Window.
 */
class GeneralFrame : public QFrame
{
    Q_OBJECT

public:
    /**Constructor. Creates PakControls object and initializes UI with .pak values.*/
    explicit GeneralFrame(PakControls* Pak, QWidget* parent = nullptr);
    /**Pointer used to access UI elements of this window.*/
    Ui_GeneralFrame* ui;
    /**QByteArray filled with the general parameter data.*/
    QByteArray paramData;
private:
    bool IsInitializing = false;
    unsigned char RushTech[4];
    unsigned char CounterMove[3];
    unsigned char FusionType[3];
    void InitializeUIElements();
private slots:
    void ChangeID(int ID);
    void ChangeAmount(int Amount);
    void ChangeIntAmount(int Amount);
    void ChangeDoubleAmount(double Amount);
    void ChangeFlagState(int State);
    void ChangeRushTech();
    void DisplayRushTech(Technique Type, QPushButton* Button = nullptr);
    void ChangeCounterTech();
    void DisplayCounterTech(Counter_Move Type, QPushButton* Button = nullptr);
    void ChangeFusionType();
    void DisplayFusionType(Fusion_Type Type, QPushButton* Button = nullptr);
    void ChangeZSearch(int Index);
    void ChangeStepInTech(int Index);
    void ChangeAuraColor(int Index);
};

#endif // GENERALFRAME_H
