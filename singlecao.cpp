#include "singlecao.h"
#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

singlecado::singlecado(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game, sprite)
{
    m_maxHp = 200;
    m_currentHp = 200;
    m_walkingSpeed = 4.0;
    m_originSpeed = 4.0;
}
void singlecado::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 200;
    m_maxHp = 200;
    m_walkingSpeed = 4.0;
    m_originSpeed = 4.0;
}

guai::guai(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game, sprite)
{
    m_maxHp = 300;
    m_currentHp = 300;
    m_walkingSpeed = 3.0;
    m_originSpeed = 3.0;
}
void guai::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 300;
    m_maxHp = 300;
    m_walkingSpeed = 3.0;
    m_originSpeed = 3.0;
}

shou::shou(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game, sprite)
{
    m_maxHp = 300;
    m_currentHp = 300;
    m_walkingSpeed = 3.0;
    m_originSpeed = 3.0;
}
void shou::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 300;
    m_maxHp = 300;
    m_walkingSpeed = 3.0;
    m_originSpeed = 3.0;
}

boss::boss(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game, sprite)
{
    m_isboss = true;
    m_maxHp = 2000;
    m_currentHp = 2000;
    m_walkingSpeed = 2.0;
    m_originSpeed = 2.0;
}
void boss::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 2000;
    m_maxHp = 2000;
    m_walkingSpeed = 2.0;
    m_originSpeed = 2.0;
}

bigboss::bigboss(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite /*= QPixmap(":/image/singlecado.png")*/)
    : Enemy(startWayPoint, game, sprite)
{
    m_isboss = true;
    m_maxHp = 6000;
    m_currentHp = 6000;
    m_walkingSpeed = 2.0;
    m_originSpeed = 2.0;
}
void bigboss::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 6000;
    m_maxHp = 6000;
    m_walkingSpeed = 2.0;
    m_originSpeed = 2.0;
}
