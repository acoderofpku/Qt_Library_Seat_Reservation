#include "f1_plan.h"
#include "ui_f1_plan.h"
#include"first_floor.h"
f1_plan::f1_plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f1_plan)
    ,next(new first_floor)
{
    ui->setupUi(this);

}

f1_plan::~f1_plan()
{
    delete ui;
}


void f1_plan::on_seats_Button_clicked()
{
    next->username = username;
    next->show();
}



void f1_plan::on_backButton_clicked()
{
    emit go_back();
}

