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

#define WEAK_RATIO 0.99f
#define REBOUND_RATIO -0.8f
#define MAX_BALL_SPEED 15
#define MIN_BALL_SPEED 5

enum {
    MIN_X,
    MAX_X,
    MIN_Y,
    MAX_y,
};

class BallSprite : public BaseSprite {
public:
    BallSprite(void);
    ~BallSprite(void);
    static BallSprite* create(const char *pszFileName);
    void collisionWithPlayer(BaseSprite* player);
    void update(float dt);
};

#endif /* defined(__Air_Hockey__BallSprite__) */
