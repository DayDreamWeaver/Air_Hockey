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
    if (this->collisionWithSides(this->getWinRect(), nextPosition, currentVector)) {
        SoundManager::playSE(HIT_SE);
    }
    
    this->setNextPosition(nextPosition);
    this->setVector(currentVector);
    this->setPosition(this->getNextPosition());
}

void BallSprite::collisionWithPlayer(BaseSprite *player) {
    /*
     Logic process for collision with player sprite
     
     Args:
       player: base sprite pointer.
     
     Returns:
       void
     */
    CCPoint nextPosition = this->getNextPosition();
    CCPoint vector = this->getVector();
    
    CCPoint playerNextPosition = player->getNextPosition();
    CCPoint playerVector = player->getVector();
    
    
    float diffx1 = nextPosition.x - player->getPositionX();
    float diffy1 = nextPosition.y - player->getPositionY();
    float distance1 = pow(diffx1, 2) + pow(diffy1, 2);
    
    float diffx2 = this->getPosition().x - player->getNextPosition().x;
    float diffy2 = this->getPosition().y - player->getNextPosition().y;
    float distance2 = pow(diffx2, 2) + pow(diffy2, 2);
                       
    float shortestCollisionDistance = pow(this->getRadius(), 2) + pow(player->getRadius(), 2);

    if (distance1 <= shortestCollisionDistance || distance2 <= shortestCollisionDistance) {
        float magtitudeBallVector = pow(vector.x, 2) + pow(vector.y , 2);
        float magtitudePlayerVector = pow(playerVector.x, 2) + pow(playerVector.y, 2);
        
        float force = sqrt(magtitudeBallVector + magtitudePlayerVector);
        float angle = atan2(diffx1, diffy1);
        
        // control ball speedp
        if (force >= MAX_BALL_SPEED) {
            force = MAX_BALL_SPEED;
        } else if (force <= MIN_BALL_SPEED) {
            force = MIN_BALL_SPEED;
        }
        
        vector.x = force * cos(angle);
        vector.y = force * sin(angle);
        
        nextPosition.x = playerNextPosition.x + (player->getRadius() + this->getRadius() + force) * cos(angle);
        nextPosition.y = playerNextPosition.y + (player->getRadius() + this->getRadius() + force) * sin(angle);
        
        SoundManager::playSE(HIT_SE);
        
    }
    
    // apply position change
    this->setNextPosition(nextPosition);
    this->setVector(vector);
}
