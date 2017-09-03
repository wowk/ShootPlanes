#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer{
public:
    static cocos2d::Scene *createScene(void);
    CREATE_FUNC(LoadingScene);
    bool init();
    void loadingFinished();
private:
    cocos2d::Animate* loadingAnimate;
};

#endif//__LOADING_SCENE_H__
