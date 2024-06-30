#include "sign_up.h"
#include "ui_sign_up.h"
#include "database.h"
sign_up::sign_up(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sign_up)
{
    ui->setupUi(this);
}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::on_SureButton_clicked()
{
    int errortype = sign_up_data_upload(ui->NewIDEdit->text(),ui->PasswordEdit_1->text(), ui->PasswordEdit_2->text());
    switch (errortype)
    {
    case 0:
        QMessageBox::warning(this,"sign up","Sign up successfully !");
        break;
    case 1:
        qDebug()<<"insert into error";
        QMessageBox::warning(this,"sign up","Insert into error !");
        break;
    case 2:
        QMessageBox::warning(this,"sign up","The two passwords you typed do not match");
        ui->PasswordEdit_1->clear();
        ui->PasswordEdit_2->clear();
        break;
    case 3:
        QMessageBox::warning(this,"sign up","User ID cannot be empty");
        break;
    case 4:
        QMessageBox::warning(this,"sign up","Password should be at least 7 characters and at most 14 characters");
        break;
    case 5:
        QMessageBox::warning(this,"sign up","The user ID alreday exists");
        break;
    default:
        break;
    }
}


void sign_up::on_clearButton_clicked()
{
    ui->NewIDEdit->clear();
    ui->PasswordEdit_1->clear();
    ui->PasswordEdit_2->clear();
}

