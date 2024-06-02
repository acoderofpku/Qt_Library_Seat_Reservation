#ifndef F2_PART1_H
#define F2_PART1_H

#include <QWidget>

namespace Ui {
class f2_part1;
}

class f2_part1 : public QWidget
{
    Q_OBJECT

public:
    explicit f2_part1(QWidget *parent = nullptr);
    ~f2_part1();

private:
    Ui::f2_part1 *ui;
};

#endif // F2_PART1_H
