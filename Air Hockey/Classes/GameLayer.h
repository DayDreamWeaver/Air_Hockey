#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

#define GOAL_WIDTH 400

class GameLayer : public cocos2d::CCLayer
{
    // player object
    GameSprite * _player1;
    GameSprite * _player2;
    GameSprite * _ball;
    GameSprite * _logo;
    GameSprite * _court;
    bool _isShowLogo;
    
    CCArray * _players;
    CCLabelTTF * _player1ScoreLabel;
    CCLabelTTF * _player2ScoreLabel;
    
    CCSize _screenSize;
    
    int _player1Score;
    int _player2Score;
    
    void playerScore(int player);

public:
    
    ~GameLayer();
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    
    // touch handler
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesEnd(CCSet* pTouches, CCEvent* event);

    void update(float dt);
};

#endif // __GAMELAYER_H__
