#include "f4_part1.h"
#include "ui_f4_part1.h"

f4_part1::f4_part1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f4_part1)
{
    ui->setupUi(this);
}

f4_part1::~f4_part1()
{
    delete ui;
}
