#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "arrowtower.h"
#include "singlecao.h"
#include "tighttowerposi.h"
#include <QMenu>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QMediaPlaylist>
#include <QMovie>
#include <QMediaPlayer>
namespace Ui {
class GameWindow;
}
class TowerPosition;
class TightTowerPosi;
class WayPoint;
class Enemy;
class Bullet;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removeTower(Tower *tower);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    QList<Enemy *> enemyList() const;

    void showeffect(QPoint&p,int damage);
    void boomeffect();
    void showdeadenemy(QPoint &p,QPixmap &m1);
    void aoe(QPoint &p,int damage);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_pushbutton_gameoff_clicked();
    void on_pushbutton_home_clicked();
    void on_pushbutton_boom_clicked();
    void on_pushbutton_cruelty_clicked();
    void on_pushbutton_rateup_clicked();
    void construct_barbette();
    void construct_warship();
    void construct_heavyplane();
    void construct_tank();
    void action_levelup();
    void action_remove();
    void updateMap();
    void gameStart();
    void main_show();
    void restart();
    void reset();
    void custom_up();
    void hideeffect();
    void hideboom();
    void cover();
signals:
    void quit();
    void gobackhome();
    void showmiddlewindow();
    void showlostwindow();
    void showwinwindow();
private:
    void create_construct_Menu();
    void create_lere_Menu();
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void drawCustom(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    Ui::GameWindow *		ui;
    int						m_waves;
    int						m_playerHp;
    int						m_playerGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    bool                    m_iscruel;
    int                     m_position;
    int                     m_posi;
    int                     m_custom;
    QLabel *                m_label;
    QLabel *                m_boom;


    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
    QList<TightTowerPosi *> m_TightTowerPosiList;
    QList<QLabel*>          m_QLabelList;
    QList<QLabel*>          m_QLabelList1;
    TightTowerPosi *        m_tighter;
    QAction *               warship;
    QAction *               heavyplane;
    QAction *               barbette;
    QAction *               tank;
    QAction *               levelup;
    QAction *               remove;
    QMediaPlayer *          m_towerplace;
    QMediaPlayer *          m_win;
    QMediaPlayer *          m_lost;
    QMediaPlayer *          m_booming;

    QMediaPlayer *          m_lostlife;
    QMenu *                 m_menu_construct;
    QMenu *                 m_menu_lere;
    QPushButton *           button_gameoff;
    QPushButton *           button_home;
    QPushButton *           button_boom;
    QPushButton *           button_cruelty;
    QPushButton *           button_firerateup;
};

#endif // GAMEWINDOW_H
