#include "f3_part2.h"
#include "ui_f3_part2.h"

f3_part2::f3_part2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::f3_part2)
{
    ui->setupUi(this);
}

f3_part2::~f3_part2()
{
    delete ui;
}
