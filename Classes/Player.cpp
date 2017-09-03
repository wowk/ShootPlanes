#include "Player.h"
#include "PlaySound.h"
#include "PhysicsShapeCache.h"


USING_NS_CC;

Player::Player()
{
    xSpeed = 90;
    ySpeed = 150;

    fireSpeed = 0.2f;
    lastFireTime = 0.0f;

    m_runDeadAction = false;
    this->setIsValid(true);
    this->setIsDead(false);

    this->setAnchorPoint(Vec2(0.5, 0.5));

    sprite = Sprite::createWithSpriteFrameName("me.png");
    this->addChild(sprite);

    auto phyCache = PhysicsShapeCache::getInstance();
    auto phyBody = phyCache->createBodyWithName("me");
    this->addComponent(phyBody);
    phyBody->setContactTestBitmask(0x2);
    phyBody->setCategoryBitmask(0x2);
    this->setTag(2);
}

bool Player::isValid() const
{
    return m_isValid;
}

void Player::setIsValid(bool isValid)
{
    m_isValid = isValid;
    if( !isValid ){
        this->getPhysicsBody()->removeFromWorld();
        this->removeFromParentAndCleanup(true);
    }
}

bool Player::isDead() const
{
    return m_isDead;
}

void Player::setIsDead(bool isDead)
{
    m_isDead = isDead;
}

void Player::update(float delta)
{
    if( this->isDead() && this->isValid() ){
        if( m_runDeadAction == false ){
            dieAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("playerDie"));
            dieAnimate->retain();
            sprite->runAction(dieAnimate);
            m_runDeadAction = true;
            _eventDispatcher->removeEventListenersForTarget(this, true);
        }else if( dieAnimate->isDone() ){
            this->setIsValid(false);
        }
    }else if( lastFireTime > fireSpeed ){
        fire(Bullet::BulletType::Normal, 10.0f, ::cos(M_PI/2.0), ::sin(M_PI/2.0));
        lastFireTime = 0.0f;
    }else{
        lastFireTime += delta;
    }
}

void Player::fire(Bullet::BulletType type, float damage, float xDir, float yDir)
{
    Bullet* bullet = Bullet::create(type, xDir, yDir, 900.0, damage);
    bullet->setLocalZOrder(11);
    bullet->setPosition(this->getPositionX(),
                        this->getPositionY() + sprite->getContentSize().height / 2);
    getParent()->addChild(bullet);
    bullet->scheduleUpdate();
    PlaySound::getInstance()->playEffect("shoot.mp3");
}
