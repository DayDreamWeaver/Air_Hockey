//
//  Air_HockeyAppDelegate.cpp
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set resource path
    CCSize screenSize = pEGLView->getFrameSize();
    pEGLView->setDesignResolutionSize(768, 1024, kResolutionExactFit);
    
    std::vector<std::string> searchPaths;
    if (screenSize.width > 768) {
        searchPaths.push_back("hd");
        pDirector->setContentScaleFactor(2);
    } else {
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(1);
    }
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPaths);
    
    // add sound
    SimpleAudioEngine::sharedEngine()->preloadEffect("hit.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("score.wav");

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
