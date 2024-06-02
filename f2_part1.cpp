#include "f2_part1.h"
#include "ui_f2_part1.h"

f2_part1::f2_part1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f2_part1)
{
    ui->setupUi(this);
}

f2_part1::~f2_part1()
{
    delete ui;
}
