#include "homepage.h"
#include "ui_homepage.h"
#include"reservation_page.h"
#include"noticeboard.h"
#include <QDebug>
homepage::homepage(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::homepage)
    , next_page(new reservation_page)
    ,noticeboard1(new noticeboard)
    ,reservation(new my_reservation)
    ,f1plan(new f1_plan)
    ,f2plan(new f2_plan)
    ,f3plan(new f3_plan)
    ,f4plan(new f4_plan)
{
    ui->setupUi(this);
    if (centralWidget()!= nullptr)
    {
        qDebug()<<"ptr not error";
        home_page = centralWidget();
        home_page->setParent(0);//now it is saved
    }
    else
        qDebug()<<"ptr error";
    show_Home_Page();
    connect(reservation,&my_reservation::re_goback,this, &homepage::show_Home_Page);
    connect(noticeboard1,&noticeboard::notice_goback,this, &homepage::show_Home_Page);
    connect(next_page, &reservation_page::goback, this, &homepage::show_Home_Page);
    connect(next_page, &reservation_page::first, this, &homepage::show_f1_plan);
    connect(next_page, &reservation_page::second, this, &homepage::show_f2_plan);
    connect(next_page, &reservation_page::third, this, &homepage::show_f3_plan);
    connect(next_page, &reservation_page::forth, this, &homepage::show_f4_plan);
    connect(f1plan,&f1_plan::go_back,this,&homepage::show_reservation_page);
    connect(f2plan,&f2_plan::go_back2,this,&homepage::show_reservation_page);
    connect(f3plan,&f3_plan::go_back3,this,&homepage::show_reservation_page);
    connect(f4plan,&f4_plan::go_back4,this,&homepage::show_reservation_page);
}

homepage::~homepage()
{
    delete f1plan;
    delete f2plan;
    delete f3plan;
    delete f4plan;
    delete noticeboard1;
    delete next_page;
    delete reservation;
    delete ui;
}

void homepage::show_Home_Page()
{

    if(home_page)
    {
        next_page->username = username;
        this->takeCentralWidget();
        this->setCentralWidget(home_page);
    }
    else
        qDebug()<<"ptr error";
}

void homepage::show_reservation_page()
{
    if(next_page)
    {
        this->takeCentralWidget();
        this->setCentralWidget(next_page);
    }
    else
        qDebug()<<"ptr error";
}

void homepage::show_f1_plan()
{
    if(f1plan)
    {
        f1plan->username = username;
        this->takeCentralWidget();
        this->setCentralWidget(f1plan);
    }
    else
        qDebug()<<"ptr error";
}

void homepage::show_f2_plan()
{
    if(f2plan)
    {
        this->takeCentralWidget();
        this->setCentralWidget(f2plan);
    }
    else
        qDebug()<<"ptr error";
}
void homepage::show_f3_plan()
{
    if(f3plan)
    {
        this->takeCentralWidget();
        this->setCentralWidget(f3plan);
    }
    else
        qDebug()<<"ptr error";
}
void homepage::show_f4_plan()
{
    if(f4plan)
    {
        this->takeCentralWidget();
        this->setCentralWidget(f4plan);
    }
    else
        qDebug()<<"ptr error";
}
/*void homepage::show_first_floor()
{
    if(firstfloor)
    {
        qDebug()<<"call";
        this->takeCentralWidget();
        this->setCentralWidget(firstfloor);
        qDebug()<<"changed";
    }
    else
        qDebug()<<"ptr error";
}*/
void homepage::on_pushButton_clicked()
{
    this->takeCentralWidget();
    this->setCentralWidget(next_page);
}
//我要预约

void homepage::on_pushButton_2_clicked()
{
    if(reservation)
    {
        reservation->username = username;
        reservation->search_my_reservation();
        this->takeCentralWidget();
        this->setCentralWidget(reservation);
    }
    else
        qDebug()<<"ptr error";
}
//我的预约

void homepage::on_pushButton_3_clicked()
{
    if(noticeboard1)
    {
        this->takeCentralWidget();
        this->setCentralWidget(noticeboard1);
    }
    else
    {
        qDebug()<<"ptr error";
    }
}
//公告栏

