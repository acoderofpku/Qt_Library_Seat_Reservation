#ifndef F4_PART3_H
#define F4_PART3_H

#include <QWidget>

namespace Ui {
class f4_part3;
}

class f4_part3 : public QWidget
{
    Q_OBJECT

public:
    explicit f4_part3(QWidget *parent = nullptr);
    ~f4_part3();

private:
    Ui::f4_part3 *ui;
};

#endif // F4_PART3_H
