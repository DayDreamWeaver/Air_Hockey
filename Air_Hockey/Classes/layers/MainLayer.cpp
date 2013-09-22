//
//  MainLayer.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/04.
//
//
#include "MainLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene * MainLayer::scene() {
    CCScene *scene = CCScene::create();
    MainLayer *layer = MainLayer::create();
    scene->addChild(layer);
    return scene;
}

MainLayer::~MainLayer() {
}

bool MainLayer::init() {
    // init super class first
    if(!CCLayer::init()) {
        return false;
    }
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    _isStartMainGame = false;
    
    // logo
    _logo = BaseSprite::gameSpriteWithFile("logo.png");
    _logo->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(_logo);
    // listen to touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(BaseSprite::update));
    
    return true;
}
void MainLayer::update(float dt) {
    if(_isStartMainGame) {
        // transition to next scene
        CCScene *gameScene = GameLayer::scene();
        //CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionSlideInL::create(2.0f, gameScene));
        CCDirector::sharedDirector()->replaceScene(gameScene);
    }

}


void MainLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
    _isStartMainGame = true;
}


