#include "StartScene.h"
#include "BackgroundSprite.h"
#include "LoadingScene.h"
#include "EnemySpawn.h"
#include "PhysicsShapeCache.h"


USING_NS_CC;
using namespace cocos2d::ui;

Scene *StartScene::createScene()
{
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    Layer* layer = StartScene::create();
    scene->addChild(layer);

    return scene;
}

bool StartScene::init()
{
    if( !Layer::init() ){
        return false;
    }

    this->loadResourse();

    this->addChild(BackgroundNode::create());

    Size vSize = Director::getInstance()->getVisibleSize();

    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    AnimationCache* animationCache = AnimationCache::getInstance();

    Sprite* titleSprite = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("logo.png"));
    titleSprite->setPosition(vSize.width / 2, vSize.height / 2 + 140);
    this->addChild(titleSprite);
    titleSprite->setLocalZOrder(3);
    titleSprite->setScale(0.6);
    titleSprite->scheduleUpdate();

    EnemySpawn* enemySpawn = EnemySpawn::create();
    this->addChild(enemySpawn);
    enemySpawn->setZOrder(1);
    enemySpawn->schedule(schedule_selector(EnemySpawn::spawn), 2.0);

    auto startMenuItem = MenuItemImage::create(
                                "menu_start.png",
                                "menu_start.png",
                                "menu_start.png",
                                CC_CALLBACK_1(StartScene::onMenuItemCallback ,this));
    startMenuItem->setTag(0);

    auto exitMenuItem = MenuItemImage::create(
                                "menu_exit.png",
                                "menu_exit.png",
                                "menu_exit.png",
                                CC_CALLBACK_1(StartScene::onMenuItemCallback ,this));
    exitMenuItem->setTag(1);

    auto menu = Menu::create();
    menu->addChild(startMenuItem);
    menu->addChild(exitMenuItem);
    menu->alignItemsVerticallyWithPadding(10);
    menu->setLocalZOrder(10);
    menu->setScale(0.5);
    menu->setAnchorPoint(Vec2(0.5,0.5));
    menu->setPosition(vSize.width/4, vSize.height/8);
    menu->setColor(Color3B(120,120,102));
    this->addChild(menu);

    return true;
}

void StartScene::onMenuItemCallback(cocos2d::Ref* pSender)
{

    auto ptr = dynamic_cast<MenuItem*>(pSender);
    if( ptr->getTag() == 0 ){
        auto scene = LoadingScene::createScene();
        Director::getInstance()->pushScene(scene);
    }else if( ptr->getTag() == 1 ){
        ::exit(0);
    }
}

void StartScene::loadResourse()
{
    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("plane.plist");
    PhysicsShapeCache::getInstance()->addShapesWithFile("planeShape.plist");
}
