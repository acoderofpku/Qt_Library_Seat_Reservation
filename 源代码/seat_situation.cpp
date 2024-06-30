#include "seat_situation.h"
#include "database.h"
#include "ui_seat_situation.h"
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
seat_situation::seat_situation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::seat_situation)
{
    ui->setupUi(this);
    //ui->editCalendar->setValidator(new QIntValidator(0,0,this));//限制显示日期的文本框不能输入任何东西
    //ui->reservation_table->verticalHeader()->setVisible(false);
    //ui->reservation_table->horizontalHeader()->setVisible(false);
    ui->reservation_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->reservation_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPalette palette;
    palette.setColor(QPalette::Base,QColor(255,255,255));
    palette.setColor(QPalette::AlternateBase,QColor(233,245,252));
    ui->reservation_table->setPalette(palette);
    ui->reservation_table->setFrameShape(QFrame::NoFrame);
    ui->reservation_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reservation_table->setColumnWidth(0,50);
    ui->reservation_table->setFocusPolicy(Qt::NoFocus);//美化预约情况表格
    datetime=QDateTime::currentDateTime();
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);//居中
    label->setGeometry(290, 40, 150, 100);

    label->setText(datetime.toString("yyyy-MM-dd hh:mm:ss ddd"));
    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &seat_situation::timeUpdate);
    Timer->start(1000);//计时器更新连接label
    for(int i=0;i<14;i++)
    {
        QTableWidgetItem *item = ui->reservation_table->item(i, 0);
        if (!item)
        {
            item = new QTableWidgetItem();
            ui->reservation_table->setItem(i, 0, item);
        }
        QDateTime timelist(QDate::currentDate(),QTime(i+8,0));
        if(isReservationMade(seat_id,timelist)){
            item->setBackground(QColor(254,0,0));
        }
        else
        {
            item->setBackground(QColor(0,255,255));
        }
    }//界面打开的时候就开始进行变色处理
    Timer_for_List=new QTimer(this);
    connect(Timer_for_List,&QTimer::timeout,this,&seat_situation::listUpdate);
    Timer_for_List->start(10000);//每分钟更新一次表格的显示
}

seat_situation::~seat_situation()
{

    delete ui;
}


void seat_situation::on_resevre_button_clicked()
{

    QStringList items;
    items<<tr("8~9")<<tr("9~10")<<tr("10~11")<<tr("11~12")<<tr("12~13")<<tr("13~14")<<tr("14~15")<<tr("15~16")<<tr("16~17")<<tr("17~18")<<tr("18~19")<<tr("19~20")<<tr("20~21")<<tr("21~22");
    QString choose=QInputDialog::getItem(this,tr(u8"选择你要预约的时间"),tr(u8"请选择"),items,0,false);
    std::string str = choose.toStdString();
    str[0] == '1'?str[0] = 10 + str[1] : str[0] = str[0];
    str[0] == '2'?str[0] = 20 + str[1] : str[0] = str[0];
    int chosen_time=int(str[0]-'0');//获取选择的时间
    QDateTime time(QDate::currentDate(),QTime(chosen_time, 0));
    int current_hour=QTime::currentTime().hour();
    if(current_hour>chosen_time)
    {
        QMessageBox::warning(this,"warning",u8"时间已过，无法预约");
        return;
    }
    if (isReservationMade(seat_id, time))
    {
        QMessageBox::warning(this,"warning", u8"该时段已被预约");
    }
    else
    {
        qDebug()<< seat_id;
        qDebug()<<time;
        insertReservationForUser(username, seat_id, time);
        QMessageBox::information(this,tr(u8"预约成功"),tr(u8"预约成功"),QMessageBox::Ok);//当预约成功的时候可以弹出表示已经预约成功了
    }
}

void seat_situation::on_time_label_linkActivated(const QString &link)
{

}
void seat_situation::on_pre_de_reserve_button_clicked()
{
    QStringList items;
    items<<tr("8~9")<<tr("9~10")<<tr("10~11")<<tr("11~12")<<tr("12~13")<<tr("13~14")<<tr("14~15")<<tr("15~16")<<tr("16~17")<<tr("17~18")<<tr("18~19")<<tr("19~20")<<tr("20~21")<<tr("21~22");
    QString choose=QInputDialog::getItem(this,tr(u8"选择你要退约的时间"),tr(u8"请选择"),items,0,true);
    std::string str = choose.toStdString();
    if(choose.isEmpty())
        return;
    str[0] == '1'?str[0] = 10 + str[1] : str[0] = str[0];
    str[0] == '2'?str[0] = 20 + str[1] : str[0] = str[0];
    int chosen_time=int(str[0]-'0');//获取选择的时间
    QDateTime time(QDate::currentDate(),QTime(chosen_time, 0));
    int current_hour=QTime::currentTime().hour() - 1;
    if(current_hour>chosen_time)
    {
        QMessageBox::warning(this,"warning",u8"预约已失效");
        return;
    }
    else if(!isReservationMade(seat_id,time))
    {
        QMessageBox::warning(this,"warning",u8"在这个时间段并没有预约");
        return;

    }
    int res=QMessageBox::question(this,u8"是否确认要取消",u8"你是否确认要取消选择时段的预约",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    switch(res){
    case QMessageBox::Cancel:
        return;
        break;
    case QMessageBox::Ok:
        if(deleteReservation(username,seat_id,time))
        {
            QMessageBox::information(this,tr(u8"退约成功"),tr(u8"退约成功"));
        }
        else
        {
            QMessageBox::warning(this,tr(u8"退约失败"),tr(u8"你并没有此段时间的预约"));
        }
        break;
    }
    return ;
}

void seat_situation::timeUpdate(void)
{
    datetime = QDateTime::currentDateTime();
    this->label->setText(datetime.toString("yyyy-MM-dd hh:mm:ss ddd"));

}//数据更新
void seat_situation::listUpdate(void){
    datetime=QDateTime::currentDateTime();
    int now = QTime::currentTime().hour();
    for(int i=0;i<14;i++)
    {
        QDateTime timelist(QDate::currentDate(),QTime(i+8,0));
        if(i + 8 < now)
        {
            ui->reservation_table->item(i, 0)->setBackground(QColor(255,255,255));
            qDebug()<<u8"已过时间变色成功";
            continue;
        }
        if(isReservationMade(seat_id,timelist)){
            ui->reservation_table->item(i, 0)->setBackground(QColor(254,0,0));//如果有预约，那么表格就会变成红色
            //qDebug()<<seat_id;
            //qDebug()<<timelist;
            qDebug()<<u8"预约时间变色成功";

        }
        else{
            ui->reservation_table->item(i, 0)->setBackground(QColor(0,255,255));//如果没有预约，表格就变成青色（Qcolor是RGB调色板的，不喜欢可以调整)
            //qDebug()<<seat_id;
            //qDebug()<<timelist;
            qDebug()<<u8"空闲时间变色成功";
        }
    }

}


