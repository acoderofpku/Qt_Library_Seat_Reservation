#ifndef F3_PLAN_H
#define F3_PLAN_H

#include <QWidget>
#include"f3_part1.h"
#include"f3_part2.h"
#include"f3_part3.h"
#include"f3_part4.h"
namespace Ui {
class f3_plan;
}

class f3_plan : public QWidget
{
    Q_OBJECT

public:
    explicit f3_plan(QWidget *parent = nullptr);
    ~f3_plan();
signals:
    void go_back3();
private slots:
    void on_backButton_clicked();

    void on_f3_1Button_clicked();

    void on_f3_2Button_clicked();

    void on_f3_3Button_clicked();

    void on_f3_4Button_clicked();

private:
    Ui::f3_plan *ui;
    f3_part1 *next1;
    f3_part2 *next2;
    f3_part3 *next3;
    f3_part4 *next4;
};

#endif // F3_PLAN_H
