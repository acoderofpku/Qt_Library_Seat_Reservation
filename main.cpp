#include "mainwindow.h"
#include "sign_up.h"
#include "homepage.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    sqlite_Init();
    MainWindow w;
    w.show();
    return a.exec();
}
