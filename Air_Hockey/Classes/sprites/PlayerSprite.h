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

class PlayerSprite : public BaseSprite {
public:
    CC_SYNTHESIZE(CCPoint, _attackPoint, AttackPoint);
    PlayerSprite(void);
    ~PlayerSprite(void);
    static PlayerSprite* create(const char *pszFileName);
    void update(float dt);
};

#endif /* defined(__Air_Hockey__PlayerSprite__) */
