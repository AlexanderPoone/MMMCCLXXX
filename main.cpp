#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/logo.png");
    QSplashScreen splash(pixmap);
    splash.show();
    MainWindow w;
    w.show();

    return a.exec();
}
