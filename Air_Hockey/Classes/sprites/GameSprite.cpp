//
//  GameSprite.cpp
//  Air Hockey
//
//  Created by hanks on 2013/08/21.
//
//

#include "GameSprite.h"

GameSprite::GameSprite(void) {
    _vector = ccp(0, 0);
}

GameSprite::~GameSprite(void) {
    
}

GameSprite * GameSprite::gameSpriteWithFile(const char * pszFilename) {
    GameSprite * sprite = new GameSprite();
    if (sprite && sprite->initWithFile(pszFilename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

GameSprite * GameSprite::gameSpriteWithFrameName(const char *pszFilename) {
    GameSprite * sprite = new GameSprite();
    if (sprite && sprite->initWithSpriteFrameName(pszFilename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void GameSprite::setPosition(const cocos2d::CCPoint &pos) {
    CCSprite::setPosition(pos);
    if (!_nextPositon.equals(pos)) {
        _nextPositon = pos;
    }
}

