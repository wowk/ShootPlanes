#ifndef __PLAYER__
#define __PLAYER__

#include "Bullet.h"
#include "cocos2d.h"

class Player : public cocos2d::Node {
public:
    CREATE_FUNC(Player);

    void update(float delta);

    void fire(Bullet::BulletType type, float damage, float xDir, float yDir);

    bool isDead() const;
    void setIsDead(bool isDead);

    bool isValid() const;
    void setIsValid(bool isValid);

protected:
    Player();

private:
    int xSpeed;
    int ySpeed;

    float fireSpeed;
    float lastFireTime;

    bool m_isValid;
    bool m_isDead;
    bool m_runDeadAction;

    cocos2d::Sprite* sprite;
    cocos2d::Animate* dieAnimate;
};

#endif //__PALYER__
