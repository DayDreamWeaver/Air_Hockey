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
    this->arrow = ArrowSprite::create("arrow_8.png");
    this->reset();
}

PlayerSprite::~PlayerSprite() {
    
}

ArrowSprite* PlayerSprite::getArrow() {
    return this->arrow;
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
    
    // update arrow
    this->transferArrow();
}

void PlayerSprite::doSpringEffect(cocos2d::CCPoint start, cocos2d::CCPoint end, CCCallFuncN *callBackFunc) {
    float targetX = (end.x - start.x) * 2.5 + start.x;
    float targetY = (end.y - start.y) * 2.5 + start.y;
    
    CCActionInterval * actionTo = CCMoveTo::create(0.4, ccp(targetX, targetY));
    CCActionInterval * actionBack = CCMoveTo::create(0.15, end);
    
    this->runAction(CCSequence::create(actionTo, actionBack, callBackFunc, NULL));
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

void PlayerSprite::transferArrow() {
    CCPoint start = this->getAttackPoint();
    CCPoint end = this->getPosition();
    // adjust scale
    if (arrow->isVisible()) {
        float distance = ccpDistance(start, end);
        CCSize size = arrow->boundingBox().size;
        float scale = 0;
        
        if (distance > 0) {
            scale = distance / _screenSize.height / 2 * MAX_SCALE;
        }
        
        arrow->setScaleX(scale);
        
        // adjust angle
        float diffx = end.x - start.x;
        float diffy = end.y - start.y;
        
        float radian = -atan2(diffy, diffx);
        float angle = CC_RADIANS_TO_DEGREES(radian);
        
        arrow->setRotation(angle);
        
        // adjust position
        arrow->setPosition(ccpMidpoint(start, end));
    }

}

void PlayerSprite::reset() {
    this->setPosition(this->getStartPoint());
    this->setTouch(NULL);
    this->arrow->setVisible(false);
    this->arrow->setPosition(this->getStartPoint());
}

