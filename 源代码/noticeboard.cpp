#include "noticeboard.h"
#include "ui_noticeboard.h"
#include"QDesktopServices.h"
#include"Qurl.h"
noticeboard::noticeboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::noticeboard)
{
    ui->setupUi(this);
}

noticeboard::~noticeboard()
{
    delete ui;
}




void noticeboard::on_news1_clicked()
{

    QDesktopServices::openUrl(QUrl( "https://news.pku.edu.cn/xwzh/99a60304bed14ef8b5253b9f2b3645b4.htm"));


}


void noticeboard::on_news2_clicked()
{
    QDesktopServices::openUrl(QUrl( "https://www.lib.pku.edu.cn/2xxzzfw/26xwgg/261xwlb/bcc5f653bde84e30970e63dd7e41b8ba.htm"));

}


void noticeboard::on_notice1_clicked()
{
     QDesktopServices::openUrl(QUrl( "https://www.lib.pku.edu.cn/2xxzzfw/26xwgg/262gglb/471781e7a4ae449a9ce3e96014ad7746.htm"));
}


void noticeboard::on_news3_clicked()
{
    QDesktopServices::openUrl(QUrl( "https://www.lib.pku.edu.cn/2xxzzfw/26xwgg/261xwlb/e2a79e53bc6044058b920f37bf7df24c.htm"));

}


void noticeboard::on_notice2_clicked()
{
    QDesktopServices::openUrl(QUrl( "https://www.lib.pku.edu.cn/2xxzzfw/26xwgg/262gglb/ad9c51ff98f14a2dad242ee6a06fcca6.htm"));

}


void noticeboard::on_backButton_clicked()
{
    emit notice_goback();
}

