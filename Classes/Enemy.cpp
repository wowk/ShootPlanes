#include "Enemy.h"
#include "GameScene.h"
#include "PlaySound.h"
#include "PhysicsShapeCache.h"


USING_NS_CC;


void Enemy::update(float delta)
{
    if( this->isDead() ){
        if( runDeadAction == false ){
            sprite->runAction(dieAnimate);
            PlaySound::getInstance()->playEffect("explosion.mp3");
            runDeadAction = true;
        }else if( dieAnimate->isDone() ){
            this->setIsValid(false);
        }
    }else{
        float x = this->getPositionX() + m_xSpeed * delta;
        float y = this->getPositionY() + m_ySpeed * delta;
        Size size = sprite->getContentSize() / 2;
        Size vSize = Director::getInstance()->getVisibleSize();
        if( x + size.width < 0 || x - size.width > vSize.width
            || y + size.height < 0 || y - size.height > vSize.height ){
            this->setIsValid(false);
        }else{
            this->setPosition(x, y);
        }
    }
}

Enemy::Enemy(EnemyType type, float speed, float health, float dir)
{
    PhysicsShapeCache* phyCache = PhysicsShapeCache::getInstance();
    PhysicsBody* phyBody = nullptr;

    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    dieAnimation = Animation::create();

    switch( type ){
    case Small:
        sprite = Sprite::createWithSpriteFrameName("plane1.png");
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die1.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die2.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die3.png"));
        phyBody = phyCache->createBodyWithName("plane1");
        break;
    case Miedum:
        sprite = Sprite::createWithSpriteFrameName("plane2.png");
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die1.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die2.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die3.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die3.png"));
        phyBody = phyCache->createBodyWithName("plane2");
        break;
    case Big:
        sprite = Sprite::createWithSpriteFrameName("plane3.png");
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die1.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die2.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die3.png"));
        dieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die3.png"));
        phyBody = phyCache->createBodyWithName("plane3");
        break;
    default:
        return;
    }

    this->addChild(sprite);
    this->addComponent(phyBody);
    phyBody->setContactTestBitmask(0x3);
    phyBody->setCategoryBitmask(0x3);
    this->setTag(3);

    dieAnimation->setLoops(1);
    dieAnimation->setRestoreOriginalFrame(false);
    dieAnimation->setDelayPerUnit(1.0/5);
    dieAnimate = Animate::create(dieAnimation);
    dieAnimate->retain();
    runDeadAction = false;

    Size size = sprite->getContentSize() / 2;
    Size vSize = Director::getInstance()->getVisibleSize();

    m_xSpeed = speed * ::cos(dir);
    m_ySpeed = speed * ::sin(dir);
    m_damaged = 0.0f;
    m_health = health;
    m_isValid = true;
    m_isDead = false;

    switch (type) {
    case EnemyType::Small:
        m_score = 1000;
        break;
    case EnemyType::Miedum:
        m_score = 3000;
        break;
    case EnemyType::Big:
        m_score = 5000;
        break;
    default:
        break;
    }

    ::srand(::time(NULL));
    float randX = ::rand() % (int)(vSize.width - size.width * 2) + size.width;
    this->setPosition(randX, vSize.height + size.height);
}

void Enemy::damaged(float damage)
{
    m_damaged += damage;
    if( m_health <= m_damaged){
        setIsDead(true);
    }
}

void Enemy::setIsValid(bool isValid)
{
    m_isValid = isValid;
    if( !isValid ){
        this->getPhysicsBody()->removeFromWorld();
        this->removeFromParentAndCleanup(true);
    }
}
