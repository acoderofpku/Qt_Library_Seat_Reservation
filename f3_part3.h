#ifndef F3_PART3_H
#define F3_PART3_H

#include <QWidget>

namespace Ui {
class f3_part3;
}

class f3_part3 : public QWidget
{
    Q_OBJECT

public:
    explicit f3_part3(QWidget *parent = nullptr);
    ~f3_part3();

private:
    Ui::f3_part3 *ui;
};

#endif // F3_PART3_H
