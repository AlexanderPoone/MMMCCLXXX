#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion")); //remember it's double colon
    QPixmap pixmap(":/logo.png");
    QSplashScreen splash(pixmap);
    splash.show();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
