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
#include <iostream>

using namespace cocos2d;

class BaseSprite : public CCSprite {
public:
    CC_SYNTHESIZE(CCPoint, _nextPositon, NextPosition);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
    
    BaseSprite(void);
    ~BaseSprite(void);

    static BaseSprite* gameSpriteWithFile(const char *pszFilename);
    // when using sprite sheet, create with frame name
    static BaseSprite* gameSpriteWithFrameName(const char *pszFilename);

    virtual void setPosition(const CCPoint &pos);
    
    inline float getRadius() {
        return this->getTexture()->getContentSize().width * 0.5f;
    }
};

#endif /* defined(__Air_Hockey__GameSprite__) */