//
//  PlayerSprite.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/07.
//
//

#include "PlayerSprite.h"
#include "../utils/SoundManager.h"
#include "ArrowSprite.h"

PlayerSprite::PlayerSprite() {
    this->arrow = ArrowSprite::create("arrow_8.png");
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
    this->collisionWithSides(this->getWinRect(), nextPosition, currentVector);
    
    // udpate position of player
    this->setNextPosition(nextPosition);
    this->setVector(currentVector);
    this->setPosition(this->getNextPosition());
}

bool PlayerSprite::collisionWithSides(const CCRect &winRect, CCPoint &nextPosition, CCPoint &currentVector) {
    bool isCollision = false;
    if (nextPosition.x < this->getRadius()) {
        nextPosition.x = this->getRadius();
        isCollision = true;
    }
    
    if (nextPosition.x > _screenSize.width - this->getRadius()) {
        nextPosition.x = _screenSize.width - this->getRadius();
        isCollision = true;
    }
    return isCollision;
}

void PlayerSprite::reset() {
    this->setPosition(this->getStartPoint());
    this->setTouch(NULL);
}

