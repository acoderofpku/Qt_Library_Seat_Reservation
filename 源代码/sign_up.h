#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include "ui_sign_up.h"

namespace Ui {
class sign_up;
}

class sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

private slots:
    void on_SureButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::sign_up *ui;
};

#endif // SIGN_UP_H
