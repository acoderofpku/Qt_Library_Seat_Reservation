#ifndef F3_PART2_H
#define F3_PART2_H

#include <QWidget>

namespace Ui {
class f3_part2;
}

class f3_part2 : public QWidget
{
    Q_OBJECT

public:
    explicit f3_part2(QWidget *parent = nullptr);
    ~f3_part2();

private:
    Ui::f3_part2 *ui;
};

#endif // F3_PART2_H
