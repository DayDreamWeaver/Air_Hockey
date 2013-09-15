//
//  GameSprite.h
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//
//

#ifndef __Air_Hockey__GameSprite__
#define __Air_Hockey__GameSprite__

#include "cocos2d.h"

using namespace cocos2d;

class BaseSprite : public CCSprite {
protected:
    // size of design resolution size
    CCSize _screenSize;

public:
    // next position for the sprite
    CC_SYNTHESIZE(CCPoint, _nextPositon, NextPosition);
    // vector for sprite, used to present speed and direction
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    // touch on the sprite
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
    
    BaseSprite(void);
    // need to use virtual deconstruction in the base class
    virtual ~BaseSprite(void);

    // directly create sprite with file
    static BaseSprite* gameSpriteWithFile(const char *pszFilename);
    // when using sprite sheet, create with frame name
    static BaseSprite* gameSpriteWithFrameName(const char *pszFilename);
    
    // override setPosition function
    // to update _nextPostion when to set position
    virtual void setPosition(const CCPoint &pos);
    // get radius of sprite
    inline float getRadius() {
        return this->getTexture()->getContentSize().width * 0.5f;
    }
    // let sprite to control status of itself
    virtual void update(float dt);
    // check basic move constraints with rect
    virtual bool isCollisionWithSides(const CCRect &winRect);
    // reset variables of sprite
    virtual void reset(void);
};

#endif /* defined(__Air_Hockey__GameSprite__) */
