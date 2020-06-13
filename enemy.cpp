#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "gamewindow.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QMediaPlayer>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include <QMediaPlayer>
#define random(x) rand()%(x)

static const int Health_Bar_Width = 40;
static const int bossHealth_Bar_Width = 100;

const QSize Enemy::ms_fixedSize(52, 52);
const QSize Enemy::ms_bossfixedSize(94, 84);

Enemy::Enemy(WayPoint *startWayPoint, GameWindow *game, const QImage &sprite/* = QMoive(":/image/monster.png")*/)
    : QObject(0)
    , m_active(false)
    , m_dizzied(false)
    , m_frozed(false)
    , m_isboss(false)
    , m_maxHp(100)
    , m_currentHp(100)
    , m_walkingSpeed(2.0)
    , m_originSpeed(2.0)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
    , dizzied(0)
    , frozed(0)
    , m_enemydestroy(new QMediaPlayer(this))
{
       m_enemydestroy->setMedia(QUrl("qrc:/music/enemy_destroy.wav"));
       m_enemydestroy->setVolume(100);
}

Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    if(targetPoint.rx() - m_pos.rx() < 0){
        QImage mirroredImage = m_sprite.mirrored(true, false);
        m_sprite_0 = QPixmap::fromImage(mirroredImage);
    }else {
        QImage mirroredImage = m_sprite.mirrored(false, false);
        m_sprite_0 = QPixmap::fromImage(mirroredImage);
    }

    m_pos = m_pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    //m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 90;
}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint;
    if(m_isboss)healthBarPoint = m_pos + QPoint(-bossHealth_Bar_Width/2 , -ms_bossfixedSize.height()/2);
    else healthBarPoint = m_pos + QPoint(-Health_Bar_Width/2 , -ms_fixedSize.height()/2);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect;
    if(m_isboss)healthBarBackRect = QRect(healthBarPoint, QSize(bossHealth_Bar_Width, 8));
    else healthBarBackRect = QRect(healthBarPoint, QSize(Health_Bar_Width, 4));
    painter->drawRect(healthBarBackRect);

    if(m_dizzied)painter->drawPixmap(healthBarPoint.rx() - 25, healthBarPoint.ry() - 50, 80, 80,QPixmap(":/image/dizzied.png"));

    painter->setBrush(Qt::green);
    QRect healthBarRect;
    if(m_isboss)healthBarRect = QRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * bossHealth_Bar_Width, 8));
    else healthBarRect = QRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 4));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    QPoint offsetPoint;
    if(m_isboss)offsetPoint = QPoint(-ms_bossfixedSize.width() / 2, -ms_bossfixedSize.height() / 2);
    else offsetPoint = QPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite_0);

    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    if(m_frozed)painter->drawPixmap(-25, 0, 50, 50,QPixmap(":/image/frozed.png"));

    painter->restore();
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;
    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}
void Enemy::getDamage1(int damage){
    m_currentHp-=damage;

}
void Enemy::getDamage(int damage)
{
    m_enemydestroy->play();

    m_currentHp -= damage;
    QPoint offp(m_pos.rx()-ms_fixedSize.width() / 2,m_pos.ry()-ms_fixedSize.width() / 2);
    if(damage==50||damage==70||damage==90){
        m_game->aoe(offp,damage);
        m_game->showeffect(offp,damage);
    }
    // 阵亡,需要移除

    // 阵亡,需要移除
        srand((int)time(0));
        int n=random(11);


        foreach (Tower *tower, m_attackedTowersList) {
            if(tower->m_candizzied){
                if(damage==40&&n<=3){
                m_dizzied = true;
                dizzied=1;
                }
                if(damage==60&&n<=5){
                m_dizzied = true;
                dizzied=2;
                }
                if(damage==80&&n<=6){
                m_dizzied = true;
                dizzied=3;
                }
            }
            if(tower->m_canfroze){
                if(damage==30){
                m_frozed = true;
                frozed=1;
                }
                if(damage==41){
                m_frozed = true;
                frozed=2;
                }
                if(damage==51){
                m_frozed = true;
                frozed=3;
                }
            }
        }
        if(m_dizzied){
            m_walkingSpeed = 0;
            if(dizzied==1)
            QTimer::singleShot(400, this, SLOT(releasedizzied()));
            if(dizzied==2)
            QTimer::singleShot(600, this, SLOT(releasedizzied()));
            if(dizzied==3)
            QTimer::singleShot(800, this, SLOT(releasedizzied()));
        }
        if(m_frozed){
            if(frozed==1){
            m_walkingSpeed = m_originSpeed *0.7;
            QTimer::singleShot(600,this,SLOT(releasefrozed()));
            }
            if(frozed==2){
            m_walkingSpeed = m_originSpeed *0.6;
            QTimer::singleShot(1100,this,SLOT(releasefrozed()));
            }
            if(frozed==3){
            m_walkingSpeed = m_originSpeed *0.5;
            QTimer::singleShot(1600,this,SLOT(releasefrozed()));
            }
        }



    if (m_currentHp <= 0)
    {
        m_enemydestroy->play();

        m_game->awardGold(200);
        m_game->showdeadenemy(offp,m_sprite_0);
        getRemoved();
    }
}

void Enemy::releasedizzied(){
    m_dizzied = false;
    dizzied=0;
    takeorigin();
}

void Enemy::releasefrozed(){
    m_frozed = false;
    frozed=0;
    takeorigin();
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint Enemy::pos() const
{
    return m_pos;
}

void Enemy::takeorigin(){
    if(m_currentHp >= m_maxHp)m_currentHp = 100;
    m_maxHp = 100;
    m_walkingSpeed = 3.0;
    m_originSpeed = 3.0;
}
