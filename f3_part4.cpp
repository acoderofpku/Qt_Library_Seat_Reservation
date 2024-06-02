#include "f3_part4.h"
#include "ui_f3_part4.h"

f3_part4::f3_part4(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f3_part4)
{
    ui->setupUi(this);
}

f3_part4::~f3_part4()
{
    delete ui;
}
