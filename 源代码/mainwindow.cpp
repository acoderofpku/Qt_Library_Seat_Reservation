#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,next_homepage(new homepage)
    ,sign_up_widget (new sign_up)
{
    ui->setupUi(this);
    log_in_hide();
    //ui->nextwidget = new sign_up;

}

MainWindow::~MainWindow()
{
    delete sign_up_widget;
    delete next_homepage;
    delete ui;
}

void MainWindow::log_in_hide()//隐藏登录框
{
    ui->BackwardButton->hide();
    ui->confirmButton->hide();
    ui->IDEdit->hide();
    ui->PasswordEdit->hide();
    ui->Passwordlabel->hide();
    ui->Accountlabel->hide();
}

void MainWindow::log_in_show()//显示登录框
{
    ui->BackwardButton->show();
    ui->confirmButton->show();
    ui->IDEdit->show();
    ui->PasswordEdit->show();
    ui->Passwordlabel->show();
    ui->Accountlabel->show();
}

void MainWindow::on_loginButton_clicked()
{
    ui->loginButton->hide();
    ui->signupButton->hide();
    log_in_show();
}

void MainWindow::on_signupButton_clicked()
{
    sign_up_widget = new sign_up;
    sign_up_widget->show();
}

void MainWindow::on_BackwardButton_clicked()
{
    ui->loginButton->show();
    ui->signupButton->show();
    ui->IDEdit->clear();
    ui->PasswordEdit->clear();
    log_in_hide();
}


void MainWindow::on_confirmButton_clicked()
{
    if(!sign_in_serach(ui->IDEdit->text(),ui->PasswordEdit->text()))
    {
        qDebug()<<"Login in error";
        QMessageBox::warning(this, "error","User name or password is in valid");
    }
    else//这是针对下一个页面的接口
    {
        username = ui->IDEdit->text();
        next_homepage->username = username;
        this->close();
        next_homepage->show();
        qDebug()<<"login successfully";
    }
}

