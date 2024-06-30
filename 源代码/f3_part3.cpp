#include "f3_part3.h"
#include "ui_f3_part3.h"

f3_part3::f3_part3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f3_part3)
{
    ui->setupUi(this);
}

f3_part3::~f3_part3()
{
    delete ui;
}
