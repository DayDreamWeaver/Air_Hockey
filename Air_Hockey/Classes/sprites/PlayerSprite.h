//
//  PlayerSprite.h
//  Air_Hockey
//
//  Created by hanks on 2013/09/07.
//
//

#ifndef __Air_Hockey__PlayerSprite__
#define __Air_Hockey__PlayerSprite__

#include "cocos2d.h"
#include "BaseSprite.h"

using namespace cocos2d;

enum {
    P1,
    P2,
};

class PlayerSprite : public BaseSprite {
public:
    CC_SYNTHESIZE(CCPoint, _attackPoint, AttackPoint);
    CC_SYNTHESIZE(int, _playerIndex, PlayerIndex);
    CC_SYNTHESIZE(CCPoint, _startPoint, StartPoint);
    PlayerSprite(void);
    ~PlayerSprite(void);
    static PlayerSprite* create(const char *pszFileName);
    void update(float dt);
    bool collisionWithSides(const CCRect &winRect, CCPoint &nextPosition, CCPoint &currentVector);
    void reset();
};

#endif /* defined(__Air_Hockey__PlayerSprite__) */
