#ifndef FIRST_FLOOR_H
#define FIRST_FLOOR_H

#include <QWidget>
#include <QPushButton>
#include "seat_situation.h"
namespace Ui {
class first_floor;
}

class first_floor : public QWidget
{
    Q_OBJECT

public:
    explicit first_floor(QWidget *parent = nullptr);
    ~first_floor();
    QString username;

    void choose_seat(int i);
signals:
    void go_back11();
private slots:

    void on_backButton_clicked();

private:
    Ui::first_floor *ui;
    seat_situation * seat;
    QList<QPushButton*> pushButtonList;
};

#endif // FIRST_FLOOR_H
