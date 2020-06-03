#include "gamewindow.h"
#include "ui_gamewindow.h"
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
    ,ui(new Ui::GameWindow)
    , m_waves(0)
    , m_playerHp(5)
    , m_playerGold(4000)
    , m_position(0)
    , m_custom(1){
    ui->setupUi(this);
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
void GameWindow::paintEvent(QPaintEvent *)
{
    const QPixmap pix(":/image/chizu.1.png");
    const QPixmap pix1(":/image/chizu.2.png");
       QPainter painter(this);
       painter.drawPixmap(0,0,pix);
       drawWave(&painter);
       drawHP(&painter);
       drawPlayerGold(&painter);
       drawCustom(&painter);

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
