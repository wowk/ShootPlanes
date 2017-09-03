#include "ScoreSprite.h"
#include <cstring>


USING_NS_CC;

void ScoreSprite::increase(int score)
{
    m_score += score;

    char buf[32] = {0};
    ::sprintf(buf, "score: %lu", m_score);
    this->setString(buf);
}

void ScoreSprite::reset()
{
    m_score = 0;
}

ScoreSprite::ScoreSprite()
{
    m_score = 0;
    this->setString("score: 0");
    this->setColor(Color3B(12, 12, 12));
    this->setFontSize(27.0);
    this->setLocalZOrder(20);
    this->setHorizontalAlignment(TextHAlignment::LEFT);
    this->setVerticalAlignment(TextVAlignment::CENTER);
    this->setAnchorPoint(Vec2(0, 0));
}
