#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "EnemySpawn.h"
#include "ScoreSprite.h"
#include "cocos2d.h"
#include "BackgroundSprite.h"
#include <list>


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void update(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void loadResource();

    void onMenuItemCallback(cocos2d::Ref* pSender);

private:
    BackgroundNode* bgSprite;
    Player* player;
    EnemySpawn* enemySpawn;
    ScoreSprite* score;
    cocos2d::Menu* menu;
};

#endif // __HELLOWORLD_SCENE_H__
