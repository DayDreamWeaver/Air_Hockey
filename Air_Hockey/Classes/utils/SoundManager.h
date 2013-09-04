//
//  SoundManager.h
//  Air_Hockey
//
//  Created by hanks on 2013/09/04.
//
//

#ifndef __Air_Hockey__SoundManager__
#define __Air_Hockey__SoundManager__

#include <iostream>
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

// sound tag
enum Sound {
    HIT_SE,
    SCORE_SE,
    ATTACK_READY_SE,
    BGM
};

// path definition
#define HIT_SE_PATH "hit.wav"
#define SCORE_SE_PATH "score.wav"
#define ATTACK_READY_SE_PATH "attack_ready.wav"
#define BGM_PATH "background.mp3"

// volumn definition
#define DEFAULT_BGM_VOLUMN 0.5f
#define DEFAULT_SE_VOLUMN 0.5f

class SoundManager {
public:
    // play background music
    static void playBGM(int BGMTag=BGM);
    // play sound effect
    static void playSE(int SETag);
    // preload all sound resources
    static void preloadRes();
    // release all sound resources
    static void releaseRes();
    // get simple audio engine object
    static SimpleAudioEngine* getSimpleAudioEngin();
    // set bgm volumn
    static void setBGMVolumn(float volumn);
    // set sound effect volumn
    static void setSEVolumn(float volumn);
    // init sound environment
    static void initSoundEnvironment();
};

#endif /* defined(__Air_Hockey__SoundManager__) */
