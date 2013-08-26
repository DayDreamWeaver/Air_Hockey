//
//  LogoLayer.h
//  Air_Hockey
//
//  Created by hanks on 2013/08/25.
//
//

#ifndef __Air_Hockey__LogoLayer__
#define __Air_Hockey__LogoLayer__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

class LogoLayer : public cocos2d::CCLayer {

    GameSprite *_logo;
    CCProgressTimer *_progressBar;
    CCLabelTTF * _barPercentage;
    
public:
    ~LogoLayer();
    // return bool value
    virtual bool init();
    static cocos2d::CCScene* scene();
    // preprocessor macro for "static create()"
    CREATE_FUNC(LogoLayer);
    // main loop function
    void update(float dt);
};

#endif /* defined(__Air_Hockey__LogoLayer__) */
