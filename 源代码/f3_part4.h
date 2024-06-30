#ifndef F3_PART4_H
#define F3_PART4_H

#include <QWidget>

namespace Ui {
class f3_part4;
}

class f3_part4 : public QWidget
{
    Q_OBJECT

public:
    explicit f3_part4(QWidget *parent = nullptr);
    ~f3_part4();

private:
    Ui::f3_part4 *ui;
};

#endif // F3_PART4_H
