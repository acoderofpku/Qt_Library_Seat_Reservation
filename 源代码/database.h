#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句
#include <QMessageBox>//消息盒子
#include <QDebug>

void sqlite_Init();//初始化数据库

bool isUsernameAvailable(const QString& username);

bool sign_in_serach(const QString &username,const QString &password);//查找数据

int sign_up_data_upload(const QString &username, const QString &password, const QString &surepsword);//注册

void insertReservationForUser(const QString &username, const QString &seat_id,const QDateTime &reservationTimes);//添加预约

bool isReservationMade(const QString &seat_id, const QDateTime &time);//查找预约

bool deleteReservation(const QString & username,const QString &seat_id, const QDateTime &time);//退约

void add_seat(const QString &seat_id);

void checkCoinsistency();

#endif // DATABASE_H
