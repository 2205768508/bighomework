#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
class QPainter;
class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite_1, const QPixmap &sprite_2, const QPixmap &sprite_3);
    ~Tower(){};
    void draw(QPainter *painter) const;

public:
    MainWindow *	m_game;
    QPoint	        m_pos;
    const QPixmap   m_sprite_1;
    const QPixmap   m_sprite_2;
    const QPixmap   m_sprite_3;
    static const QSize ms_fixedSize;
private:
    int				m_attackRange;
};

#endif // TOWER_H
