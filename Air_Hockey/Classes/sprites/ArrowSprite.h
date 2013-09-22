//
//  ArrowSprite.h
//  Air_Hockey
//
//  Created by hanks on 2013/09/22.
//
//

#ifndef __Air_Hockey__ArrowSprite__
#define __Air_Hockey__ArrowSprite__

#include "cocos2d.h"

using namespace cocos2d;

class ArrowSprite : public CCSprite {
public:
    ArrowSprite();
    ~ArrowSprite();
    static ArrowSprite *create(const char * pszFileName);
};


#endif /* defined(__Air_Hockey__ArrowSprite__) */
