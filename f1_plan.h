#ifndef F1_PLAN_H
#define F1_PLAN_H

#include <QWidget>
#include "first_floor.h"
namespace Ui {
class f1_plan;
}

class f1_plan : public QWidget
{
    Q_OBJECT

public:
    explicit f1_plan(QWidget *parent = nullptr);
    ~f1_plan();
    QString username;
signals:
    void go_back();
private slots:

    void on_seats_Button_clicked();

    void on_backButton_clicked();

private:
    Ui::f1_plan *ui;
    first_floor *next;
};

#endif // F1_PLAN_H
