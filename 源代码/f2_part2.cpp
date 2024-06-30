#include "f2_part2.h"
#include "ui_f2_part2.h"

f2_part2::f2_part2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f2_part2)
{
    ui->setupUi(this);
}

f2_part2::~f2_part2()
{
    delete ui;
}
