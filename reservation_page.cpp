#include "reservation_page.h"
#include "ui_reservation_page.h"
reservation_page::reservation_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::reservation_page)

{
    ui->setupUi(this);
}

reservation_page::~reservation_page()
{

    delete ui;
}


void reservation_page::on_backButton_clicked()
{
    emit goback();
}


void reservation_page::on_firstButton_clicked()
{
    emit first();
}



void reservation_page::on_secondButton_clicked()
{
    emit second();
}


void reservation_page::on_thirdButton_clicked()
{
    emit third();
}


void reservation_page::on_forthButton_clicked()
{
    emit forth();
}

