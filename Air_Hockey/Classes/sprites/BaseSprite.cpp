//
//  GameSprite.cpp
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//
//

#include "BaseSprite.h"

BaseSprite::BaseSprite(void) {
    _vector = ccp(0, 0);
}

BaseSprite::~BaseSprite(void) {
    
}

BaseSprite* BaseSprite::gameSpriteWithFile(const char *pszFilename) {
    BaseSprite *sprite = new BaseSprite();
    if (sprite && sprite->initWithFile(pszFilename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

BaseSprite* BaseSprite::gameSpriteWithFrameName(const char *pszFilename) {
    BaseSprite *sprite = new BaseSprite();
    if (sprite && sprite->initWithSpriteFrameName(pszFilename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void BaseSprite::setPosition(const cocos2d::CCPoint &pos) {
    CCSprite::setPosition(pos);
    if (!_nextPositon.equals(pos)) {
        _nextPositon = pos;
    }
}

void BaseSprite::update(float dt) {
    /*
     Let sprite to control its status, like postion, rotation, vector, self
     */
}

bool BaseSprite::isCollsionWithSides(const CCRect &winRect) {
    /*
     Make sure sprite is in the window, when positon of sprite
     is out of winSize, get it back to winSize
     
     Args:
       winSize: CCSize, available move space
     
     Return:
       bool
     */
    bool isCollsion = false;
    float radius = this->getRadius();
    CCPoint nextPosition = this->getNextPosition();
    CCPoint rectStartPoint = winRect.origin;
    CCSize rectSize = winRect.size;

    // if x is out of rect
    if (nextPosition.x < radius) {
        nextPosition.x = radius;
        isCollsion = true;
    }
    
    if (nextPosition.x > rectSize.width - radius) {
        nextPosition.x = rectSize.width - radius;
        isCollsion = true;
    }
    
    // if y is out of rect
    if (nextPosition.y < radius) {
        nextPosition.y = radius;
        isCollsion = true;
    }

    if (nextPosition.y > rectStartPoint.y + rectSize.height - radius) {
        nextPosition.y = rectStartPoint.y + rectSize.height - radius;
        isCollsion = true;
    }

    return isCollsion;
}
