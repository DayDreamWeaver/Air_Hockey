//
//  GameSprite.cpp
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//
//

#include "BaseSprite.h"
#include "BallSprite.h"

BaseSprite::BaseSprite(void) {
    this->reset();
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
    /*
     Update next position, and set sprite position to next 
     positon.
     
     pos: CCPoint, next position object
     */
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

bool BaseSprite::collisionWithSides(const CCRect &winRect, CCPoint &nextPosition, CCPoint &currentVector) {
    /*
     Make sure sprite is in the window, when positon of sprite
     is out of winSize, get it back to winSize
     
     Args:
       winSize: CCSize, available move space
       nextPoint: CCPoint ref, next position of sprite
       currentVector: CCPoint ref, current vector of sprite
     
     Return:
       bool
     */
    bool isCollsion = false;
    
    float radius = this->getRadius();
    CCPoint rectStartPoint = winRect.origin;
    CCSize rectSize = winRect.size;

    // if x is out of rect
    if (nextPosition.x < radius) {
        nextPosition.x = radius;
        currentVector.x *= REBOUND_RATIO;
        isCollsion = true;
    }
    
    if (nextPosition.x > rectSize.width - radius) {
        nextPosition.x = rectSize.width - radius;
        currentVector.x *= REBOUND_RATIO;
        isCollsion = true;
    }
    
    // if y is out of rect
    if (nextPosition.y < radius) {
        nextPosition.y = radius;
        currentVector.y *= REBOUND_RATIO;
        isCollsion = true;
    }

    if (nextPosition.y > rectStartPoint.y + rectSize.height - radius) {
        nextPosition.y = rectStartPoint.y + rectSize.height - radius;
        currentVector.y *= REBOUND_RATIO;
        isCollsion = true;
    }
    
    return isCollsion;
}

void BaseSprite::reset() {
    /*
     Reset all status for the sprite.
     */
    _vector = ccp(0, 0);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _touch = NULL;
}
