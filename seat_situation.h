#ifndef SEAT_SITUATION_H
#define SEAT_SITUATION_H
#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class seat_situation;
}
QT_END_NAMESPACE

class seat_situation : public QWidget
{
    Q_OBJECT

public:
    seat_situation(QWidget *parent = nullptr);
    ~seat_situation();
    void timeUpdate(void);
    void listUpdate(void);

    QString seat_id;

    QString username;
private slots:
    void on_resevre_button_clicked();

    void on_pre_de_reserve_button_clicked();

    void on_time_label_linkActivated(const QString &link);

private:
    Ui::seat_situation *ui;
    QTimer *Timer;
    QDateTime datetime;
    QLabel *label;
    QTimer *Timer_for_List;
};
#endif // SEAT_SITUATION_H
