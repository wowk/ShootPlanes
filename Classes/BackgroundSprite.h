#ifndef __BACKGROUND_NODE__
#define __BACKGROUND_NODE__

#include <cocos2d.h>

USING_NS_CC;

class BackgroundNode : public Node {
public:
    BackgroundNode();
    ~BackgroundNode();

    void update(float delta);

    CREATE_FUNC(BackgroundNode);

private:
    Sprite* bg01;
    Sprite* bg02;
    float speed;
};

#endif //__BACKGROUND_NODE__
