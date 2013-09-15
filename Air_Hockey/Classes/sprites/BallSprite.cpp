//
//  BallSprite.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/07.
//
//

#include "BallSprite.h"
#include "../utils/SoundManager.h"

BallSprite::BallSprite() {
    
}

BallSprite::~BallSprite() {
    
}

BallSprite* BallSprite::create(const char* pszFileName) {
    /*
     Create sprite with image file name.
     
     Args:
       pszFileName: char *, string of file name
     
     Returns:
       BallSprite *
     */
    BallSprite *sprite = new BallSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void BallSprite::update(float dt) {
    /*
     Update ball sprite status
     */
    CCPoint nextPosition = this->getNextPosition();
    CCPoint currentVector = this->getVector();
    // vector become slower according with time
    currentVector = ccpMult(currentVector, WEAK_RATIO);
    
    // update next position of sprite
    nextPosition.x += currentVector.x;
    nextPosition.y += currentVector.y;

    // check collision with bound of screen
    if (this->isCollisionWithSides(this->getWinRect())) {
        currentVector = ccpMult(currentVector, REBOUND_RATIO);
        SoundManager::playSE(HIT_SE);
    }
    
    this->setPosition(nextPosition);
    this->setVector(currentVector);
}

void BallSprite::collisionWithPlayer(BaseSprite *player) {
    /*
     Logic process for collision with player sprite
     
     Args:
       player: base sprite pointer.
     
     Returns:
       void
     */
    CCPoint ballNextPosition = this->getNextPosition();
    CCPoint ballVector = this->getVector();
    
    CCPoint playerNextPosition = player->getNextPosition();
    CCPoint playerVector = player->getVector();
    
    
    float diffx1 = ballNextPosition.x - player->getPositionX();
    float diffy1 = ballNextPosition.y - player->getPositionY();
    float distance1 = pow(diffx1, 2) + pow(diffy1, 2);
    
    float diffx2 = this->getPosition().x - player->getNextPosition().x;
    float diffy2 = this->getPosition().y - player->getNextPosition().y;
    float distance2 = pow(diffx2, 2) + pow(diffy2, 2);
                       
    float shortestCollisionDistance = pow(this->getRadius(), 2) + pow(player->getRadius(), 2);

    if (distance1 <= shortestCollisionDistance || distance2 <= shortestCollisionDistance) {
        float magtitudeBallVector = pow(ballVector.x, 2) + pow(ballVector.y , 2);
        float magtitudePlayerVector = pow(playerVector.x, 2) + pow(playerVector.y, 2);
        
        float force = sqrt(magtitudeBallVector + magtitudePlayerVector);
        float angle = atan2(diffx1, diffy1);
        
        // control ball speedp
        if (force >= MAX_BALL_SPEED) {
            force = MAX_BALL_SPEED;
        } else if (force <= MIN_BALL_SPEED) {
            force = MIN_BALL_SPEED;
        }
        
        ballVector.x = force * cos(angle);
        ballVector.y = force * sin(angle);
        
        ballNextPosition.x = playerNextPosition.x + (player->getRadius() + this->getRadius() + force) * cos(angle);
        ballNextPosition.y = playerNextPosition.y + (player->getRadius() + this->getRadius() + force) * sin(angle);
        
        SoundManager::playSE(HIT_SE);
        
    }
    
}
