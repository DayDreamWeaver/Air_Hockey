//
//  ArrowSprite.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/09/22.
//
//

#include "ArrowSprite.h"

ArrowSprite::ArrowSprite() {

}

ArrowSprite::~ArrowSprite() {
    
}

ArrowSprite* ArrowSprite::create(const char *pszFileName) {
    ArrowSprite *sprite = new ArrowSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
