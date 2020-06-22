#include "mainwindow.h"
#include <QApplication>
#include "gamewindow.h"
#include "middlewindow.h"
#include "winwindow.h"
#include "lostwindow.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>
#include <QElapsedTimer>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow start;
    GameWindow w;
    MiddleWindow middle;
    WinWindow win;
    LostWindow lost;

    w.resize(1024,768);
    start.resize(1024,768);
    middle.resize(1024,768);
    win.resize(1024,768);
    lost.resize(1024,768);

    start.setWindowTitle("Tower Defense");
    w.setWindowTitle("Tower Defense");
    middle.setWindowTitle("Tower Denfense");
    win.setWindowTitle("Tower Denfense");
    lost.setWindowTitle("Tower Denfense");


    start.show();
    QObject::connect(&start,SIGNAL(showgamewindow()),&w,SLOT(main_show()));
    QObject::connect(&start,SIGNAL(quit()),&a,SLOT(quit()));

    QObject::connect(&w,SIGNAL(gobackhome()),&start,SLOT(start_show()));
    QObject::connect(&w,SIGNAL(showmiddlewindow()),&middle,SLOT(middle_show()));
    QObject::connect(&w,SIGNAL(showwinwindow()),&win,SLOT(Win_show()));
    QObject::connect(&w,SIGNAL(showlostwindow()),&lost,SLOT(lost_show()));
    QObject::connect(&w,SIGNAL(quit()),&a,SLOT(quit()));

    QObject::connect(&middle,SIGNAL(showsecondcustom()),&w,SLOT(custom_up()));
    QObject::connect(&middle,SIGNAL(gobackhome()),&start,SLOT(start_show()));
    QObject::connect(&middle,SIGNAL(quit()),&a,SLOT(quit()));

    QObject::connect(&win,SIGNAL(gobackhome()),&start,SLOT(start_show()));
    QObject::connect(&win,SIGNAL(quit()),&a,SLOT(quit()));

    QObject::connect(&lost,SIGNAL(gobackhome()),&start,SLOT(start_show()));
    QObject::connect(&lost,SIGNAL(showmainwindow()),&w,SLOT(restart()));
    QObject::connect(&lost,SIGNAL(quit()),&a,SLOT(quit()));


    return a.exec();
}
