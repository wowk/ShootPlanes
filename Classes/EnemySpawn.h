#ifndef __ENEMY_SPAWN_H__
#define __ENEMY_SPAWN_H__

#include "cocos2d.h"
#include "Enemy.h"


class EnemySpawn : public cocos2d::Node {
public:
    CREATE_FUNC(EnemySpawn);
    void spawn(float delta);

private:
    EnemySpawn();
    int m_spawnMinSpeed;  //ms
    int m_spawnMaxSpeed;  //ms
    int m_lastSpawnTime;  //ms
};

#endif//__ENEMY_SPAWN_H__
