#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include "enemy.h"
#include "gamewindow.h"
#include <QTimer>

class Tower;

class Barbette : public Tower{
public:
    Barbette(QPoint pos, GameWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/barbette_1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/barbette_2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/barbette_3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/fireball_1.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/fireball_2.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/fireball_3.png"));
    void levelup();
};


class Warship : public Tower{
public:
    Warship(QPoint pos, GameWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/warship_1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/warship_2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/warship_3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/fireball_1.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/fireball_2.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/fireball_3.png"));
    void levelup();
};

class Heavyplane : public Tower{
public:
    Heavyplane(QPoint pos, GameWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/heavyplane_1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/heavyplane_2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/heavyplane_3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/fireball_1.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/fireball_2.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/fireball_3.png"));
    void levelup();
};


class Tank : public Tower{
public:
    Tank(QPoint pos, GameWindow *game,
            const QPixmap &sprite_1 = QPixmap(":/image/tank_1.png"),
            const QPixmap &sprite_2 = QPixmap(":/image/tank_2.png"),
            const QPixmap &sprite_3 = QPixmap(":/image/tank_3.png"),
            const QPixmap &bullet_1 = QPixmap(":/image/fireball_1.png"),
            const QPixmap &bullet_2 = QPixmap(":/image/fireball_2.png"),
            const QPixmap &bullet_3 = QPixmap(":/image/fireball_3.png"));
    void levelup();
};




#endif // ARROWTOWER_H
