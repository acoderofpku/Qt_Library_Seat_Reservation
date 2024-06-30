#ifndef F4_PART2_H
#define F4_PART2_H

#include <QWidget>

namespace Ui {
class f4_part2;
}

class f4_part2 : public QWidget
{
    Q_OBJECT

public:
    explicit f4_part2(QWidget *parent = nullptr);
    ~f4_part2();

private:
    Ui::f4_part2 *ui;
};

#endif // F4_PART2_H
