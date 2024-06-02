#include "f4_plan.h"
#include "ui_f4_plan.h"
#include"f4_part1.h"
#include"f4_part2.h"
#include"f4_part3.h"
f4_plan::f4_plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f4_plan)
    ,next1(new f4_part1)
    ,next2(new f4_part2)
    ,next3(new f4_part3)
{
    ui->setupUi(this);
}

f4_plan::~f4_plan()
{
    delete ui;
}

void f4_plan::on_backButton_clicked()
{
    emit go_back4();
}


void f4_plan::on_f4_1Button_clicked()
{
    next1->show();
}


void f4_plan::on_f4_2Button_clicked()
{
    next2->show();
}


void f4_plan::on_f443Button_clicked()
{
    next3->show();
}

