//
//  BaseCard.cpp
//  Air_Hockey
//
//  Created by hanks on 2013/10/28.
//
//

#include "BaseCard.h"

BaseCard::BaseCard() {
    
}

BaseCard::~BaseCard() {
    
}

BaseCard* BaseCard::create(const char *pszFileName) {
    BaseCard *sprite = new BaseCard();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}




