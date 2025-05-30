#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainmenuwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAccept_clicked();

    void on_btnCancel_clicked();

private:
    Ui::MainWindow *ui;
    MainMenuWindow *mainMenuWindow;
};
#endif // MAINWINDOW_H
