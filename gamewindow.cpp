#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "tighttowerposi.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QDateTime>
#include <QCoreApplication>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <math.h>

static const int TowerCost = 300;

GameWindow::GameWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::GameWindow)
   , m_waves(0)
   , m_playerHp(5)
   , m_playerGold(4000)
   , m_gameEnded(false)
   , m_gameWin(false)
   , m_iscruel(false)
   , m_tighter(NULL)
   , m_posi(NULL)
   , m_position(0)
   , m_custom(1)
   , m_label(new QLabel(this))
   , m_boom(new QLabel(this))
{
   ui->setupUi(this);
   preLoadWavesInfo();
   loadTowerPositions();
   addWayPoints();

   button_gameoff = new QPushButton(this);
   button_home = new QPushButton(this);
   button_boom = new QPushButton(this);
   button_cruelty = new QPushButton(this);
   button_firerateup = new QPushButton(this);

   button_home->setGeometry(QRect(850,20,70,70));
   button_home->setIcon(QIcon(QPixmap(":/image/uchi.png")));
   button_home->setIconSize(QSize(60,60));
   button_home->setFlat(true);

   button_gameoff->setGeometry(QRect(950,20,70,70));
   button_gameoff->setIcon(QIcon(QPixmap(":/image/close.png")));
   button_gameoff->setIconSize(QSize(60,60));
   button_gameoff->setFlat(true);

   button_boom->setGeometry(QRect(940,90,70,70));
   button_boom->setIcon(QIcon(QPixmap(":/image/booming.png")));
   button_boom->setIconSize(QSize(60,60));
   button_boom->setFlat(true);

   button_cruelty->setGeometry(QRect(940,160,70,70));
   button_cruelty->setIcon(QIcon(QPixmap(":/image/crazy.png")));
   button_cruelty->setIconSize(QSize(60,60));
   button_cruelty->setFlat(true);

   button_firerateup->setGeometry(QRect(940,230,70,70));
   button_firerateup->setIcon(QIcon(QPixmap(":/image/firerateup.png")));
   button_firerateup->setIconSize(QSize(60,60));
   button_firerateup->setFlat(true);

   connect(button_home,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_home_clicked()));
   connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_gameoff_clicked()));
   connect(button_boom,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_boom_clicked()));
   connect(button_cruelty,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_cruelty_clicked()));
   connect(button_firerateup,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_rateup_clicked()));

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


   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));

   timer->start(30);

}

GameWindow::~GameWindow()
{
   delete ui;
}

