#ifndef MY_RESERVATION_H
#define MY_RESERVATION_H
#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QWidget>
#include <QSqlTableModel>

#include <QWidget>

namespace Ui {
class my_reservation;
}

class my_reservation : public QWidget
{
    Q_OBJECT

public:
    explicit my_reservation(QWidget *parent = nullptr);
    ~my_reservation();
    QString username;

    void search_my_reservation();
signals:
    void re_goback();
private slots:

    void on_backButton_clicked();

private:
    Ui::my_reservation *ui;
};

#endif // MY_RESERVATION_H
