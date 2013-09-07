//
//  SoundManager.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/04.
//
//

#include "SoundManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void SoundManager::playBGM(int BGMTag) {
    /*
     Play background music
     
     Args:
       BGMTag: enum type for bgm
     
     Returns:
       void
     */
    
    switch (BGMTag) {
        case BGM:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGM_PATH);
            break;
        default:
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BGM_PATH);
            break;
    }
    
}

void SoundManager::playSE(int SETag) {
    /*
     Play sound effect with SE tag
     
     Args:
       SETag: enum type for each sound effect
     
     Returns:
       void
     */
    
    switch (SETag) {
        case HIT_SE:
            SimpleAudioEngine::sharedEngine()->playEffect(HIT_SE_PATH);
            break;
        case SCORE_SE:
            SimpleAudioEngine::sharedEngine()->playEffect(SCORE_SE_PATH);
            break;
        case ATTACK_READY_SE:
            SimpleAudioEngine::sharedEngine()->playEffect(ATTACK_READY_SE_PATH);
            break;
        default:
            SimpleAudioEngine::sharedEngine()->playEffect(HIT_SE_PATH);
            break;
    }
}

void SoundManager::preloadSound() {
    /*
     Preload all the sound resources
     
     Returns:
       void
     */
    
    SimpleAudioEngine::sharedEngine()->preloadEffect(HIT_SE_PATH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(SCORE_SE_PATH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(ATTACK_READY_SE_PATH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(BGM_PATH);
}

void SoundManager::releaseSound() {
    /*
     Release all sound resources
     
     Returns:
       void
     */
    
    SimpleAudioEngine::sharedEngine()->end();
}

SimpleAudioEngine* SoundManager::getSimpleAudioEngin() {
    /*
     Get simple audio engin object
     
     Returns:
       SimpleAudioEngine* obj
     */
    
    return SimpleAudioEngine::sharedEngine();
}

void SoundManager::setBGMVolumn(float volumn) {
    /*
     Set background volumn
     
     Args:
       volumn: float, amount of volumn
     
     Returns:
       void
     */
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volumn);
}

void SoundManager::setSEVolumn(float volumn) {
    /*
     Set sound effect volumn
     
     Args:
       volumn: float, amount of volumn
     
     Returns:
       void
     */
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volumn);
}

void SoundManager::initSoundEnvironment() {
    /*
     Initiate sound environment.
     
     Like preload, and set volumn
     
     Returns:
       void
     */
    
    SoundManager::preloadSound();
    SoundManager::setBGMVolumn(DEFAULT_BGM_VOLUMN);
    SoundManager::setSEVolumn(DEFAULT_SE_VOLUMN);
}

void SoundManager::resumeSound() {
    /*
     Resume sound play
     */
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void SoundManager::pauseSound() {
    /*
     Pause sound play
     */
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}