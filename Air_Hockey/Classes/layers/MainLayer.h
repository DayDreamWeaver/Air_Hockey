//
//  MainLayer.h
//  Air_Hockey
//
//  Created by hanks on 2013/09/04.
//
//

#ifndef __Air_Hockey__MainLayer__
#define __Air_Hockey__MainLayer__

#include "cocos2d.h"
#include "../sprites/BaseSprite.h"

using namespace cocos2d;

class MainLayer : public cocos2d::CCLayer {
    
    BaseSprite *_logo;
    CCSize _screenSize;
    bool _isStartMainGame;
public:
    ~MainLayer();
    // return bool value
    virtual bool init();
    static cocos2d::CCScene* scene();
    // preprocessor macro for "static create()"
    CREATE_FUNC(MainLayer);
    // main loop function
    void update(float dt);
    
    // touch handler
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
};

#endif /* defined(__Air_Hockey__MainLayer__) */
