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
    CCPoint current_postion = this->getPosition();
    CCPoint rectStartPoint = winRect.origin;
    CCSize rectSize = winRect.size;

    // if x is out of rect
    if (current_postion.x < radius) {
        this->setPositionX(radius);
        isCollsion = true;
    }

    if (current_postion.x > rectSize.width - radius) {
        this->setPositionX(rectSize.width - radius);
        isCollsion = true;
    }

    // if y is out of rect
    if (current_postion.y < radius) {
        this->setPositionY(radius);
        isCollsion = true;
    }

    if (current_postion.y > rectStartPoint.y + rectSize.height - radius) {
        this->setPositionY(rectStartPoint.y + rectSize.height - radius);
        isCollsion = true;
    }

    return isCollsion;
}

