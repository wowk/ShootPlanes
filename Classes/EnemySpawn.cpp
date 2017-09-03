#include "EnemySpawn.h"
#include "Enemy.h"

USING_NS_CC;

EnemySpawn::EnemySpawn()
{
    m_spawnMinSpeed = 600;
    m_spawnMaxSpeed = 2000;
    m_lastSpawnTime = 0;
}

void EnemySpawn::spawn(float delta)
{
    struct {
        Enemy::EnemyType type;
        float damage;
        float speed;
        float dir;
    } enemyList[]{
        {Enemy::EnemyType::Small, 20.0f, 200 + rand() % 50, M_PI * 1.5},
        {Enemy::EnemyType::Miedum, 50.0f, 100 + rand() % 50, M_PI * 1.5},
        {Enemy::EnemyType::Big, 200.0f, 50 + rand() % 50, M_PI * 1.5},
    };

    int enemyIndex = 0;
    int randNum= rand() + 300;
    if( randNum % 9 == 0 ){
        enemyIndex = 1;
    }else if( randNum % 17 == 0 ){
        enemyIndex = 2;
    }

    Enemy* enemy = Enemy::create(
                enemyList[enemyIndex].type,
                enemyList[enemyIndex].speed,
                enemyList[enemyIndex].damage,
                enemyList[enemyIndex].dir);
    enemy->setLocalZOrder(getLocalZOrder());
    getParent()->addChild(enemy);
    enemy->scheduleUpdate();
}
