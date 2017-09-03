#include "BackgroundSprite.h"

BackgroundNode::BackgroundNode()
{
    Size size = Director::getInstance()->getVisibleSize();

    bg01 = Sprite::create("bg_01.jpg");
    bg02 = Sprite::create("bg_02.jpg");

    bg01->setAnchorPoint(Vec2(0, 0));
    bg02->setAnchorPoint(Vec2(0, 0));
    bg01->setPosition(0, 0);
    bg02->setPosition(0, -size.height);
    bg01->setLocalZOrder(0);
    bg02->setLocalZOrder(0);

    speed = 40;

    this->addChild(bg01);
    this->addChild(bg02);
    this->scheduleUpdate();
}

BackgroundNode::~BackgroundNode()
{

}

void BackgroundNode::update(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    float newY1 = bg01->getPositionY() - delta * speed;
    float newY2;

    if( newY1 < -size.height ){
        newY1 = 2 * size.height + newY1;
        newY2 = newY1 - size.height;
    }else if( newY1 <= 0 ){
        newY2 = newY1 + size.height;
    }else if( newY1 > 0 ){
        newY2 = newY1 - size.height;
    }

    bg01->setPositionY(newY1);
    bg02->setPositionY(newY2);
}
