#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Node {
public:
    enum BulletType {Normal};

    void update(float delta);

    static Bullet* create(Bullet::BulletType type, float xDir, float yDir, float speed, float damage){
        Bullet *pRet = new(std::nothrow) Bullet(type, xDir, yDir, speed, damage);
        if (pRet && pRet->init()){
            pRet->autorelease();
            return pRet;
        }else{
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

    bool isValid() const;

    cocos2d::Rect collRect();

    float damage() const;

    void setIsValid(bool isValid);

private:
    explicit Bullet(Bullet::BulletType type, float xDir, float yDir, float speed, float damage);

private:
    bool m_isValid;
    float m_xSpeed;
    float m_ySpeed;
    float m_damage;
    cocos2d::Sprite* sprite;
};

#endif//__BULLET_H__
