#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

#define GOAL_WIDTH 400

#define RED 1
#define NORMAL_BOLD 10
#define MAX_BOLD 20
#define MAX_SCALE 20
#define MAX_BALL_SPEED 15
#define MIN_BALL_SPEED 5

#define HIT_SE "hit.wav"
#define SCORE_SE "score.wav"
#define ATTACK_READY_SE "attack_ready.wav"
#define BGM "background.mp3"

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
    GameSprite * _player1;
    GameSprite * _player2;
    GameSprite * _ball;
    GameSprite * _logo;
    GameSprite * _court;
    GameSprite * _arrow1;
    GameSprite * _arrow2;
    bool _isShowLogo;
    
    // player attack start position
    CCPoint _attackPoint1;
    CCPoint _attackPoint2;
    
    CCArray * _players;
    CCLabelTTF * _player1ScoreLabel;
    CCLabelTTF * _player2ScoreLabel;
    
    CCPoint _originalPoint1;
    CCPoint _originalPoint2;
    
    CCSize _screenSize;
    
    int _player1Score;
    int _player2Score;
    
    int _originalPlayer1Y;
    int _originalPlayer2Y;
    
    // partical system
    CCParticleSystem * _jet;
    
    void updatePlayerScore(int player);
    
    // draw line between touch point and origin point
    void drawLine(CCPoint start, CCPoint end, int color, int boldDegree);
    
    // transform arrow according to player position
    void transformArrow(GameSprite * arrow, CCPoint start, CCPoint end);

    // count middel CCPoint
    CCPoint getMiddlePoint(CCPoint start, CCPoint end);
    
    // spring effect
    void doSpringEffect(GameSprite * sprite, CCPoint start, CCPoint end);
    
    // get gesture direction
    int getGestureDicrection(CCPoint start, CCPoint end, int playerIndex);
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