void GameWindow::loadTowerPositions()
{
   QFile file;
   PListReader reader;
   if(m_custom == 1)
   {
       file.setFileName(":/config/TowersPosition.plist");
       if (!file.open(QFile::ReadOnly | QFile::Text))
          {
              QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
              return;
          }
   }else if(m_custom == 2){
       file.setFileName(":/config/TowersPosition2.plist");
       if (!file.open(QFile::ReadOnly | QFile::Text))
          {
              QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition2.plist");
              return;
          }
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
    const QPixmap pix1(":/image/chizu.2.png");
   if(m_custom == 1){
       QPainter painter(this);
       painter.drawPixmap(0,0,pix);

       foreach (const TowerPosition &towerPos, m_towerPositionsList)
           towerPos.draw(&painter);

       foreach (const Tower *tower, m_towersList)
           tower->draw(&painter);

       foreach (const WayPoint *wayPoint, m_wayPointsList)
           wayPoint->draw(&painter);

       foreach (const Enemy *enemy, m_enemyList)
           enemy->draw(&painter);

       foreach (const Bullet *bullet, m_bulletList)
           bullet->draw(&painter);

       drawWave(&painter);
       drawHP(&painter);
       drawPlayerGold(&painter);
       drawCustom(&painter);
   }else if(m_custom == 2){
       QPainter painter(this);
       painter.drawPixmap(0,0,pix1);

       foreach (const TowerPosition &towerPos, m_towerPositionsList)
           towerPos.draw(&painter);

       foreach (const Tower *tower, m_towersList)
           tower->draw(&painter);

       foreach (const WayPoint *wayPoint, m_wayPointsList)
           wayPoint->draw(&painter);

       foreach (const Enemy *enemy, m_enemyList)
           enemy->draw(&painter);

       foreach (const Bullet *bullet, m_bulletList)
           bullet->draw(&painter);

       drawWave(&painter);
       drawHP(&painter);
       drawPlayerGold(&painter);
       drawCustom(&painter);
   }
}
void GameWindow::aoe(QPoint &p, int damage){
    foreach(Enemy *enemy,m_enemyList){
        QPoint a=enemy->pos();
        double dis=sqrt((double)(pow(a.rx()-p.rx(),2))+(double)(pow(a.ry()-p.ry(),2)));
        if(dis<50&&dis>0.1){
            enemy->getDamage1(30);
        }
        delete &a;
        delete &dis;
    }
}


void GameWindow::showeffect(QPoint &p,int damage){
    QLabel *m=new QLabel(this);
    if(damage==50)
    m->setPixmap(QPixmap(":/image/turret_effect1.png"));
    if(damage==70)
    m->setPixmap(QPixmap(":/image/turret_effect2.png"));
    if(damage==90)
    m->setPixmap(QPixmap(":/image/turret_effect3.png"));
    m->setGeometry(p.rx(),p.ry(),60,85);
    m->show();
    m_QLabelList.prepend(m);
    QTimer::singleShot(500,this,SLOT(hideeffect()));
}
void GameWindow::hideeffect(){
    QLabel *m = new QLabel(this);
    m = m_QLabelList.takeLast();
    m->hide();
    delete m;
}
void GameWindow::showdeadenemy(QPoint &p, QPixmap &m1){
    QLabel *m = new QLabel(this);
    m->setPixmap(m1);
    m->setGeometry(p.rx(),p.ry(),60,85);
    m->show();
    m_QLabelList1.prepend(m);
      QGraphicsOpacityEffect* m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(m);
       m_pGraphicsOpacityEffect->setOpacity(1);
       m->setGraphicsEffect(m_pGraphicsOpacityEffect);
       QPropertyAnimation* m_pNameAnimation = new QPropertyAnimation(m_pGraphicsOpacityEffect,"opacity",this);
       m_pNameAnimation->setEasingCurve(QEasingCurve::Linear);
       m_pNameAnimation->setDuration(2500);
       m_pNameAnimation->setStartValue(1);
       m_pNameAnimation->setEndValue(0);
       m_pNameAnimation->start(QAbstractAnimation::KeepWhenStopped);
       m_QLabelList1.takeLast();

       delete m;
       delete m_pNameAnimation;
}


void GameWindow::mousePressEvent(QMouseEvent *event)
{
   QPoint pressPos = event->pos();
   auto it = m_towerPositionsList.begin();
   while (it != m_towerPositionsList.end())
   {
       if (it->containPoint(pressPos) && !it->hasTower())
       {
           for(int i=0;i<m_towerPositionsList.size();i++){
               if(m_towerPositionsList[i].getPos() == it->getPos()){
                   m_posi = i;
               }
           }
           create_construct_Menu();
           m_menu_construct->popup(event->globalPos());
           m_menu_construct->exec(QCursor().pos());
           break;
       }
       else if(it->hasTower() && it->containPoint(pressPos) ){
           for(int i=0;i<m_towerPositionsList.size();i++){
               if(m_towerPositionsList[i].getPos() == it->getPos()){
                   m_position = i;
               }
           }

           auto subit = m_TightTowerPosiList.begin();
           while (subit != m_TightTowerPosiList.end()){
               TightTowerPosi *it_1 = *subit;
               if(it_1->containPoint(pressPos)){
                   m_tighter = it_1;
                   create_lere_Menu();
                   m_menu_lere->popup(event->globalPos());
                   m_menu_lere->exec(QCursor().pos());
                   break;
               }
               ++subit;
           }
       }
       ++it;
   }
}

bool GameWindow::canBuyTower() const
{
   if (m_playerGold >= TowerCost)
       return true;
   return false;
}

void GameWindow::drawWave(QPainter *painter)
{
   painter->setPen(QPen(Qt::white));
   painter->drawText(QRect(500, 5, 100, 35), QString("WAVE : %1 / ").arg(m_waves + 1) + QString("%1").arg(m_wavesInfo.size()));
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

void GameWindow::doGameOver()
{
   if (!m_gameEnded)
   {
       m_lost->play();

       m_gameEnded = true;
       this->hide();
       emit showlostwindow();
   }
}

void GameWindow::awardGold(int gold)
{
   m_playerGold += gold;
   update();
}


void GameWindow::addWayPoints()
{
   if(m_custom == 1){
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
   }else if(m_custom == 2){
       WayPoint *wayPoint1 = new WayPoint(QPoint(544, 352));
       m_wayPointsList.push_back(wayPoint1);

       WayPoint *wayPoint2 = new WayPoint(QPoint(480, 352));
       m_wayPointsList.push_back(wayPoint2);
       wayPoint2->setNextWayPoint(wayPoint1);

       WayPoint *wayPoint3 = new WayPoint(QPoint(480, 480));
       m_wayPointsList.push_back(wayPoint3);
       wayPoint3->setNextWayPoint(wayPoint2);

       WayPoint *wayPoint4 = new WayPoint(QPoint(672,480));
       m_wayPointsList.push_back(wayPoint4);
       wayPoint4->setNextWayPoint(wayPoint3);

       WayPoint *wayPoint5 = new WayPoint(QPoint(672, 224));
       m_wayPointsList.push_back(wayPoint5);
       wayPoint5->setNextWayPoint(wayPoint4);

       WayPoint *wayPoint6 = new WayPoint(QPoint(352,224));
       m_wayPointsList.push_back(wayPoint6);
       wayPoint6->setNextWayPoint(wayPoint5);

       WayPoint *wayPoint7 = new WayPoint(QPoint(352,608));
       m_wayPointsList.push_back((wayPoint7));
       wayPoint7->setNextWayPoint(wayPoint6);

       WayPoint *wayPoint8 = new WayPoint(QPoint(800,608));
       m_wayPointsList.push_back((wayPoint8));
       wayPoint8->setNextWayPoint(wayPoint7);

       WayPoint *wayPoint9 = new WayPoint(QPoint(800,96));
       m_wayPointsList.push_back((wayPoint9));
       wayPoint9->setNextWayPoint(wayPoint8);

       WayPoint *wayPoint10 = new WayPoint(QPoint(224,96));
       m_wayPointsList.push_back((wayPoint10));
       wayPoint10->setNextWayPoint(wayPoint9);

       WayPoint *wayPoint11 = new WayPoint(QPoint(224,352));
       m_wayPointsList.push_back((wayPoint11));
       wayPoint11->setNextWayPoint(wayPoint10);

       WayPoint *wayPoint12 = new WayPoint(QPoint(32,352));
       m_wayPointsList.push_back((wayPoint12));
       wayPoint12->setNextWayPoint(wayPoint11);

   }

}



void GameWindow::getHpDamage(int damage/* = 1*/)
{
   m_lostlife->play();

   m_playerHp -= damage;
   if (m_playerHp <= 0){
       doGameOver();
   }
}

void GameWindow::removedEnemy(Enemy *enemy)
{
   Q_ASSERT(enemy);

   m_enemyList.removeOne(enemy);
   delete enemy;

   if (m_enemyList.empty() && m_playerHp > 0)
   {
       ++m_waves;
       if (!loadWave())
       {
           m_win->play();

           m_gameWin = true;
           this->hide();
           if(m_custom == 1)emit showmiddlewindow();
           else if(m_custom == 2)emit showwinwindow();
       }
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

void GameWindow::updateMap()
{
   foreach (Enemy *enemy, m_enemyList)
       enemy->move();
   foreach (Tower *tower, m_towersList)
       tower->checkEnemyInRange();
   update();
}

void GameWindow::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    QFile file2(":/config/Waves2.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }
    if (!file2.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }
    PListReader reader;
    if(m_custom == 1)reader.read(&file);
    else if(m_custom ==2)reader.read(&file2);
    m_wavesInfo = reader.data();
    file.close();
    file2.close();
}

bool GameWindow::loadWave()
{
   if (m_waves >= m_wavesInfo.size())
       return false;

   WayPoint *startWayPoint = m_wayPointsList.back();
   QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

   for (int i = 0; i < curWavesInfo.size(); ++i)
   {
       QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
       int spawnTime = dict.value("spawnTime").toInt();

       if(dict.value("type") == "singlecado"){
           Enemy *enemy = new singlecado(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "enemy"){
           Enemy *enemy = new Enemy(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "guai"){
           Enemy *enemy = new guai(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "shou"){
           Enemy *enemy = new shou(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "boss"){
           Enemy *enemy = new boss(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }else if(dict.value("type") == "bigboss"){
           Enemy *enemy = new bigboss(startWayPoint, this);
           m_enemyList.push_back(enemy);
           if(m_iscruel){
               enemy->m_maxHp *= 1.5;
               enemy->m_currentHp *= 1.5;
               enemy->m_walkingSpeed *= 1.5;
               enemy->m_originSpeed *= 1.5;
           }
           QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
       }
   }

   return true;
}

QList<Enemy *> GameWindow::enemyList() const
{
   return m_enemyList;
}

void GameWindow::gameStart()
{
   loadWave();
}

void GameWindow::create_construct_Menu(){
    m_menu_construct = new QMenu(this);

   m_menu_construct->setSizeIncrement(QSize(100,80));
   QString str;

   barbette = new QAction(m_menu_construct);
   Barbette *bar = new Barbette(QPoint(0,0),this);
   str = QString("%1").arg(bar->getCost());
   barbette->setText("Barbette $ " + str);
   barbette->setIcon(QPixmap(":/image/barbette_1.png"));
   delete bar;

   heavyplane = new QAction(m_menu_construct);
   Heavyplane *heavy = new Heavyplane(QPoint(0,0),this);
   str = QString("%1").arg(heavy->getCost());
   heavyplane->setText("Heavyplane $ "+ str);
   heavyplane->setIcon(QPixmap(":/image/heavyplane_1.png"));
   delete heavy;

   warship = new QAction(m_menu_construct);
   Warship *war = new Warship(QPoint(0,0),this);
   str = QString("%1").arg(war->getCost());
   warship->setText("Warship $ " + str);
   warship->setIcon(QPixmap(":/image/warship_1.png"));
   delete war;

   tank = new QAction(m_menu_construct);
   Tank *ta = new Tank(QPoint(0,0),this);
   str = QString("%1").arg(ta->getCost());
   tank->setText("Tank $ " + str);
   tank->setIcon(QPixmap(":/image/tank_1.png"));
   delete ta;

   m_menu_construct->addAction(barbette);
   m_menu_construct->addAction(tank);
   m_menu_construct->addAction(heavyplane);
   m_menu_construct->addAction(warship);


   connect(barbette,SIGNAL(triggered()),this,SLOT(construct_barbette()));
   connect(heavyplane,SIGNAL(triggered()),this,SLOT(construct_heavyplane()));
   connect(warship,SIGNAL(triggered()),this,SLOT(construct_warship()));
   connect(tank,SIGNAL(triggered()),this,SLOT(construct_tank()));

}

void GameWindow::create_lere_Menu(){
    m_menu_lere = new QMenu(this);
    levelup = new QAction(m_menu_lere);
    QString str;
    if(m_tighter->getTower()->getlevel() == 1)str = QString("%1").arg(m_tighter->getTower()->getLevelCost1());
    else if(m_tighter->getTower()->getlevel() == 2)str = QString("%1").arg(m_tighter->getTower()->getLevelCost2());

    levelup->setText("Upgrate $ "+str);
    levelup->setIcon(QPixmap(":/image/level_up.png"));

    remove = new QAction(m_menu_lere);
    if(m_tighter->getTower()->getlevel() == 1)str = QString("%1").arg(m_tighter->getTower()->getCost() - 100);
    else if(m_tighter->getTower()->getlevel() == 2)str = QString("%1").arg(m_tighter->getTower()->getLevelCost1() + m_tighter->getTower()->getCost() - 200);
    else if(m_tighter->getTower()->getlevel() == 3)str = QString("%1").arg(m_tighter->getTower()->getLevelCost2() + m_tighter->getTower()->getLevelCost1() + m_tighter->getTower()->getCost() - 300);
    remove->setText("Sell $ " + str);
    remove->setIcon(QPixmap(":/image/remove.png"));

    m_menu_lere->addAction(levelup);
    m_menu_lere->addAction(remove);

    connect(levelup,SIGNAL(triggered()),this,SLOT(action_levelup()));
    connect(remove,SIGNAL(triggered()),this,SLOT(action_remove()));
}

void GameWindow::construct_heavyplane(){
   Tower *tower = new Heavyplane(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       m_towerplace->play();

       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}

void GameWindow::construct_warship(){
   Tower *tower = new Warship(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       m_towerplace->play();

       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}

void GameWindow::construct_barbette(){
   Tower *tower = new Barbette(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       m_towerplace->play();
       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}

void GameWindow::construct_tank(){
   Tower *tower = new Tank(m_towerPositionsList[m_posi].centerPos(), this);
   if (m_playerGold >= tower->getCost())
   {
       m_towerplace->play();

       m_playerGold -= tower->getCost();
       m_towerPositionsList[m_posi].setHasTower();

       TightTowerPosi *tight = new TightTowerPosi(m_towerPositionsList[m_posi].getPos(), tower, this);
       m_towersList.push_back(tower);
       m_TightTowerPosiList.push_back(tight);
       update();
       return ;
   }
   m_menu_construct->exec();
}


void GameWindow::action_levelup(){
   if(m_tighter->getTower()->getlevel() < 3){
       if(m_tighter->getTower()->getlevel() == 1 && m_playerGold >= m_tighter->getTower()->getLevelCost1()){
           m_playerGold -= m_tighter->getTower()->getLevelCost1();
           m_tighter->getTower()->levelup();

           m_towerplace->play();

           update();
           return;

       }
       else if(m_tighter->getTower()->getlevel() == 2 && m_playerGold >= m_tighter->getTower()->getLevelCost2()){
           m_playerGold -= m_tighter->getTower()->getLevelCost2();
           m_tighter->getTower()->levelup();

           m_towerplace->play();

           update();
           return;
       }
       m_menu_lere->exec();
   }
}

void GameWindow::action_remove(){
   if(m_TightTowerPosiList.indexOf(m_tighter) < 0){return;}
   else if(m_tighter->getTower()->getlevel() == 1){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getCost() -100;
       m_TightTowerPosiList.removeOne(m_tighter);
       update();
       return ;
   }
   else if(m_tighter->getTower()->getlevel() == 2){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getLevelCost1() + m_tighter->getTower()->getCost() -200;
       m_TightTowerPosiList.removeOne(m_tighter);
       update();
       return;
   }
   else if(m_tighter->getTower()->getlevel() == 3){
       removeTower(m_tighter->getTower());
       m_playerGold += m_tighter->getTower()->getLevelCost2() + m_tighter->getTower()->getLevelCost1() +m_tighter->getTower()->getCost()- 300;
       m_TightTowerPosiList.removeOne(m_tighter);
       update();
       return ;
   }
   m_menu_lere->exec();
}

void GameWindow::on_pushbutton_home_clicked(){
    this->hide();
    emit gobackhome();
}

void GameWindow::on_pushbutton_gameoff_clicked(){
    this->hide();
    emit quit();
}

void GameWindow::on_pushbutton_boom_clicked(){
    if(m_playerGold >= 1000){
        boomeffect();
        foreach (Enemy *enemy, m_enemyList){
            if(enemy->m_active && !enemy->m_isboss)removedEnemy(enemy);
            if(enemy->m_active && enemy->m_isboss){
                enemy->m_currentHp /= 4;
                enemy->m_currentHp *= 3;
            }
        }
        foreach (Tower *tower, m_towersList) {
            tower->m_fireRateTimer->stop();
            tower->m_chooseEnemy = NULL;
            tower->m_rotationSprite = 0.0;
        }
        m_playerGold -=1000;
    }
    return ;
}

void GameWindow::boomeffect(){
    m_booming->play();

    m_boom->setPixmap(QPixmap(":/image/boom.png"));
    m_boom->setGeometry(237,109,550,550);
    m_boom->show();
    QTimer::singleShot(300,this,SLOT(hideboom()));
    return ;
}

void GameWindow::hideboom(){
    m_boom->hide();
}

void GameWindow::on_pushbutton_cruelty_clicked(){
    if(!m_iscruel){
        m_iscruel = true;
        foreach (Enemy * enemy, m_enemyList) {
            enemy->m_currentHp *= 1.5;
            enemy->m_maxHp *= 1.5;
            enemy->m_walkingSpeed *= 1.5;
            enemy->m_originSpeed *= 1.5;
        }
    }else if(m_iscruel){
        m_iscruel = false;
        foreach (Enemy * enemy, m_enemyList) {
            enemy->takeorigin();
        }
    }
}

void GameWindow::on_pushbutton_rateup_clicked(){
    if(m_playerGold >= 500){
        m_playerGold -= 500;
        foreach (Tower *tower, m_towersList) {
            tower->m_fireRate /= 2.0;
        }
        QTimer::singleShot(3000,this,SLOT(cover()));
    }

}

void GameWindow::cover(){
    foreach (Tower *tower, m_towersList) {
        tower->m_fireRate *= 2.0;
    }
}
void GameWindow::main_show(){
    m_custom = 1;
    reset();
    this->show();
    gameStart();
}

void GameWindow::restart(){
    reset();
    this->show();
    gameStart();
}

void GameWindow::reset(){
    m_enemyList.clear();
    m_QLabelList.clear();
    m_QLabelList1.clear();
    m_bulletList.clear();
    m_towerPositionsList.clear();
    m_wavesInfo.clear();
    m_wayPointsList.clear();
    m_TightTowerPosiList.clear();
    m_towersList.clear();
    m_waves = 0;
    m_playerGold = 4000;
    m_playerHp = 5;
    m_gameEnded = false;
    m_gameWin = false;
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();
}

void GameWindow::custom_up(){
    m_custom = 2;
    reset();
    this->show();
    gameStart();
}



