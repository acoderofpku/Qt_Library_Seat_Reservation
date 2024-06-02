#ifndef F4_PLAN_H
#define F4_PLAN_H

#include <QWidget>
#include"f4_part1.h"
#include"f4_part2.h"
#include"f4_part3.h"
namespace Ui {
class f4_plan;
}

class f4_plan : public QWidget
{
    Q_OBJECT

public:
    explicit f4_plan(QWidget *parent = nullptr);
    ~f4_plan();
signals:
    void go_back4();
private slots:
    void on_backButton_clicked();

    void on_f4_1Button_clicked();

    void on_f4_2Button_clicked();

    void on_f443Button_clicked();

private:
    Ui::f4_plan *ui;
    f4_part1 *next1;
    f4_part2 *next2;
    f4_part3 *next3;
};

#endif // F4_PLAN_H
