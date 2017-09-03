#include "Bullet.h"
#include "GameScene.h"
#include "PhysicsShapeCache.h"

USING_NS_CC;

Bullet::Bullet(BulletType type, const float xDir, float yDir, float speed, float damage)
{
    PhysicsBody* phyBody = nullptr;
    auto phyCache = PhysicsShapeCache::getInstance();

    switch( type ){
    case BulletType::Normal:
        sprite = Sprite::createWithSpriteFrameName("cartridge.png");
        phyBody = phyCache->createBodyWithName("cartridge");
        break;
    default:
        return;
    }
    this->addChild(sprite);
    this->addComponent(phyBody);
    phyBody->setContactTestBitmask(0x1);
    phyBody->setCategoryBitmask(0x1);
    this->setTag(1);

    m_xSpeed = xDir * speed;
    m_ySpeed = yDir * speed;
    m_damage = damage;

    this->setLocalZOrder(10);
    this->setIsValid(true);
}

void Bullet::update(float delta)
{
    float dx, dy;
    dx = m_xSpeed * delta + this->getPositionX();
    dy = m_ySpeed * delta + this->getPositionY();

    Size size = Director::getInstance()->getVisibleSize();

    if( dy < 0 || dx < 0 || dx > size.width || dy > size.height ){
        setIsValid(false);
        return;
    }else{
        this->setPosition(dx, dy);
    }
}

bool Bullet::isValid() const
{
    return m_isValid;
}

Rect Bullet::collRect()
{
    Size size = sprite->getContentSize();
    return Rect(getPositionX() - size.width / 2,
                getPositionY() - size.height / 2,
                size.width, size.height);
}

float Bullet::damage() const
{
    return m_damage;
}

void Bullet::setIsValid(bool isValid)
{
    m_isValid = isValid;
    if( !isValid ){
        this->getPhysicsBody()->removeFromWorld();
        this->removeFromParentAndCleanup(true);
    }
}
