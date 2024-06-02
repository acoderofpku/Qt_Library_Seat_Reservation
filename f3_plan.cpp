#include "f3_plan.h"
#include "ui_f3_plan.h"
#include"f3_part1.h"
#include"f3_part2.h"
#include"f3_part3.h"
#include"f3_part4.h"
f3_plan::f3_plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f3_plan)
    ,next1(new f3_part1)
    ,next2(new f3_part2)
    ,next3(new f3_part3)
    ,next4(new f3_part4)
{
    ui->setupUi(this);
}

f3_plan::~f3_plan()
{
    delete ui;
}

void f3_plan::on_backButton_clicked()
{
    emit go_back3();
}


void f3_plan::on_f3_1Button_clicked()
{
    next1->show();
}


void f3_plan::on_f3_2Button_clicked()
{
    next2->show();
}


void f3_plan::on_f3_3Button_clicked()
{
    next3->show();
}


void f3_plan::on_f3_4Button_clicked()
{
    next4->show();
}

