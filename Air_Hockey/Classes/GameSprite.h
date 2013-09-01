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

class GameSprite : public CCSprite {
public:
    CC_SYNTHESIZE(CCPoint, _nextPositon, NextPosition);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
    
    GameSprite(void);
    ~GameSprite(void);

    static GameSprite* gameSpriteWithFile(const char * pszFilename);
    // when using sprite sheet, create with frame name
    static GameSprite* gameSpriteWithFrameName(const char * pszFilename);

    virtual void setPosition(const CCPoint& pos);
    inline float radius() {
        return this->getTexture()->getContentSize().width * 0.5f;
    }
};

#endif /* defined(__Air_Hockey__GameSprite__) */
