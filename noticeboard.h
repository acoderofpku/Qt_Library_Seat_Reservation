#ifndef NOTICEBOARD_H
#define NOTICEBOARD_H

#include <QWidget>

namespace Ui {
class noticeboard;
}

class noticeboard : public QWidget
{
    Q_OBJECT

public:
    explicit noticeboard(QWidget *parent = nullptr);
    ~noticeboard();
signals:
    void notice_goback();
private slots:
    void on_news1_clicked();

    void on_news2_clicked();

    void on_notice1_clicked();

    void on_news3_clicked();

    void on_notice2_clicked();

    void on_backButton_clicked();

private:
    Ui::noticeboard *ui;
};

#endif // NOTICEBOARD_H
