#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "gamewindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(35, 35);

Tower::Tower(QPoint pos, GameWindow *game, const QPixmap &sprite_1, const QPixmap &sprite_2, const QPixmap &sprite_3,
             const QPixmap &bullet_1, const QPixmap &bullet_2, const QPixmap &bullet_3)
    : m_attacking(false)
    , m_candizzied(false)
    , m_canfroze(false)
    , m_attackRange(70)
    , m_damage(10)
    , m_fireRate(1000)
    , m_level(1)
    , m_rotationSprite(0.0)
    , m_game(game)
    , m_chooseEnemy(NULL)
    , m_pos(pos)
    , m_sprite_1(sprite_1)
    , m_sprite_2(sprite_2)
    , m_sprite_3(sprite_3)
    , m_bullet_1(bullet_1)
    , m_bullet_2(bullet_2)
    , m_bullet_3(bullet_3)
    , m_cost(300)
    , m_levelCost1(150)
    , m_levelCost2(200)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

}



Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) ;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter *painter) const
{
    if(m_level == 1){
        painter->save();
        painter->setPen(Qt::white);
        // 绘制攻击范围
        painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
        // 绘制偏转坐标,由中心+偏移=左上
        QPoint offsetPoint(-m_sprite_1.width() /2, -m_sprite_1.height() /2);
        // 绘制炮塔并选择炮塔
        painter->translate(m_pos);
        painter->rotate(m_rotationSprite);
        painter->drawPixmap(offsetPoint, m_sprite_1);
        painter->restore();
    }else if(m_level == 2){
        painter->save();
        painter->setPen(Qt::white);
        painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
        QPoint offsetPoint(-m_sprite_2.width() /2, -m_sprite_2.height() /2);
        painter->translate(m_pos);
        painter->rotate(m_rotationSprite);
        painter->drawPixmap(offsetPoint, m_sprite_2);
        painter->restore();
    }else if(m_level == 3){
        painter->save();
        painter->setPen(Qt::white);
        painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
        QPoint offsetPoint(-m_sprite_3.width() /2, -m_sprite_3.height() /2);
        painter->translate(m_pos);
        painter->rotate(m_rotationSprite);
        painter->drawPixmap(offsetPoint, m_sprite_3);
        painter->restore();
    }
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    if(m_level == 1){
        Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, m_bullet_1);
        bullet->move();
        m_game->addBullet(bullet);
    }else if(m_level == 2){
        Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, m_bullet_2);
        bullet->move();
        m_game->addBullet(bullet);
    }else if(m_level == 3){
        Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, m_bullet_3);
        bullet->move();
        m_game->addBullet(bullet);
    }


}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}
int  Tower::getlevel(){
    return this->m_level;
}
int Tower::getAttackRange(){
    return m_attackRange;
}
int Tower::getLevelCost1(){
    return this->m_levelCost1;
}
int Tower::getLevelCost2(){
    return this->m_levelCost2;
}
int Tower::getCost(){
    return this->m_cost;
}

