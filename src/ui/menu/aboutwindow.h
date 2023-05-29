#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include "src/external/qt_includes.h"
#include "ui_aboutwindow.h"
#include "src/options.h"

namespace Ui
{
class AboutWindow;
}

/**
 * @todo write docs
 */
class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    AboutWindow(Options* options);
private:
    QScopedPointer<Ui::AboutWindow> ui;
};

#endif // ABOUTWINDOW_H
