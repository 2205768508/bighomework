#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
//#include "tower.h"

class QPainter;
//class Tower;

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/HD.png"));

    void setHasTower(bool hasTower = true);
    void setHasnoTower(bool hasTower = false);
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;
    QPoint getPos();
private:
    bool		m_hasTower;
    QPoint		m_pos;
    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
