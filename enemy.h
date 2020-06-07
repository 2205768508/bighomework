#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QMovie>
#include <QLabel>
#include <QImage>
#include <QMediaPlayer>

class WayPoint;
class QPainter;
class GameWindow;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite = QImage(":/image/monster.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getDamage1(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    virtual void takeorigin();
    QPoint pos() const;

public slots:
    void doActivate();
    void releasedizzied();
    void releasefrozed();

public:
    bool			m_active;
    bool            m_dizzied;
    int             dizzied;
    bool            m_frozed;
    int             frozed;
    bool            m_isboss;
    int 		    m_maxHp;
    int	            m_currentHp;
    qreal			m_walkingSpeed;
    qreal           m_originSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    GameWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;
    QMediaPlayer *  m_enemydestroy;

    const QImage	m_sprite;
    QPixmap         m_sprite_0;
    static const QSize ms_fixedSize;
    static const QSize ms_bossfixedSize;
};

#endif // ENEMY_H
