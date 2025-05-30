#include "mainwindow.h"
#include "globals.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "mainmenuwindow.h"
#include "user.h"
#include "datasource.h"
#include <QDebug>
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool is_empty_login(string username, string password){
    return trim_string(username).empty() || trim_string(password).empty();
}

bool is_valid_login(user user,string username,string password){
    return(username == user.name &&
            password == user.password &&
            !is_empty_login(username,password) );
}


void MainWindow::on_btnAccept_clicked()
{
    user user = load_user_from_json();

    string username = ui->txtUserName->text().toStdString();
    string password = ui->txtPassword->text().toStdString();

    //login credetials validation
    if(is_valid_login(user,username,password)){

        //Menu window is created with program options
        MainMenuWindow *new_window = new MainMenuWindow();
        new_window->setAttribute(Qt::WA_DeleteOnClose); // Ensures the window is deleted when closed
        new_window->show();
        this->hide();
    }
    else{
        QMessageBox::warning(this,"Login Error","User Name and Password Incorrect!");
    }

}


void MainWindow::on_btnCancel_clicked()
{
    this->close();
}

