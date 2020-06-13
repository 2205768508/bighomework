#include "tighttowerposi.h"

const QSize TightTowerPosi::m_fixedSize(44, 44);

TightTowerPosi::TightTowerPosi(TightTowerPosi*& tighter)
    :m_pos(tighter->m_pos)
    ,m_tower(tighter->m_tower)
{}

TightTowerPosi::TightTowerPosi(QPoint pos, Tower *tower, GameWindow *game):
    m_pos(pos),
    m_tower(tower)
{}

Tower* TightTowerPosi::getTower(){
    return this->m_tower;
}

QPoint TightTowerPosi::getPos(){
    return this->m_pos;
}

const QPoint TightTowerPosi::centerPos() const
{
    QPoint offsetPoint(m_fixedSize.width() / 2, m_fixedSize.height() / 2);
    return m_pos + offsetPoint;
}

bool TightTowerPosi::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + m_fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + m_fixedSize.height());
    return isXInHere && isYInHere;
}
