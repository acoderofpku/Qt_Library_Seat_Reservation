#include "f4_part2.h"
#include "ui_f4_part2.h"

f4_part2::f4_part2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f4_part2)
{
    ui->setupUi(this);
}

f4_part2::~f4_part2()
{
    delete ui;
}
