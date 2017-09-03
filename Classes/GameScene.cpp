#include "Player.h"
#include "EnemySpawn.h"
#include "Enemy.h"
#include "PlaySound.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsShapeCache.h"


USING_NS_CC;
USING_NS_CC_MATH;


Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));

    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

void GameScene::loadResource()
{
    PhysicsShapeCache::getInstance()->addShapesWithFile("planeShape.plist");

    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("plane.plist");
    Animation* playerDieAnimation = Animation::create();
    playerDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("me_die1.png"));
    playerDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("me_die2.png"));
    playerDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("me_die3.png"));
    playerDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die4.png"));
    playerDieAnimation->setLoops(1);
    playerDieAnimation->setRestoreOriginalFrame(false);
    playerDieAnimation->setDelayPerUnit(1.0f/3.0f);

    Animation* smallEnemyDieAnimation = Animation::create();
    smallEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die1.png"));
    smallEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die2.png"));
    smallEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane1_die3.png"));
    smallEnemyDieAnimation->setLoops(1);
    smallEnemyDieAnimation->setRestoreOriginalFrame(false);
    smallEnemyDieAnimation->setDelayPerUnit(1.0f/3.0f);

    Animation* mediumEnemyDieAnimation = Animation::create();
    mediumEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die1.png"));
    mediumEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die2.png"));
    mediumEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die3.png"));
    mediumEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane2_die4.png"));
    mediumEnemyDieAnimation->setLoops(1);
    mediumEnemyDieAnimation->setRestoreOriginalFrame(false);
    mediumEnemyDieAnimation->setDelayPerUnit(1.0f/4.0f);

    Animation* bigEnemyDieAnimation = Animation::create();
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die1.png"));
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die2.png"));
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die3.png"));
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die4.png"));
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die5.png"));
    bigEnemyDieAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("plane3_die6.png"));
    bigEnemyDieAnimation->setLoops(1);
    bigEnemyDieAnimation->setRestoreOriginalFrame(false);
    bigEnemyDieAnimation->setDelayPerUnit(1.0f/6.0f);

    AnimationCache* animationCache = AnimationCache::getInstance();
    animationCache->addAnimation(playerDieAnimation, "playerDie");
    animationCache->addAnimation(smallEnemyDieAnimation, "smallEnemyDie");
    animationCache->addAnimation(mediumEnemyDieAnimation, "mediumEnemyDie");
    animationCache->addAnimation(bigEnemyDieAnimation, "bigEnemyDie");
}

bool GameScene::init()
{
    if ( !Layer::init() ){
        return false;
    }
    setName("Scene");
    loadResource();

    Size vSize = Director::getInstance()->getVisibleSize();

    //play music
    PlaySound::getInstance()->playBackgoundMusic("bgm.mp3");

    //add background
    this->addChild(BackgroundNode::create());

    //add player
    player = Player::create();
    player->setZOrder(10);
    player->setPosition(vSize.width / 2, vSize.height / 2 - 100);
    this->addChild(player);
    player->schedule(schedule_selector(Player::update), 0.1f);

    //add enemy spawner
    enemySpawn = EnemySpawn::create();
    this->addChild(enemySpawn);
    enemySpawn->schedule(schedule_selector(EnemySpawn::spawn), 1.0f);

    //add score board
    score = ScoreSprite::create();
    score->setPosition(0, vSize.height - 30);
    this->addChild(score);

    //add mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](EventMouse* event) {
        if( !player ){
            return;
        }
        Size size = Director::getInstance()->getVisibleSize();
        player->setPosition(event->getCursorX(), size.height + event->getCursorY());
    };
    mouseListener->onMouseDown = [=](EventMouse* event) {
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //add physics contact listener
    auto phyContactListener = EventListenerPhysicsContact::create();
    phyContactListener->onContactBegin = [=](PhysicsContact & contact) -> bool {
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();
        Bullet* pBullet = nullptr;
        Enemy* pEnemy = nullptr;
        Player* pPlayer = nullptr;

        if( !nodeA || !nodeB ) return false;

        if( nodeA->getTag() == 1 && nodeB->getTag() == 3 ){
            pBullet = dynamic_cast<Bullet*>(nodeA);
            pEnemy = dynamic_cast<Enemy*>(nodeB);
            if( !pBullet->isValid() || pEnemy->isDead() ){
                return false;
            }
            pBullet->setIsValid(false);
            pEnemy->damaged(pBullet->damage());
            if( pEnemy->isDead() ){
                score->increase(pEnemy->score());
            }
        }else if( nodeA->getTag() == 3 && nodeB->getTag() == 1 ){
            pBullet = dynamic_cast<Bullet*>(nodeB);
            pEnemy = dynamic_cast<Enemy*>(nodeA);
            if( !pBullet->isValid() || pEnemy->isDead() ){
                return false;
            }
            pBullet->setIsValid(false);
            pEnemy->damaged(pBullet->damage());
            if( pEnemy->isDead() ){
                score->increase(pEnemy->score());
            }
        }else if( nodeA->getTag() == 2 && nodeB->getTag() == 3 ){
            pPlayer= dynamic_cast<Player*>(nodeA);
            pEnemy = dynamic_cast<Enemy*>(nodeB);
            if( pPlayer->isDead() || pEnemy->isDead() ){
                return false;
            }else{
                pPlayer->setIsDead(true);
                pEnemy->setIsDead(true);
                player = nullptr;
                menu->setVisible(true);
            }
        }else if( nodeA->getTag() == 3 && nodeB->getTag() == 2 ){
            pPlayer= dynamic_cast<Player*>(nodeB);
            pEnemy = dynamic_cast<Enemy*>(nodeA);
            if( pPlayer->isDead() || pEnemy->isDead() ){
                return false;
            }else{
                pPlayer->setIsDead(true);
                pEnemy->setIsDead(true);
                player = nullptr;
                menu->setVisible(true);
            }
        }

        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(phyContactListener, this);

    //add menu
    auto continueMenuItem = MenuItemFont::create("Continue",
                                CC_CALLBACK_1(GameScene::onMenuItemCallback,this));
    continueMenuItem->setTag(0);
    auto mainMenuItem = MenuItemFont::create("Main Menu",
                                CC_CALLBACK_1(GameScene::onMenuItemCallback,this));
    mainMenuItem->setTag(1);

    menu = Menu::create();
    menu->addChild(continueMenuItem);
    menu->addChild(mainMenuItem);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setScale(0.5);

    menu->setPosition(vSize.width / 4, vSize.height / 4);
    menu->setVisible(false);
    this->addChild(menu);

    this->scheduleUpdate();

    return true;
}

void GameScene::onMenuItemCallback(Ref *pSender)
{
    auto vSize = Director::getInstance()->getVisibleSize();
    unsigned tag = dynamic_cast<Node*>(pSender)->getTag();
    if( tag == 0 ){
        for( Node* node : this->getChildren() ){
            if( node->getTag() == 3 ){
                dynamic_cast<Enemy*>(node)->setIsDead(true);
            }
        }
        menu->setVisible(false);
        score->reset();
        player = Player::create();
        player->setZOrder(10);
        player->setPosition(vSize.width / 2, vSize.height / 2 - 100);
        this->addChild(player);
        player->schedule(schedule_selector(Player::update), 0.1f);
    }else if( tag == 1 ){
        Director::getInstance()->popScene();
    }
}

void GameScene::update(float delta)
{
    return;
}
