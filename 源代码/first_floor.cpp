#include "first_floor.h"
#include "ui_first_floor.h"
#include "database.h"
#include<QStackedWidget>
first_floor::first_floor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::first_floor)
{
    ui->setupUi(this);
    pushButtonList = {ui->pushButton,ui->pushButton_2,ui->pushButton_3
                      ,ui->pushButton_4,ui->pushButton_5,ui->pushButton_6
                      ,ui->pushButton_7,ui->pushButton_8};
    for (int i = 0; i < 8; ++i)
    {
        connect(pushButtonList[i],&QPushButton::clicked, this, [&,i]{
            choose_seat(i);
        });
    }
    for (int i = 0;i < 8; ++i)
        add_seat(pushButtonList[i]->text());
}

first_floor::~first_floor()
{
    delete seat;
    delete ui;
}

void first_floor::choose_seat(int i)
{
    seat = new seat_situation();
    seat->username = username;
    seat->seat_id = pushButtonList[i]->text();
    seat->show();
}



void first_floor::on_backButton_clicked()
{
    hide();
}

