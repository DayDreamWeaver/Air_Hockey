//
//  LogoLayer.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/08/25.
//
//

#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene * LogoLayer::scene() {
    CCScene *scene = CCScene::create();
    LogoLayer *layer = LogoLayer::create();
    scene->addChild(layer);
    return scene;
}

LogoLayer::~LogoLayer() {

}

bool LogoLayer::init() {
    // init super class first
    if (!CCLayer::init()) {
        return false;
    }

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint screenCenter = ccp(screenSize.width * 0.5, screenSize.height * 0.5);

    // create logo sprite
    _logo = GameSprite::gameSpriteWithFile("logo_top.jpg");
    _logo->setPosition(screenCenter);
    _logo->setZOrder(-1);
    this->addChild(_logo);
    
    // create progress bar outside part
    GameSprite *barOutside = GameSprite::gameSpriteWithFile("bar_outside.png");
    barOutside->setPosition(screenCenter);
    this->addChild(barOutside);
    
    // create progress bar inside part
    _progressBar = CCProgressTimer::create(GameSprite::gameSpriteWithFile("bar_inside.png"));
    // set initial status
    _progressBar->setPercentage(0.0f);
    // set bar to horizontal
    _progressBar->setType(kCCProgressTimerTypeBar);
    _progressBar->setBarChangeRate(ccp(1, 0));
    // start from left to right
    _progressBar->setMidpoint(ccp(0, 0));
    _progressBar->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5 + 3));
    this->addChild(_progressBar);

    // enable touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(LogoLayer::update));
    
    return true;
}

void LogoLayer::update(float dt) {
    
    // draw progress bar
    float percentage = _progressBar->getPercentage();
    
    percentage += 0.5f;
    
    if (percentage < 100) {
        _progressBar->setPercentage(percentage);
    } else {
        // load is completed, move to next scene
        // transition to next scene
        CCDirector::sharedDirector()->setDepthTest(true);
        CCScene *gameScene = GameLayer::scene();
        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1.0f, gameScene));
        //CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFadeUp::create(3.5, gameScene));
    }
    
    
}
