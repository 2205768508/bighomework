#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QtMath>
#include <QVector2D>

class Enemy;
class GameWindow;
class QPainter;

class Bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           GameWindow *game, const QPixmap &sprite);

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap 	m_sprite;
    QPoint			m_currentPos;
    qreal			m_rotationSprite;
    Enemy *			m_target;
    GameWindow *	m_game;
    int				m_damage;

    static const QSize ms_fixedSize;
};

#endif // BULLET_H
