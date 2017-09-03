#include "PlaySound.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"


using CocosDenshion::SimpleAudioEngine;


void PlaySound::playBackgoundMusic(const char *path)
{
    if( SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() ){
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    }else{
        SimpleAudioEngine::getInstance()->playBackgroundMusic(path, true);
    }
}

void PlaySound::playEffect(const char *path)
{
    if( soundIdMap.find(path) == soundIdMap.end() ){
        soundIdMap[path] = SimpleAudioEngine::getInstance()->playEffect(path);
    }else{
        SimpleAudioEngine::getInstance()->stopEffect(soundIdMap[std::string(path)]);
        soundIdMap[path] = SimpleAudioEngine::getInstance()->playEffect(path);
    }
}

PlaySound::PlaySound()
{
    SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("explosion.mp3");
}
