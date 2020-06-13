#include "arrowtower.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "gamewindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
Warship::Warship(QPoint pos, GameWindow *game,
        const QPixmap &sprite_1 /*= QPixmap(":/image/tower_arrow1.png")*/,
        const QPixmap &sprite_2 /*= QPixmap(":/image/tower_arrow2.png")*/,
        const QPixmap &sprite_3 /*= QPixmap(":/image/tower_arrow3.png")*/,
        const QPixmap &bullet_1 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_2 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_3 /*= QPixmap(":/image/bullet.png")*/)
    : Tower(pos,game,sprite_1,sprite_2,sprite_3,bullet_1,bullet_2,bullet_3)

{
     m_fireRate = 1100;
     m_attackRange = 120;
     m_damage = 50;
     m_cost = 600;
     m_levelCost1 = 650;
     m_levelCost2 = 700;
}


void Warship::levelup(){
    m_level++;
    if(m_level == 2){
        m_attackRange = 140 ;
        m_damage = 700;
        m_fireRate = 900;
    }else if(m_level == 3){
        m_attackRange = 160;
        m_damage = 900;
        m_fireRate = 700;
    }
}

Heavyplane::Heavyplane(QPoint pos, GameWindow *game,
        const QPixmap &sprite_1 /*= QPixmap(":/image/tower_arrow1.png")*/,
        const QPixmap &sprite_2 /*= QPixmap(":/image/tower_arrow2.png")*/,
        const QPixmap &sprite_3 /*= QPixmap(":/image/tower_arrow3.png")*/,
        const QPixmap &bullet_1 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_2 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_3 /*= QPixmap(":/image/bullet.png")*/)
    : Tower(pos,game,sprite_1,sprite_2,sprite_3,bullet_1,bullet_2,bullet_3)

{
     m_candizzied = true;
     m_fireRate = 1400;
     m_attackRange = 100;
     m_damage = 40;
     m_cost = 450;
     m_levelCost1 = 500;
     m_levelCost2 = 550;
}


void Heavyplane::levelup(){
    m_level++;
    if(m_level == 2){
        m_attackRange = 115 ;
        m_damage = 600;
        m_fireRate = 1200;
    }else if(m_level == 3){
        m_attackRange = 130;
        m_damage = 800;
        m_fireRate = 1000;
    }
}

Barbette::Barbette(QPoint pos, GameWindow *game,
        const QPixmap &sprite_1 /*= QPixmap(":/image/tower_arrow1.png")*/,
        const QPixmap &sprite_2 /*= QPixmap(":/image/tower_arrow2.png")*/,
        const QPixmap &sprite_3 /*= QPixmap(":/image/tower_arrow3.png")*/,
        const QPixmap &bullet_1 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_2 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_3 /*= QPixmap(":/image/bullet.png")*/)
    : Tower(pos,game,sprite_1,sprite_2,sprite_3,bullet_1,bullet_2,bullet_3)
{
     m_canfroze = true;
     m_fireRate = 1200;
     m_attackRange = 120;
     m_damage = 30;
     m_cost = 350;
     m_levelCost1 = 400;
     m_levelCost2 = 450;
}


void Barbette::levelup(){
    m_level++;
    if(m_level == 2){
        m_attackRange = 145 ;
        m_damage = 410;
        m_fireRate = 1000;
    }else if(m_level == 3){
        m_attackRange = 170;
        m_damage = 510;
        m_fireRate = 800;
    }
}

Tank::Tank(QPoint pos, GameWindow *game,
        const QPixmap &sprite_1 /*= QPixmap(":/image/tower_arrow1.png")*/,
        const QPixmap &sprite_2 /*= QPixmap(":/image/tower_arrow2.png")*/,
        const QPixmap &sprite_3 /*= QPixmap(":/image/tower_arrow3.png")*/,
        const QPixmap &bullet_1 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_2 /*= QPixmap(":/image/bullet.png")*/,
        const QPixmap &bullet_3 /*= QPixmap(":/image/bullet.png")*/)
    : Tower(pos,game,sprite_1,sprite_2,sprite_3,bullet_1,bullet_2,bullet_3)

{
     m_fireRate = 1400;
     m_attackRange = 120;
     m_damage = 20;
     m_cost = 250;
     m_levelCost1 = 300;
     m_levelCost2 = 350;
}


void Tank::levelup(){
    m_level++;
    if(m_level == 2){
        m_attackRange = 140 ;
        m_damage = 280;
        m_fireRate = 1200;
    }else if(m_level == 3){
        m_attackRange = 160;
        m_damage = 340;
        m_fireRate = 1000;
    }
}






