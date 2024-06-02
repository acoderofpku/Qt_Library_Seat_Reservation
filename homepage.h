#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include "reservation_page.h"
#include "first_floor.h"
#include"noticeboard.h"
#include "my_reservation.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class homepage;
}
QT_END_NAMESPACE

class homepage : public QMainWindow
{
    Q_OBJECT
//homepage管理下属两个页面，floor和reservation，点击按钮传出信号，由homepage执行操作
public:
    homepage(QWidget *parent = nullptr);
    ~homepage();
    void show_Home_Page();
    void show_reservation_page();
   // void show_first_floor();

    void show_f1_plan();

    void show_f2_plan();

    void show_f3_plan();

    void show_f4_plan();


    QString username;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::homepage *ui;
    reservation_page *next_page;
    noticeboard *noticeboard1;
    my_reservation * reservation;
    first_floor *firstfloor ;
    f1_plan *f1plan;
    f2_plan *f2plan;
    f3_plan *f3plan;
    f4_plan *f4plan;
    QWidget *home_page;

};
#endif // HOMEPAGE_H
