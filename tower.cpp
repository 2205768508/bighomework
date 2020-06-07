#include "tower.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
Tower::Tower(QPoint pos, MainWindow *game, const QPixmap &sprite_1, const QPixmap &sprite_2, const QPixmap &sprite_3):
    m_attackRange(70)
    , m_game(game)
    , m_pos(pos)
    , m_sprite_1(sprite_1)
    , m_sprite_2(sprite_2)
    , m_sprite_3(sprite_3)
{


}
void Tower::draw(QPainter *painter) const
{
        painter->save();
        painter->setPen(Qt::white);
        // 绘制攻击范围
        painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
        // 绘制偏转坐标,由中心+偏移=左上
        QPoint offsetPoint(-m_sprite_1.width() /2, -m_sprite_1.height() /2);
        // 绘制炮塔并选择炮塔
        painter->translate(m_pos);
        painter->drawPixmap(offsetPoint, m_sprite_1);
        painter->restore();
 }
