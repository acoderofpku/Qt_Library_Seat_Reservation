#include "database.h"
#include "qdatetime.h"
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>
#include <QStringList>
void sqlite_Init()
{
    QSqlDatabase::removeDatabase("seating_system.db");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("seating_system.db");
    if(!db.open())
    {
        qDebug()<<"open error";
    }
    //create excle
    QSqlQuery query;
    query.exec("BEGIN TRANSACTION");
    QString createusers=QString("create table if not exists Users(id integer primary key autoincrement,"
                                  "username TEXT unique not NULL,""password TEXT not NULL);");
    if(!query.exec(createusers))
    {
        qDebug()<<"users table create error:"<<query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    else
    {
        qDebug()<<"users table create success";
    }
    QString createseats = QString("CREATE TABLE IF NOT EXISTS Seats ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "seat_id TEXT unique not NULL);");
    if(!query.exec(createseats))
    {
        qDebug()<<"seats table create error:"<<query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    else
    {
        qDebug()<<"seats table create success";
    }
    QString createReservationTimesTable = QString("CREATE TABLE IF NOT EXISTS ReservationTimes ("
                                                  "time_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                  "time DATETIME NOT NULL);");
    if (!query.exec(createReservationTimesTable))
    {
        qDebug() << "Failed to create ReservationTimes table:" << query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    QString creatreservations = QString("CREATE TABLE IF NOT EXISTS Reservations ("
                                        "reservation_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "username TEXT NOT NULL,"
                                        "seat_id TEXT NOT NULL,"
                                        "FOREIGN KEY(username) REFERENCES Users(username),"
                                        "FOREIGN KEY(seat_id) REFERENCES Seats(seat_id) ON DELETE CASCADE ON UPDATE CASCADE);");
    if(!query.exec(creatreservations))
    {
        qDebug()<<"Reservations table create error:"<<query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    else
    {
        qDebug()<<"Reservations table create success";
    }
    // 创建UserReservationTimes关联表
    QString createUserReservationTimesTable = QString("CREATE TABLE IF NOT EXISTS UserReservationTimes ("
                                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                      "reservation_id INTEGER,"
                                                      "time_id INTEGER,"
                                                      "UNIQUE(reservation_id, time_id),"
                                                      "FOREIGN KEY(reservation_id) REFERENCES Reservations(reservation_id),"
                                                      "FOREIGN KEY(time_id) REFERENCES ReservationTimes(time_id));");
    if (!query.exec(createUserReservationTimesTable))
    {
        qDebug() << "Failed to create UserReservationTimes table:" << query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    query.exec("COMMIT");
}

void add_seat(const QString &seat_id)
{
    QSqlDatabase db = QSqlDatabase::database(); // 假设数据库已经打开
    if (!db.isValid())
    {
        qDebug() << "Database not properly initialized.";
        return ;
    }
    QSqlQuery query(db);
    query.exec("BEGIN TRANSACTION");
    QString uniseat = "SELECT COUNT(*) FROM Seats WHERE seat_id = :seat_id";
    query.prepare(uniseat);
    query.addBindValue(seat_id);
    if (!query.exec())
    {
        qDebug() << "Error cheaking seat existence in Seats: " << query.lastError().text();
        query.exec("ROLLBACK");
        return ;
    }
    if(query.next() && query.value(0).toInt() > 0)
    {
        qDebug()<<"Seat_id already exists";
        return ;
    }
    QString addseat = "INSERT INTO Seats(seat_id) values(:seat_id)";
    query.prepare(addseat);
    query.addBindValue(seat_id);
    if (!query.exec())
    {
        qDebug() << "Error adding new seat in Seats: " << query.lastError().text();
        query.exec("ROLLBACK");
        return ;
    }
    query.exec("COMMIT");
}

bool sign_in_serach(const QString &username, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::database();
    // 使用参数占位符 ? 来代替直接的值，并在prepare后使用bindValue绑定
    QString sql = QString("SELECT * FROM Users WHERE username=? AND password=?");
    QSqlQuery query(db);
    query.exec("BEGIN TRANSACTION");
    query.prepare(sql);
    query.addBindValue(username); // 绑定第一个问号
    query.addBindValue(password); // 绑定第二个问号
    qDebug() << "Executing Query:" << query.lastQuery(); // 打印即将执行的SQL语句
    qDebug() << "Bound Values Count:" << query.boundValues().count(); // 打印绑定的参数数量
    if (query.exec() && query.next())
    {
        query.exec("COMMIT");
        return true;
    }
    else
    {
        query.exec("COMMIT");
        return false;
    }
}

bool isUsernameAvailable(const QString& username) {
    // 假设你已经有一个已经初始化的QSqlDatabase对象
    // 如果还没有，你需要先连接数据库
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("BEGIN TRANSACTION");
    // 构造查询语句，检查用户名是否已存在
    QString sql = "SELECT COUNT(*) FROM Users WHERE username = :username";
    query.prepare(sql);
    query.bindValue(":username", username);
    qDebug() << "Executing Query:" << query.lastQuery(); // 打印即将执行的SQL语句
    qDebug() << "Bound Values Count:" << query.boundValues().count(); // 打印绑定的参数数量
    // 执行查询
    if (!query.exec()) {
        // 处理查询错误
        qDebug() << "Error querying database:" << query.lastError().text();
        query.exec("COMMMIT");
        return false; // 或者你可以根据错误情况返回不同的值
    }

    // 读取查询结果
    if (query.next()) {
        int count = query.value(0).toInt();
        // 如果计数大于0，表示用户名已存在
        query.exec("COMMMIT");
        if (count > 0) {
            return false;
        } else {
            return true; // 用户名可用
        }
    } else {
        // 没有结果，可能是查询语句有问题或其他错误
        qDebug() << "No result from query";
        query.exec("COMMMIT");
        return false; // 或者你可以根据错误情况返回不同的值
    }
}

int sign_up_data_upload(const QString &username, const QString &password, const QString &surepsword)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(password == surepsword)
    {
        if (username.isEmpty())
        {
            return 3;
        }
        if (!isUsernameAvailable(username))
        {
            return 5;
        }
        if (password.length() < 7 || password.length() > 14)
        {
            return 4;
        }
        //创建执行语句对象
        QSqlQuery query(db);
        query.exec("BEGIN TRANSACTION");
        query.prepare(("insert into Users(username,password) values(:username,:password)"));
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        if (!query.exec())
        {
            query.exec("COMMMIT");
            return 1;
        }
        else
        {
            query.exec("COMMMIT");
            return 0;
        }
    }
    else
    {
        return 2;
    }
}

void insertReservationForUser(const QString &username, const QString &seat_id, const QDateTime &reservationTimes)
{
    QSqlDatabase db = QSqlDatabase::database();
    /*if (db.isOpen())
    {
        QSqlQuery pragmaQuery(db);
        if (!pragmaQuery.exec("PRAGMA foreign_keys = ON;"))
        {
            qDebug() << "Failed to turn on foreign keys: " << pragmaQuery.lastError().text();
        }
        else {
            qDebug() << "Foreign keys support enabled.";
        }
    }*/

    QSqlQuery query(db);
    query.exec("BEGIN TRANSACTION");
    QString insertTime = QString("INSERT INTO ReservationTimes (time) VALUES (:time)");
    query.prepare(insertTime);
    query.bindValue(":time", reservationTimes.toString(Qt::ISODate));
    if (!query.exec())
    {
        qDebug() << "Failed to insert time:" << query.lastError().text();
        query.exec("ROLLBACK");
        return;
    }
    else
    {
        qDebug()<<"Insert time successfully";
    }

    // 在Reservations表中创建预约记录
    QString insertReservation = QString("INSERT INTO Reservations (username, seat_id) VALUES (:username, :seat_id)");
    query.prepare(insertReservation);
    qDebug()<<username<<seat_id;
    query.bindValue(":username", username);
    query.bindValue(":seat_id", seat_id); // 确保绑定seat_id
    if (!query.exec())
    {
        qDebug() <<"Failed to insert into Reservations:" << query.lastError().text();
        query.exec("ROLLBACK");
        return;
    }
    int reservationId = query.lastInsertId().toInt();

    // 在UserReservationTimes表中插入关联
    if (reservationId > 0) // 确保reservationId有效
    {
        QString getTimeId = QString("SELECT time_id FROM ReservationTimes WHERE time = :time");
        query.prepare(getTimeId);
        query.bindValue(":time", reservationTimes.toString(Qt::ISODate)); // 使用bindValue
        if (!query.exec() || !query.next())
        {
            qDebug() << "Failed to get time_id:" << query.lastError().text();
            query.exec("ROLLBACK");
            return;
        }
        int timeId = query.value(0).toInt();


        QString insertUserReservationTime = QString("INSERT INTO UserReservationTimes (reservation_id, time_id) VALUES (:reservation_id, :time_id)");
        query.prepare(insertUserReservationTime);
        query.bindValue(":reservation_id", reservationId);
        query.bindValue(":time_id", timeId);
        if (!query.exec())
        {
            qDebug() << "Failed to insert into UserReservationTimes:" << query.lastError().text();
            query.exec("ROLLBACK");
        }
    }

    query.exec("COMMIT"); // 提交事务
}

bool isReservationMade(const QString &seat_id, const QDateTime &time)
{
    QSqlDatabase db = QSqlDatabase::database(); // 假设数据库已经通过其他地方初始化并打开
    if (!db.isValid()) {
        qDebug() << "Database not properly initialized.";
        return false;
    }
    QSqlQuery query(db);
    // 首先，找出与该座位相关的所有预约记录ID
    query.exec("BEGIN TRANSACTION");
    QString findReservationIds = QString("SELECT  reservation_id FROM Reservations WHERE seat_id = :seat_id");
    query.prepare(findReservationIds);
    //qDebug()<< seat_id;
    //qDebug() << "Executing Query:" << query.lastQuery(); // 打印即将执行的SQL语句
    //qDebug() << "Bound Values Count:" << query.boundValues().count(); // 打印绑定的参数数量
    query.bindValue(":seat_id", seat_id);

    if (!query.exec())
    {
        qDebug() << "Error querying reservations for seat: " << query.lastError().text();
        query.exec("ROLLBACK");
        return false;
    }
    // 使用集合存储相关的reservation_id，以避免多次查询
    QSet<int> relatedReservationIds;
    while (query.next())
    {
        relatedReservationIds.insert(query.value(0).toInt());
    }

    if (relatedReservationIds.isEmpty())
    {
        query.exec("COMMIT");
        return false; // 该座位没有相关预约
    }
    // 现在，检查这些预约是否包含了特定时间
    QString checkTimeInReservation = "SELECT COUNT(*) FROM UserReservationTimes AS URT "
                                     "JOIN ReservationTimes AS RT ON URT.time_id = RT.time_id "
                                     "WHERE URT.reservation_id  = :reservationIds AND RT.time = :time;";
    for (int reservation:relatedReservationIds)
    {
        query.prepare(checkTimeInReservation);
        //qDebug()<<time.toString(Qt::ISODate);
        query.bindValue(":reservationIds",reservation);
        query.bindValue(":time", time.toString(Qt::ISODate));
        if (!query.exec())
        {
            qDebug() << "Error checking time in reservations: " << query.lastError().text();
            query.exec("ROLLBACK");
            return false;
        }
        if (query.next())
        {
            if(query.value(0).toInt() > 0)
                return true; // 如果计数大于0，说明找到了匹配的时间和座位的预约记录
        }
    }
    query.exec("COMMIT");
    return false; // 没有找到匹配的时间
}

bool deleteReservation(const QString& username,const QString &seat_id, const QDateTime &time)
{
    QSqlDatabase db = QSqlDatabase::database(); // 假设数据库已经打开
    if (!db.isValid())
    {
        qDebug() << "Database not properly initialized.";
        return false;
    }
    QSqlQuery query(db);
    query.exec("BEGIN TRANSACTION");
    // 首先，找出与该座位相关的所有预约记录ID
    QString findReservationIds =QString("SELECT  reservation_id FROM Reservations WHERE seat_id = :seat_id");
    query.prepare(findReservationIds);
    query.bindValue(":seat_id", seat_id);
    if (!query.exec())
    {
        qDebug() << "Error querying reservations for seat: " << query.lastError().text();
        query.exec("ROLLBACK");
        return false;
    }
    QSet<int> relatedReservationIds;
    while (query.next())
    {
        relatedReservationIds.insert(query.value(0).toInt());
    }
    if (relatedReservationIds.isEmpty())
    {
        return false; // 该座位没有相关预约
    }


    QString confirmuser = QString("SELECT username FROM Reservations WHERE reservation_id = :reservation_id");
    for (int reservation_id:relatedReservationIds)
    {
    //    qDebug()<<reservation_id;
        query.prepare(confirmuser);
        query.bindValue(":reservation_id", reservation_id);
        if (!query.exec())
        {
            qDebug() << "Error confirming user for reservation: " << query.lastError().text();
            query.exec("ROLLBACK");
            return false;
        }
        bool res = query.next();
        qDebug()<<res;
        if(res)
        {
            if(username == query.value(0).toString())
            {
                try
                {
                    // 删除ReservationTimes表中匹配的时间记录
                    QString deleteReservationTimes = "DELETE FROM ReservationTimes "
                                                         "WHERE time_id IN ("
                                                         "SELECT T2.time_id "
                                                         "FROM UserReservationTimes AS T2 "
                                                         "JOIN ReservationTimes AS T1 ON T1.time_id = T2.time_id "
                                                         "WHERE T2.reservation_id = :reservation_id AND T1.time = :time"
                                                         ")";
                    query.prepare(deleteReservationTimes);
                    query.bindValue(":reservation_id", reservation_id);
                    query.bindValue(":time", time.toString(Qt::ISODate));
                    if (!query.exec())
                    {
                        qDebug() << "Error deleting from ReservationTimes: " << query.lastError().text();
                        query.exec("ROLLBACK"); // 出现错误，回滚事务
                        return false;
                    }
                    // 删除Reservations表中匹配的记录
                    QString deleteReservations = "DELETE FROM Reservations "
                                                "WHERE reservation_id = :reservation_id";
                    query.prepare(deleteReservations);
                    query.bindValue(":reservation_id", reservation_id);
                    if (!query.exec())
                    {
                        qDebug() << "Error deleting from Reservations: " << query.lastError().text();
                        query.exec("ROLLBACK"); // 出现错误，回滚事务
                        return false;
                    }
                    // 提交事务
                    if (!query.exec("COMMIT"))
                    {
                        qDebug() << "Error committing transaction: " << query.lastError().text();
                        return false;
                    }
                }
                catch (...)
                {
                    query.exec("ROLLBACK"); // 异常时回滚事务
                    throw; // 重新抛出异常
                }
                return true; // 删除成功
            }
        }
    }
    return false;
}

void checkCoinsistency()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isValid()) {
        qDebug() << "Database not properly initialized.";
        return;
    }

    QSqlQuery checkConsistency(db);

    // 准备并执行更正后的查询
    QString consistencyCheckQuery =
        "SELECT R.time_id "
        "FROM ReservationTimes AS R "
        "WHERE NOT EXISTS (SELECT 1 FROM UserReservationTimes AS URT WHERE URT.time_id = R.time_id)";

    if (!checkConsistency.prepare(consistencyCheckQuery)) {
        qDebug() << "Failed to prepare the query: " << checkConsistency.lastError().text();
        return;
    }

    if (!checkConsistency.exec()) {
        qDebug() << "Failed to execute the query: " << checkConsistency.lastError().text();
        return;
    }

    // 处理查询结果
    while (checkConsistency.next()) {
        int reservationId = checkConsistency.value(0).toInt();
        qDebug() << "Inconsistent data found: time ID" << reservationId << "not linked in UserReservationTimes.";
    }
}
