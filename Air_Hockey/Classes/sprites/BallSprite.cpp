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
    this->reset();
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

bool BallSprite::collisionWithSides(const CCRect &winRect, CCPoint &nextPosition, CCPoint &currentVector) {
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
    
    // update position, nextPosition and vector 
    this->setNextPosition(nextPosition);
    this->setVector(currentVector);
    this->setPosition(this->getNextPosition());
}

void BallSprite::collisionWithPlayer(BaseSprite *player, CCPoint &nextPosition, CCPoint &currentVector) {
    /*
     Logic process for collision with player sprite
     
     Args:
       player: base sprite pointer.
     
     Returns:
       void
     */
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
        float magtitudeBallVector = pow(currentVector.x, 2) + pow(currentVector.y , 2);
        float magtitudePlayerVector = pow(playerVector.x, 2) + pow(playerVector.y, 2);
        
        float force = sqrt(magtitudeBallVector + magtitudePlayerVector);
        float angle = atan2(diffx1, diffy1);
        
        // control ball speed
        if (force >= MAX_BALL_SPEED) {
            force = MAX_BALL_SPEED;
        } else if (force <= MIN_BALL_SPEED) {
            force = MIN_BALL_SPEED;
        }
        
        currentVector.x = force * cos(angle);
        currentVector.y = force * sin(angle);
        
        nextPosition.x = playerNextPosition.x + (player->getRadius() + this->getRadius() + force) * cos(angle);
        nextPosition.y = playerNextPosition.y + (player->getRadius() + this->getRadius() + force) * sin(angle);
        
        SoundManager::playSE(HIT_SE);
        
        // update ball positionssre
        this->setNextPosition(nextPosition);
        this->setVector(currentVector);
    }
}

void BallSprite::reset() {
    this->setVector(ccp(0, 0));
}
