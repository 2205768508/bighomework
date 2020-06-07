#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "enemy.h"
#include "bullet.h"
#include <plistreader.h>
#include <QMessageBox>
#include <QXmlStreamReader>
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::GameWindow)
  , m_waves(0)
  , m_playerHp(5)
  , m_playerGold(4000)
  , m_gameEnded(false)
  , m_posi(NULL)
  , m_position(0)
  , m_custom(1){
    ui->setupUi(this);
    loadTowerPositions();
    addWayPoints();

    m_towerplace = new QMediaPlayer(this);
    m_win = new QMediaPlayer(this);
    m_lost = new QMediaPlayer(this);
    m_booming = new QMediaPlayer(this);
    m_lostlife = new QMediaPlayer(this);

    m_towerplace->setMedia(QUrl("qrc:/music/tower_place.wav"));
    m_win->setMedia(QUrl("qrc:/music/win.mp3"));
    m_lost->setMedia(QUrl("qrc:/music/lose.mp3"));
    m_booming->setMedia(QUrl("qrc:/music/boom.wav"));
    m_lostlife->setMedia(QUrl("qrc:/music/life_lost.wav"));

    m_towerplace->setVolume(100);
    m_win->setVolume(100);
    m_lost->setVolume(100);
    m_booming->setVolume(100);
    m_lostlife->setVolume(100);

    QMediaPlayer * player = new QMediaPlayer(this);
    QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();
    QMediaContent media(QUrl("qrc:/music/bgm.mp3"));
    player->setVolume(100);

    backgroundMusicList->addMedia(media);
    backgroundMusicList->setCurrentIndex(0);
    backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(backgroundMusicList);
    player->play();
}
void GameWindow::loadTowerPositions()
{
   QFile file;
   PListReader reader;
       file.setFileName(":/config/TowersPosition.plist");
       if (!file.open(QFile::ReadOnly | QFile::Text))
          {
              QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
              return;
          }
   reader.read(&file);

   QList<QVariant> array = reader.data();
   foreach (QVariant dict, array)
   {
       QMap<QString, QVariant> point = dict.toMap();
       int x = point.value("x").toInt();
       int y = point.value("y").toInt();
       //TowerPosition *Position = new TowerPosition(QPoint(x,y), NULL, QPixmap(":/image/open_spot.png"));
       m_towerPositionsList.push_back(QPoint(x,y));
   }
   file.close();
}
void GameWindow::paintEvent(QPaintEvent *)
{
    const QPixmap pix(":/image/chizu.1.png");

       QPainter painter(this);
       painter.drawPixmap(0,0,pix);

       foreach (const Tower *tower, m_towersList)
           tower->draw(&painter);

       foreach (const TowerPosition &towerPos, m_towerPositionsList)
           towerPos.draw(&painter);

       foreach (const WayPoint *wayPoint, m_wayPointsList)
           wayPoint->draw(&painter);
       drawWave(&painter);
       drawHP(&painter);
       drawPlayerGold(&painter);
       drawCustom(&painter);

}
void GameWindow::doGameOver()
{
   if (!m_gameEnded)
   {
       m_lost->play();

       m_gameEnded = true;
       this->hide();
   }
}

void GameWindow::removedEnemy(Enemy *enemy)
{
   Q_ASSERT(enemy);

   m_enemyList.removeOne(enemy);
   delete enemy;
}
void GameWindow::getHpDamage(int damage/* = 1*/)
{
   m_lostlife->play();

   m_playerHp -= damage;
   if (m_playerHp <= 0){
       doGameOver();
   }
}
void GameWindow::removeTower(Tower *tower){
   Q_ASSERT(tower);

   m_towerPositionsList[m_position].setHasnoTower();
   m_towersList.removeOne(tower);
   delete tower;
}

void GameWindow::removedBullet(Bullet *bullet)
{
   Q_ASSERT(bullet);

   m_bulletList.removeOne(bullet);
   delete bullet;
}

