#include "LoadingScene.h"
#include "BackgroundSprite.h"
#include "GameScene.h"


USING_NS_CC;

Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LoadingScene::create();
    scene->addChild(layer);

    return scene;
}

bool LoadingScene::init()
{
    if( !Layer::init() ){
        return false;
    }


    auto bgNode = BackgroundNode::create();
    this->addChild(bgNode);

    auto vSize = Director::getInstance()->getVisibleSize();
    auto spriteCache = SpriteFrameCache::getInstance();
    auto loadingAnimation = Animation::create();
    loadingAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("loading1.png"));
    loadingAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("loading2.png"));
    loadingAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("loading3.png"));
    loadingAnimation->setDelayPerUnit(0.3);
    loadingAnimation->setLoops(3);
    loadingAnimate = Animate::create(loadingAnimation);
    auto callback = CallFunc::create(CC_CALLBACK_0(LoadingScene::loadingFinished, this));
    auto seqAction = Sequence::create(loadingAnimate, callback, nullptr);
    auto node = Sprite::create();
    node->setPosition(vSize.width/2, vSize.height / 1.5);
    node->runAction(seqAction);
    this->addChild(node);

    return true;
}

void LoadingScene::loadingFinished()
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
