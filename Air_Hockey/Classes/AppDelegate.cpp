//
//  Air_HockeyAppDelegate.cpp
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "layers/GameLayer.h"
#include "layers/LogoLayer.h"
#include "utils/SoundManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    SoundManager::releaseSound();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // get real screen size from device
    CCSize screenSize = pEGLView->getFrameSize();
    // set design size
    pEGLView->setDesignResolutionSize(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT, kResolutionShowAll);
    
    std::vector<std::string> searchPaths;
    if (screenSize.width > 768) {
        printf("hd here.\n");
        searchPaths.push_back("hd");
        pDirector->setContentScaleFactor(2);
    } else {
        printf("sd here.\n");
        searchPaths.push_back("sd");
        pDirector->setContentScaleFactor(1);
    }
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPaths);
    
    // init sound
    SoundManager::initSoundEnvironment();
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = GameLayer::scene();

    // first show logo scene
    CCScene *pScene = LogoLayer::scene();
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SoundManager::pauseSound();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SoundManager::resumeSound();
}