void GameWindow::addBullet(Bullet *bullet)
{
   Q_ASSERT(bullet);

   m_bulletList.push_back(bullet);
}
void GameWindow::addWayPoints()
{

       WayPoint *wayPoint1 = new WayPoint(QPoint(1030, 416));
       m_wayPointsList.push_back(wayPoint1);

       WayPoint *wayPoint2 = new WayPoint(QPoint(736, 416));
       m_wayPointsList.push_back(wayPoint2);
       wayPoint2->setNextWayPoint(wayPoint1);

       WayPoint *wayPoint3 = new WayPoint(QPoint(736, 224));
       m_wayPointsList.push_back(wayPoint3);
       wayPoint3->setNextWayPoint(wayPoint2);

       WayPoint *wayPoint4 = new WayPoint(QPoint(608,224));
       m_wayPointsList.push_back(wayPoint4);
       wayPoint4->setNextWayPoint(wayPoint3);

       WayPoint *wayPoint5 = new WayPoint(QPoint(608, 672));
       m_wayPointsList.push_back(wayPoint5);
       wayPoint5->setNextWayPoint(wayPoint4);

       WayPoint *wayPoint6 = new WayPoint(QPoint(224,672));
       m_wayPointsList.push_back(wayPoint6);
       wayPoint6->setNextWayPoint(wayPoint5);

       WayPoint *wayPoint7 = new WayPoint(QPoint(224,480));
       m_wayPointsList.push_back((wayPoint7));
       wayPoint7->setNextWayPoint(wayPoint6);

       WayPoint *wayPoint8 = new WayPoint(QPoint(416,480));
       m_wayPointsList.push_back((wayPoint8));
       wayPoint8->setNextWayPoint(wayPoint7);

       WayPoint *wayPoint9 = new WayPoint(QPoint(416,224));
       m_wayPointsList.push_back((wayPoint9));
       wayPoint9->setNextWayPoint(wayPoint8);

       WayPoint *wayPoint10 = new WayPoint(QPoint(96,224));
       m_wayPointsList.push_back((wayPoint10));
       wayPoint10->setNextWayPoint(wayPoint9);

       WayPoint *wayPoint11 = new WayPoint(QPoint(96,352));
       m_wayPointsList.push_back((wayPoint11));
       wayPoint11->setNextWayPoint(wayPoint10);

       WayPoint *wayPoint12 = new WayPoint(QPoint(224,352));
       m_wayPointsList.push_back((wayPoint12));
       wayPoint12->setNextWayPoint(wayPoint11);

       WayPoint *wayPoint13 = new WayPoint(QPoint(224,96));
       m_wayPointsList.push_back((wayPoint13));
       wayPoint13->setNextWayPoint(wayPoint12);

       WayPoint *wayPoint14 = new WayPoint(QPoint(32,96));
       m_wayPointsList.push_back((wayPoint14));
       wayPoint14->setNextWayPoint(wayPoint13);
   }
void GameWindow::drawWave(QPainter *painter)
{
   painter->setPen(QPen(Qt::white));
   painter->drawText(QRect(500, 5, 100, 35), QString("WAVE : %1 / ").arg(m_waves + 1));
}

void GameWindow::drawHP(QPainter *painter)
{
   painter->setPen(QPen(Qt::white));
   painter->drawText(QRect(100, 5, 100, 35), QString("HP : %1").arg(m_playerHp));
   const QPixmap gold = QPixmap(":/image/icon_HP.png");
   painter->drawPixmap(75, 3, gold);
}

void GameWindow::drawPlayerGold(QPainter *painter)
{
   painter->setPen(QPen(Qt::white));
   painter->drawText(QRect(300, 5, 200, 35), QString("GOLD : %1 / ").arg(m_playerGold));
   const QPixmap gold = QPixmap(":/image/icon_gold.png");
   painter->drawPixmap(275, 3, gold);
}

void GameWindow::drawCustom(QPainter *painter){
    painter->setPen(QPen(Qt::white));
    painter->drawText(QRect(700, 5, 200, 35), QString("CUSTOM : %1").arg(m_custom));
}
void GameWindow::game_show(){
    this->show();
}
QList<Enemy *> GameWindow::enemyList() const
{
   return m_enemyList;
}
