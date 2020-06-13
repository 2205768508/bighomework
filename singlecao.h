#ifndef SINGLECADO_H
#define SINGLECADO_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "waypoint.h"
#include <QPainter>
#include "gamewindow.h"
#include "tower.h"

class Enemy;

class singlecado : public Enemy
{
public:
    singlecado(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/singlecado.png"));
    void takeorigin();

};

class guai : public Enemy
{
public:
    guai(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/guai.png"));
    void takeorigin();

};

class shou : public Enemy
{
public:
    shou(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/shou.png"));
    void takeorigin();

};

class boss : public Enemy
{
public:
    boss(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/boss.png"));
    void takeorigin();

};

class bigboss : public Enemy
{
public:
    bigboss(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/bigboss.png"));
    void takeorigin();

};



#endif // SINGLECADO_H
