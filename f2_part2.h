#ifndef F2_PART2_H
#define F2_PART2_H

#include <QWidget>

namespace Ui {
class f2_part2;
}

class f2_part2 : public QWidget
{
    Q_OBJECT

public:
    explicit f2_part2(QWidget *parent = nullptr);
    ~f2_part2();

private:
    Ui::f2_part2 *ui;
};

#endif // F2_PART2_H
