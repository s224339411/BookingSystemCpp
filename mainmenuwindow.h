#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMessageBox>
#include <QCloseEvent>
#include <QMainWindow>

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();


private slots:
    void on_actionList_triggered();

    void on_actionAdd_2_triggered();

    void on_actionToday_triggered();

    void on_actionWeekly_triggered();

    void on_actionMonthly_triggered();

    void on_actionUpdate_triggered();

    void on_actionCancel_triggered();

private:
    Ui::MainMenuWindow *ui;
};



#endif // MAINMENUWINDOW_H
