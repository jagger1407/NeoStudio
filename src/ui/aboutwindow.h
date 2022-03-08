#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include "src/qt_includes.h"

namespace Ui
{
    class AboutWindow;
}
class AboutWindow : public QDialog
{
    Q_OBJECT
public:
    explicit AboutWindow(QWidget* parent = nullptr);
    ~AboutWindow() override;
private:
    QScopedPointer<Ui::AboutWindow> ui;
};

#endif // ABOUTWINDOW_H
