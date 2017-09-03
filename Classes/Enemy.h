#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Node {
public:
    enum EnemyType {Small, Miedum, Big};
    static Enemy* create(Enemy::EnemyType type, float speed, float damage, float dir)
    {
        Enemy* pRet = new(std::nothrow) Enemy(type, speed, damage, dir);
        if( pRet && pRet->init() ){
            pRet->autorelease();
            return pRet;
        }else{
            delete pRet;
            return nullptr;
        }
    }

    void update(float delta);

    void damaged(float damage);

    void setIsValid(bool isValid);

    bool isValid() const {return m_isValid;}

    void setIsDead(bool isDead){ m_isDead = isDead;}

    bool isDead() const { return m_isDead;}

    unsigned long score(){ return m_score;}

private:
    explicit Enemy(Enemy::EnemyType type, float speed, float health, float dir);

private:
    unsigned long m_score;
    bool runDeadAction;
    bool m_isDead;
    bool m_isValid;
    float m_xSpeed, m_ySpeed;
    float m_damaged;
    float m_health;
    cocos2d::Sprite* sprite;
    cocos2d::Animation* dieAnimation;
    cocos2d::Animate* dieAnimate;
};

#endif//__ENEMY_H__
