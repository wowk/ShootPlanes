#ifndef __SCORE_SPRITE_H__
#define __SCORE_SPRITE_H__

#include "cocos2d.h"

class ScoreSprite : public cocos2d::LabelTTF {
public:
    CREATE_FUNC(ScoreSprite);
    void increase(int score);
    void reset();

protected:
    ScoreSprite();

private:
    unsigned long m_score;
    cocos2d::Sprite* sprite;
};

#endif//__SCORE_SPRITE_H__
