#include "f4_part3.h"
#include "ui_f4_part3.h"

f4_part3::f4_part3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f4_part3)
{
    ui->setupUi(this);
}

f4_part3::~f4_part3()
{
    delete ui;
}
