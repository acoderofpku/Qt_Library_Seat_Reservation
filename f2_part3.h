#ifndef F2_PART3_H
#define F2_PART3_H

#include <QWidget>

namespace Ui {
class f2_part3;
}

class f2_part3 : public QWidget
{
    Q_OBJECT

public:
    explicit f2_part3(QWidget *parent = nullptr);
    ~f2_part3();

private:
    Ui::f2_part3 *ui;
};

#endif // F2_PART3_H
