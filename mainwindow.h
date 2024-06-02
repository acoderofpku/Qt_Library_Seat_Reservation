#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStackedWidget>
#include "sign_up.h"
#include "homepage.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void log_in_hide();
    void log_in_show();

private slots:
    void on_loginButton_clicked();

    void on_signupButton_clicked();

    void on_BackwardButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::MainWindow *ui;
    homepage * next_homepage;

    QString username;
    sign_up * sign_up_widget;
};
#endif // MAINWINDOW_H
