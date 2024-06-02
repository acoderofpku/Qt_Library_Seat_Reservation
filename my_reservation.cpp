#include "my_reservation.h"
#include "ui_my_reservation.h"
#include <QSqlError>
#include <QInputDialog>
#include <QTime>
#include <QDateTime>
#include <QString>
#include <QDate>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QApplication>
#include <QErrorMessage>
#include <QMessageBox>
#include <QValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPalette>
#include <QTableWidget>

my_reservation::my_reservation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::my_reservation)
{
    ui->setupUi(this);
}

my_reservation::~my_reservation()
{
    delete ui;
}

void my_reservation::search_my_reservation()
{
    QSqlDatabase db = QSqlDatabase::database();//
    if (!db.open())
    {
        qDebug() << "Failed to connect to database 1.";
        return;
    }
    QSqlQuery query(db);//初始化数据表
    QString selectQuery = "SELECT * FROM Reservations WHERE username = 'username'";//查询对应数据
    if (!query.exec(selectQuery))
    {
        qDebug() << "Failed to select data from db:"<< query.lastError().text();
        qDebug("ROLLBACK");
        return;
    }
    QSqlTableModel * model1 = new QSqlTableModel(this,db);
    model1->setTable("Reservations");//设置操作的表为Reseravations
    ui->re_table1->setModel(model1);
    model1->setFilter(QString("username = '%1'").arg(username));
    model1->select();//数据处理
    //数据美化部分,但是表里头的数据是怎么排列的?
    QStringList tables;
    tables << "reservation_id"<<"username"<<"seat_id";//这里是表里头每个username对应数据排列的顺序
    for(int i = 0 ; i < tables.count(); i++)
        model1->setHeaderData(i,Qt::Horizontal,tables[i]);//设置显示框表头显示
    model1->setSort(0, Qt::AscendingOrder);//设置按照第0列排序
    ui->re_table1->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    ui->re_table1->horizontalHeader()->setStretchLastSection(true);//设置最后一列填充后面表格
    ui->re_table1->setColumnWidth(0,200);//设置列宽，界面看起来更舒适,COL,WIDTH
    ui->re_table1->setColumnWidth(1,120);//设置列宽，界面看起来更舒适
    ui->re_table1->setColumnWidth(2,120);//设置列宽，界面看起来更加舒适
   /* QString selectTime= "SELECT time FROM ReservationTimes AS T1 "
                         "JOIN UserReservationTimes AS T2 ON T1.time_id = T2.time_id "
                         "JOIN Reservations AS T3 ON T2.reservation_id = T3.reservation_id "
                         "WHERE T3.username = :username";*/
    QString selectTime = "SELECT time FROM ReservationTimes WHERE time_id IN (SELECT time_id FROM UserReservationTimes "
                         "WHERE reservation_id IN (SELECT reservation_id FROM Reservations WHERE username = :username))";
    query.prepare(selectTime);
    query.bindValue(":username", username);
    if(!query.exec())
    {
        qDebug() << "Failed to search ReservationTimes :" << query.lastError().text();
        query.exec("ROLLBACK"); // 有错误发生，回滚事务
        return;
    }
    QSqlTableModel *model2=new QSqlTableModel(this,db);
    model2->setTable("ReservationTimes");
    ui->re_table2->setModel(model2);
    model2->select();//开始查找
    QStringList table2;
    table2<<"SS";
    model2->setHeaderData(0,Qt::Horizontal,table2[0]);
    ui->re_table1->horizontalHeader()->hideSection(0);
    ui->re_table2->horizontalHeader()->hideSection(0);
    ui->re_table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->re_table2->horizontalHeader()->setStretchLastSection(true);

}


void my_reservation::on_backButton_clicked()
{
    emit re_goback();
}

