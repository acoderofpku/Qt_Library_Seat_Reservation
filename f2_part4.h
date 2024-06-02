#ifndef F2_PART4_H
#define F2_PART4_H

#include <QWidget>

namespace Ui {
class f2_part4;
}

class f2_part4 : public QWidget
{
    Q_OBJECT

public:
    explicit f2_part4(QWidget *parent = nullptr);
    ~f2_part4();

private:
    Ui::f2_part4 *ui;
};

#endif // F2_PART4_H
