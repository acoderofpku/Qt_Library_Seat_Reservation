#ifndef F2_PLAN_H
#define F2_PLAN_H

#include <QWidget>
#include"f2_part1.h"
#include"f2_part2.h"
#include"f2_part3.h"
#include"f2_part4.h"

namespace Ui {
class f2_plan;
}

class f2_plan : public QWidget
{
    Q_OBJECT

public:
    explicit f2_plan(QWidget *parent = nullptr);
    ~f2_plan();
signals:
    void go_back2();
private slots:
    void on_backButton_clicked();

    void on_f2_1Button_clicked();

    void on_f2_2Button_clicked();

    void on_f2_4Button_clicked();

    void on_f2_3Button_clicked();

private:
    Ui::f2_plan *ui;
    f2_part1 *next1;
    f2_part2 *next2;
    f2_part3 *next3;
    f2_part4 *next4;

};
#endif // F2_PLAN_H
