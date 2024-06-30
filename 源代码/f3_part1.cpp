#include "f3_part1.h"
#include "ui_f3_part1.h"

f3_part1::f3_part1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f3_part1)
{
    ui->setupUi(this);
}

f3_part1::~f3_part1()
{
    delete ui;
}
