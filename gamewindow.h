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
QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

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
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    void loadTowerPositions();
    void addWayPoints();
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void drawCustom(QPainter *painter);
};

#endif // GAMEWINDOW_H
