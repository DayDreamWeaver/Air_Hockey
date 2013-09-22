#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "../sprites/BallSprite.h"
#include "../sprites/PlayerSprite.h"

using namespace cocos2d;

#define GOAL_WIDTH 400

#define RED 1
#define GREEN 2
#define BLUE 3
#define NORMAL_BOLD 10
#define MAX_BOLD 20
#define MAX_BALL_SPEED 15
#define MIN_BALL_SPEED 5

enum {
    UP,
    DOWN,
};

enum {
    Foreground,
    Middleground,
    Background,
};

class GameLayer : public cocos2d::CCLayer
{

    // player object
    PlayerSprite * _player1;
    PlayerSprite * _player2;
    
    // ball object
    BallSprite * _ball;
    
    BaseSprite * _court;
    
    CCArray * _players;
    CCLabelTTF * _player1ScoreLabel;
    CCLabelTTF * _player2ScoreLabel;
    
    CCSize _screenSize;
    
    int _player1Score;
    int _player2Score;
    
    
    int _attackRangeDegree;
    // partical system
    CCParticleSystem * _jet;
    
    void updatePlayerScore(int player);
    
    // draw line between touch point and origin point
    void drawLine(CCPoint start, CCPoint end, int color, int boldDegree);
    // get gesture direction
    int getGestureDicrection(CCPoint start, CCPoint end, int playerIndex);
    // get acute angle of attack direction
    double getAcuteAngleOfAttack(CCPoint attack, CCPoint tap);
    // draw two lines show the attack angle range
    void drawAngleCheckLine();
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
    void reset(void);
    
};

#endif // __GAMELAYER_H__
