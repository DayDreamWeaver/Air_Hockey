//
//  LogoLayer.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/08/25.
//
//

#include "LogoLayer.h"
#include "SimpleAudioEngine.h"
#include "MainLayer.h"

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
    // design resolution size
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint screenCenter = ccp(screenSize.width * 0.5, screenSize.height * 0.5);

    // create logo sprite
    _logo = BaseSprite::gameSpriteWithFile("logo_top.jpg");
    _logo->setPosition(screenCenter);
    _logo->setZOrder(-1);
    this->addChild(_logo);
    
    // create progress bar outside part
    BaseSprite *barOutside = BaseSprite::gameSpriteWithFile("bar_outside.png");
    barOutside->setPosition(screenCenter);
    this->addChild(barOutside);
    
    // create progress bar inside part
    _progressBar = CCProgressTimer::create(BaseSprite::gameSpriteWithFile("bar_inside.png"));
    // set initial status
    _progressBar->setPercentage(0.0f);
    // set bar to horizontal
    _progressBar->setType(kCCProgressTimerTypeBar);
    _progressBar->setBarChangeRate(ccp(1, 0));
    // start from left to right
    _progressBar->setMidpoint(ccp(0, 0));
    _progressBar->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5 + 3));
    this->addChild(_progressBar);
    
    // create progress bar label
    _barPercentage = CCLabelTTF::create("0", "Arial", 25);
    _barPercentage->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(_barPercentage);

    // enable touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(LogoLayer::update));
    
    return true;
}

void LogoLayer::update(float dt) {
    
    // draw progress bar
    float percentage = _progressBar->getPercentage();
    
    percentage += 10.0f;
    
    char temp[10];
    
    if (percentage <= 100) {
        _progressBar->setPercentage(percentage);
        sprintf(temp, "%d%%", int(percentage));
        _barPercentage->setString(temp);
    } else {
        // load is completed, move to next scene
        // transition to next scene
        CCScene *gameScene = MainLayer::scene();
        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionSlideInL::create(2.0f, gameScene));
    }
    
    
}
