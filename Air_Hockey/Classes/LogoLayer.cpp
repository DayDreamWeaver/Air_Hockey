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

    // create logo sprite
    _logo = GameSprite::gameSpriteWithFile("logo_top.jpg");
    _logo->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5));
    _logo->setZOrder(-1);
    this->addChild(_logo);

    // enable touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(LogoLayer::update));
    
    return true;
}

void LogoLayer::update(float dt) {
    // transation to next scene
    CCDirector::sharedDirector()->setDepthTest(true);
    CCScene *gameScene = GameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(3.5, gameScene));
    //CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFadeUp::create(3.5, gameScene));
}
