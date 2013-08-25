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
    GameSprite * _arrow1;
    bool _isShowLogo;
    
    CCArray * _players;
    CCLabelTTF * _player1ScoreLabel;
    CCLabelTTF * _player2ScoreLabel;
    
    CCPoint _originalPoint1;
    CCPoint _originalPoint2;
    
    CCSize _screenSize;
    
    int _player1Score;
    int _player2Score;
    
    void playerScore(int player);
    
    // draw line between touch point and origin point
    void drawLine(CCPoint start, CCPoint end, int color, int boldDegree);
    
    // transform arrow according to player position
    void transformArrow(CCPoint start, CCPoint end);

    // count middel CCPoint
    CCPoint get_middle_point(CCPoint start, CCPoint end);
    
    // spring effect
    void springEffect(GameSprite * sprite, CCPoint start, CCPoint end);
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
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

    void update(float dt);
    virtual void draw();
    
};

#endif // __GAMELAYER_H__
