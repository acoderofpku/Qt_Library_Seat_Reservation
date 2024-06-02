#include "f2_part4.h"
#include "ui_f2_part4.h"

f2_part4::f2_part4(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f2_part4)
{
    ui->setupUi(this);
}

f2_part4::~f2_part4()
{
    delete ui;
}
