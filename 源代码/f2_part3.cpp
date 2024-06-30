#include "f2_part3.h"
#include "ui_f2_part3.h"

f2_part3::f2_part3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f2_part3)
{
    ui->setupUi(this);
}

f2_part3::~f2_part3()
{
    delete ui;
}
