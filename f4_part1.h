#ifndef F4_PART1_H
#define F4_PART1_H

#include <QWidget>

namespace Ui {
class f4_part1;
}

class f4_part1 : public QWidget
{
    Q_OBJECT

public:
    explicit f4_part1(QWidget *parent = nullptr);
    ~f4_part1();

private:
    Ui::f4_part1 *ui;
};

#endif // F4_PART1_H
