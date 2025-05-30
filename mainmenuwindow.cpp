#include "mainmenuwindow.h"
#include "dialogbookingadd.h"
#include "dialogbookingcancel.h"
#include "dialogbookinglistmonthly.h"
#include "dialogbookinglisttoday.h"
#include "dialogbookinglistweek.h"
#include "dialogbookingupdate.h"
#include "globals.h"
#include "ui_mainmenuwindow.h"
#include "dialogroomlist.h"
#include <QMessageBox>
#include <QDialog>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setWindowTitle("Booking System");
    setAttribute(Qt::WA_DeleteOnClose);

    // Set background image using stylesheet
    setStyleSheet(
           "QMainWindow {"
           "   background-image: url("+ MAIN_WINDOW_IMAGE_PATH +");"
           "   background-position: center;"
           "   background-repeat: no-repeat;"
           "   background-size: 50% 50%;"
           "}"
        );

}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_actionList_triggered()
{
    DialogRoomList *dialogRoomList = new DialogRoomList(this);
    dialogRoomList->setModal(true);
    dialogRoomList->show();
}



void MainMenuWindow::on_actionAdd_2_triggered()
{
    DialogBookingAdd *dialogBookingAdd = new DialogBookingAdd(this);
    dialogBookingAdd->setModal(true);
    dialogBookingAdd->show();
}


void MainMenuWindow::on_actionToday_triggered()
{
    DialogBookingListToday* dialogBookingListToday = new  DialogBookingListToday(this);
    dialogBookingListToday->setModal(true);
    dialogBookingListToday->show();

}


void MainMenuWindow::on_actionWeekly_triggered()
{
    DialogBookingListWeek* dialogBookingListWeekly = new  DialogBookingListWeek(this);
    dialogBookingListWeekly->setModal(true);
    dialogBookingListWeekly->show();
}


void MainMenuWindow::on_actionMonthly_triggered()
{
    DialogBookingListMonthly* dialogBookingListMonthly = new  DialogBookingListMonthly(this);
    dialogBookingListMonthly->setModal(true);
    dialogBookingListMonthly->show();
}


void MainMenuWindow::on_actionUpdate_triggered()
{
    DialogBookingUpdate* dialogBookingUpadte = new  DialogBookingUpdate(this);
    dialogBookingUpadte->setModal(true);
    dialogBookingUpadte->show();
}


void MainMenuWindow::on_actionCancel_triggered()
{
    DialogBookingCancel *dialogBookingListWeekly = new DialogBookingCancel(this);
    dialogBookingListWeekly->setModal(true);
    dialogBookingListWeekly->show();
}

