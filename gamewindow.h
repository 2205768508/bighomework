#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QMediaPlaylist>
#include <QMovie>
#include <QMediaPlayer>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QList>
#include "tower.h"
#include "towerposition.h"
#include "waypoint.h"
#include "bullet.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    QList<Enemy *> enemyList() const;
    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removeTower(Tower *tower);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
private slots:
    void game_show();
private:
    Ui::GameWindow *		ui;
    QMediaPlayer *          m_towerplace;
    QMediaPlayer *          m_win;
    QMediaPlayer *          m_lost;
    QMediaPlayer *          m_booming;
    QMediaPlayer *          m_lostlife;
    int						m_waves;
    int						m_playerHp;
    int						m_playerGold;
    int                     m_position;
    int                     m_posi;
    int                     m_custom;
    bool					m_gameEnded;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
    void loadTowerPositions();
    void addWayPoints();
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void drawCustom(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();
};

#endif // GAMEWINDOW_H
