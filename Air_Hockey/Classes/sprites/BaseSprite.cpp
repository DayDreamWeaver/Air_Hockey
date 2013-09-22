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
    
}

void BaseSprite::reset() {
    /*
     Reset all status for the sprite.
     */
    _vector = ccp(0, 0);
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _touch = NULL;
}
