//
//  BallSprite.h
//  Air_Hockey
//
//  Created by hanks on 2013/09/07.
//
//

#ifndef __Air_Hockey__BallSprite__
#define __Air_Hockey__BallSprite__

#include "BaseSprite.h"

using namespace cocos2d;

#define WEAK_RATIO 0.99f
#define REBOUND_RATIO -0.8f
#define MAX_BALL_SPEED 15
#define MIN_BALL_SPEED 5

class BallSprite : public BaseSprite {
public:
    BallSprite(void);
    ~BallSprite(void);
    static BallSprite* create(const char *pszFileName);
    void collisionWithPlayer(BaseSprite* player, CCPoint &nextPosition, CCPoint &currentVector);
    void update(float dt);
    bool collisionWithSides(const CCRect &winRect, CCPoint &nextPosition, CCPoint &currentVector);
    void reset(void);
};

#endif /* defined(__Air_Hockey__BallSprite__) */
