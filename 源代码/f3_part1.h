#ifndef F3_PART1_H
#define F3_PART1_H

#include <QWidget>

namespace Ui {
class f3_part1;
}

class f3_part1 : public QWidget
{
    Q_OBJECT

public:
    explicit f3_part1(QWidget *parent = nullptr);
    ~f3_part1();

private:
    Ui::f3_part1 *ui;
};

#endif // F3_PART1_H
