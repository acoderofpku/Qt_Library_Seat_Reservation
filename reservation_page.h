#ifndef RESERVATION_PAGE_H
#define RESERVATION_PAGE_H

#include <QWidget>
#include"f1_plan.h"
#include"f2_plan.h"
#include"f3_plan.h"
#include"f4_plan.h"
namespace Ui {
class reservation_page;
}

class reservation_page : public QWidget
{
    Q_OBJECT

public:
    explicit reservation_page(QWidget *parent = nullptr);
    ~reservation_page();

    QString username;

private slots:
    void on_backButton_clicked();

    void on_firstButton_clicked();

    void on_secondButton_clicked();

    void on_thirdButton_clicked();

    void on_forthButton_clicked();

signals:
    void goback();
    void first();
    void second();
    void third();
    void forth();
private:
    Ui::reservation_page *ui;
};

#endif // RESERVATION_PAGE_H
