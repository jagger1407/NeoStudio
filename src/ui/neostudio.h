#ifndef NEOSTUDIO_H
#define NEOSTUDIO_H

#include "src/qt_includes.h"
#include "src/debug.h"
#include "aboutwindow.h"
// Parameter Tabs
#include "src/ui/generalframe.h"

namespace Ui {
class NeoStudio;
}
/**
 * Main Window User Interface
 */
class NeoStudio : public QMainWindow
{
    Q_OBJECT

public:
    /**Constructor. Creates the main Neo Studio window.*/
    explicit NeoStudio(QWidget* parent = nullptr);
    /**Destructor. Idk how to use this, it was automatically generated.*/
    ~NeoStudio() override;
private:
    QScopedPointer<Ui::NeoStudio> ui;
    GeneralFrame* generalWindow;
    QString file;
    PakControls* pak = nullptr;
    void InitFile();
private slots:
    void OpenFile();
    void SaveFile();
    void SaveFileAs();
    void CloseFile();
    void OpenAbout();
};

#endif // NEOSTUDIO_H
