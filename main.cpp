#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "gamewindow.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>
#include <QElapsedTimer>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow start;
    GameWindow game;


    game.resize(1024,768);
    start.resize(1024,768);

    start.setWindowTitle("Tower Defense");
    game.setWindowTitle("Tower Defense");


    start.show();
    QObject::connect(&start,SIGNAL(showgamewindow()),&game,SLOT(game_show()));
    QObject::connect(&start,SIGNAL(quit()),&a,SLOT(quit()));



    return a.exec();
}
