#ifndef __PLAY_SOUND_H__
#define __PLAY_SOUND_H__

#include <map>
#include <string>


class PlaySound {
public:
    static PlaySound* getInstance(){
        static PlaySound* pInst = new PlaySound;
        return pInst;
    }
    void playBackgoundMusic(const char* path);
    void playEffect(const char* path);
    void preloadEffect(const char* path);

private:
    PlaySound();

private:
    std::map<std::string, int> soundIdMap;
};

#endif//__PLAY_SOUND_H__
