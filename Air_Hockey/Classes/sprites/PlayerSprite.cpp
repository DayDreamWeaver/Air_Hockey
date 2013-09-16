//
//  PlayerSprite.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/07.
//
//

#include "PlayerSprite.h"
#include "../utils/SoundManager.h"

PlayerSprite::PlayerSprite() {
    
}

PlayerSprite::~PlayerSprite() {
    
}

PlayerSprite* PlayerSprite::create(const char *pszFileName) {
    PlayerSprite *sprite = new PlayerSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void PlayerSprite::update(float dt) {
    /*
      Update player status

      Args:
        dt: float, interval between frame

      Returns:
        void
     */
    
    CCPoint nextPosition = this->getNextPosition();
    CCPoint currentVector = this->getVector();
    if (this->collisionWithSides(this->getWinRect(), nextPosition, currentVector)) {
        SoundManager::playSE(HIT_SE);
    }
    
}
