#include "f2_plan.h"
#include "ui_f2_plan.h"
#include"f2_part1.h"
#include"f2_part2.h"
#include"f2_part3.h"
#include"f2_part4.h"
f2_plan::f2_plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f2_plan)
    ,next1(new f2_part1)
,next2(new f2_part2)
,next3(new f2_part3)
,next4(new f2_part4)
{
    ui->setupUi(this);
}

f2_plan::~f2_plan()
{
    delete ui;
}

void f2_plan::on_backButton_clicked()
{
    emit go_back2();
}


void f2_plan::on_f2_1Button_clicked()
{
    next1->show();
}


void f2_plan::on_f2_2Button_clicked()
{
    next2->show();
}




void f2_plan::on_f2_3Button_clicked()
{
    next3->show();
}


void f2_plan::on_f2_4Button_clicked()
{
    next4->show();
}

