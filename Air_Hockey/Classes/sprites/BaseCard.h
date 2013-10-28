//
//  BaseCard.h
//  Air_Hockey
//
//  Created by hanks on 2013/10/28.
//
//

#ifndef __Air_Hockey__BaseCard__
#define __Air_Hockey__BaseCard__

#include "BaseSprite.h"

using namespace cocos2d;

class BaseCard : public BaseSprite {
public:
    BaseCard();
    ~BaseCard();
    
    static BaseCard* create(const char * pszFileName);
};


#endif /* defined(__Air_Hockey__BaseCard__) */
