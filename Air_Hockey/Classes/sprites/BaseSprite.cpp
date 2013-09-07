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

bool BaseSprite::isCollsionWithSides(const CCSize &winSize) {
    /*
     Make sure sprite is in the window, when positon of sprite
     is out of winSize, get it back to winSize
     
     Args:
       winSize: CCSize, available move space
     
     Return:
       bool
     */
    
}

