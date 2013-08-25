#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define RED 1
#define NORMAL_BOLD 10
#define MAX_BOLD 200
#define MAX_SCALE 20

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    // show logo at the begining of game
    _isShowLogo = true;
    _player1Score = 0;
    _player2Score = 0;
    _screenSize = CCDirector::sharedDirector()->getWinSize();

    _court = GameSprite::gameSpriteWithFile("court.png");
    _court->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    // set Z value to -1, to set background to the bottom
    _court->setZOrder(-1);
    this->addChild(_court);
    
    _player1 = GameSprite::gameSpriteWithFile("mallet.png");
    _originalPoint1 = ccp(_screenSize.width * 0.5, _player1->radius() * 8);
    _player1->setPosition(_originalPoint1);
    this->addChild(_player1);
    
    _player2 = GameSprite::gameSpriteWithFile("mallet.png");
    _originalPoint2 = ccp(_screenSize.width * 0.5, _screenSize.height - _player2->radius() * 8);
    _player2->setPosition(_originalPoint2);
    
    this->addChild(_player2);
    
    _ball = GameSprite::gameSpriteWithFile("puck.png");
    _ball->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _ball->radius()));
    this->addChild(_ball);
    
    // keep player objects
    _players = CCArray::create(_player1, _player2, NULL);
    _players->retain();
    
    // label
    _player1ScoreLabel = CCLabelTTF::create("0", "Arial", 60);
    _player1ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 - 80));
    _player1ScoreLabel->setRotation(90);
    this->addChild(_player1ScoreLabel);
    
    _player2ScoreLabel = CCLabelTTF::create("0", "Arial", 60);
    _player2ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 + 80));
    _player2ScoreLabel->setRotation(90);
    this->addChild(_player2ScoreLabel);
    
    // logo
    _logo = GameSprite::gameSpriteWithFile("logo.png");
    _logo->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(_logo);
    
    // arrow
    _arrow1 = GameSprite::gameSpriteWithFile("arrow_1.png");
    this->addChild(_arrow1);
    
    
    if (_isShowLogo) {
        _court->setVisible(!_isShowLogo);
        _player1->setVisible(!_isShowLogo);
        _player2->setVisible(!_isShowLogo);
        _ball->setVisible(!_isShowLogo);
        _player1ScoreLabel->setVisible(!_isShowLogo);
        _player2ScoreLabel->setVisible(!_isShowLogo);
        _arrow1->setVisible(!_isShowLogo);
    }
    
    // listen to touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameSprite::update));
    
    return true;
}

void GameLayer::draw() {
    /* test to draw line
    if (!_isShowLogo) {
        // become bolder when distance become larger, and start NORMAL_BOLD to MAX_BOLD
        int blod_value_1 = (ccpDistance(_originalPoint1, _player1->getPosition()) / _screenSize.height) * MAX_BOLD;
        int blod_value_2 = (ccpDistance(_originalPoint2, _player2->getPosition()) / _screenSize.height) * MAX_BOLD;
        
        drawLine(_originalPoint1, _player1->getPosition(), RED, blod_value_1);
        drawLine(_originalPoint2, _player2->getPosition(), RED, blod_value_2);
    }
     */
}

void GameLayer::transformArrow(CCPoint start, CCPoint end) {
    // adjust scale
    float distance = ccpDistance(start, end);
    CCSize size = _arrow1->boundingBox().size;
    float scale = 0;
    
    if (distance > 0) {
        scale = distance / _screenSize.height / 2 * MAX_SCALE;
    }
    
    _arrow1->setScaleX(scale);
    
    // adjust angle
    float diffx = end.x - start.x;
    float diffy = end.y - start.y;
    
    float radian = -atan2(diffy, diffx);
    float angle = CC_RADIANS_TO_DEGREES(radian);
    
    _arrow1->setRotation(angle);
    
    // adjust position
    CCPoint middelPoint = get_middle_point(start, end);
    _arrow1->setPosition(middelPoint);

}
                         
CCPoint GameLayer::get_middle_point(CCPoint start, CCPoint end) {
    return ccp((start.x + end.x) / 2, (start.y + end.y) / 2);
}

void GameLayer::drawLine(CCPoint start, CCPoint end, int color, int bold) {
    // select color
    switch (color) {
        case RED:
            //red line from bottom left to top right corner
            ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
            break;
    }
    
    // set bold value of line
    if (bold < NORMAL_BOLD) {
        bold = NORMAL_BOLD;
    }
    glLineWidth(bold);

    // draw line
    ccDrawLine(start, end);
}

void GameLayer::update(float dt) {
    if (!_isShowLogo) {
        // should be visible
        _court->setVisible(!_isShowLogo);
        _player1->setVisible(!_isShowLogo);
        _player2->setVisible(!_isShowLogo);
        _ball->setVisible(!_isShowLogo);
        _player1ScoreLabel->setVisible(!_isShowLogo);
        _player2ScoreLabel->setVisible(!_isShowLogo);
        _arrow1->setVisible(!_isShowLogo);
        
        // should be unvisible
        _logo->setVisible(_isShowLogo);
        
        CCPoint ballNextPosition = _ball->getNextPosition();
        CCPoint ballVector = _ball->getVector();
        ballVector =  ccpMult(ballVector, 0.98f);

        ballNextPosition.x += ballVector.x;
        ballNextPosition.y += ballVector.y;

        GameSprite * player;
        CCPoint playerNextPosition;
        CCPoint playerVector;

        float squared_radii = pow(_player1->radius() + _ball->radius(), 2);
        for (int p = 0; p < _players->count(); p++) {
            player = (GameSprite *)_players->objectAtIndex(p);
            playerNextPosition = player->getNextPosition();
            playerVector = player->getVector();

            float diffx = ballNextPosition.x - player->getPositionX();
            float diffy = ballNextPosition.y - player->getPositionY();

            float distance1 = pow(diffx, 2) + pow(diffy, 2);
            float distance2 = pow(_ball->getPositionX() - playerNextPosition.x, 2) + 
                pow(_ball->getPositionY() - playerNextPosition.y, 2);

            if (distance1 <= squared_radii || distance2 <= squared_radii) {
                float mag_ball = pow(ballVector.x, 2) + pow(ballVector.y, 2);
                float mag_player = pow(playerVector.x, 2) + pow(playerVector.y, 2);

                float force = sqrt(mag_ball + mag_player);
                float angle = atan2(diffy, diffx);

                ballVector.x = force * cos(angle);
                ballVector.y = force * sin(angle);

                ballNextPosition.x = playerNextPosition.x + (player->radius() + _ball->radius() + force) * cos(angle);
                ballNextPosition.y = playerNextPosition.y + (player->radius() + _ball->radius() + force) * sin(angle);

                SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
            }
        }

        if (ballNextPosition.x < _ball->radius()) {
            ballNextPosition.x = _ball->radius();
            ballVector.x *= -0.8f;
            SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
        }

        if (ballNextPosition.x > _screenSize.width - _ball->radius()) {
            ballNextPosition.x = _screenSize.width - _ball->radius();
            ballVector.x *= -0.8f;
            SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
        }

        if (ballNextPosition.y > _screenSize.height - _ball->radius()) {
            if (_ball->getPosition().x < _screenSize.width * 0.5f - GOAL_WIDTH * 0.5f || 
                _ball->getPosition().x > _screenSize.width * 0.5f + GOAL_WIDTH * 0.5f ) {
                ballNextPosition.y = _screenSize.height - _ball->radius();
                ballVector.y *= -0.8f;
                SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
            }
        }

        if (ballNextPosition.y < _ball->radius()) {
            if (_ball->getPosition().x < _screenSize.width * 0.5f - GOAL_WIDTH * 0.5f ||
                _ball->getPosition().x > _screenSize.width * 0.5f + GOAL_WIDTH * 0.5f) {
                ballNextPosition.y = _ball->radius();
                ballVector.y *= -0.8f;
                SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
            }
        }

        _ball->setVector(ballVector);
        _ball->setNextPosition(ballNextPosition);

        // check for goals
        if (ballNextPosition.y < _ball->radius() * 2) {
            this->playerScore(2);
        }

        if (ballNextPosition.y > _screenSize.height + _ball->radius() * 2) {
            this->playerScore(1);
        }

        _player1->setPosition(_player1->getNextPosition());
        _player2->setPosition(_player2->getNextPosition());    
        _ball->setPosition(_ball->getNextPosition());
        
        // transform arrow
        this->transformArrow(_originalPoint1, _player1->getPosition());
    }
}

void GameLayer::springEffect(GameSprite * sprite, cocos2d::CCPoint start, cocos2d::CCPoint end) {
    float targetX = (end.x - start.x) * 2 + start.x;
    float targetY = (end.y - start.y) * 2 + start.y;
    
    CCActionInterval * actionTo = CCMoveTo::create(0.4, ccp(targetX, targetY));
    CCActionInterval * actionBack = CCMoveTo::create(0.15, _originalPoint1);
    
    _player1->runAction(CCSequence::create(actionTo, actionBack, NULL));
    printf("%f, %f", _player1->getVector().x, _player1->getVector().y);
}

void GameLayer::playerScore(int player) {
    SimpleAudioEngine::sharedEngine()->playEffect("score.wav");
    _ball->setVector(ccp(0, 0));
    
    // get back to original position
    char score_buffer[10];
    if (player == 1) {
        _player1Score++;
        sprintf(score_buffer, "%i", _player1Score);
        _player1ScoreLabel->setString(score_buffer);
        _ball->setNextPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 + 2 * _ball->radius()));
    } else {
        _player2Score++;
        sprintf(score_buffer, "%i", _player2Score);
        _player2ScoreLabel->setString(score_buffer);
        _ball->setNextPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _ball->radius()));
    }
    
    // clear touch obj
    _player1->setPosition(_originalPoint1);
    _player2->setPosition(_originalPoint2);
    _player1->setTouch(NULL);
    _player2->setTouch(NULL);
}

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
    CCSetIterator i;
    CCTouch* touch;
    CCPoint tap;
    GameSprite* player;
    
    _isShowLogo = false;
    printf("touch!!");
    
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < 2; p++) {
                player = (GameSprite *)_players->objectAtIndex(p);
                if (player->boundingBox().containsPoint(tap)) {
                    player->setTouch(touch);
                }
            }
        }
    }
    
}

void GameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event) {
    CCSetIterator i;
    CCTouch* touch;
    CCPoint tap;
    GameSprite* player;
    
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < _players->count(); p++) {
                player = (GameSprite *)_players->objectAtIndex(p);
                if (player->getTouch() != NULL && player->getTouch() == touch) {
                    CCPoint nextPosition = tap;
                    if (nextPosition.x < player->radius()) {
                        nextPosition.x = player->radius();
                    }
                    
                    if (nextPosition.x > _screenSize.width - player->radius()) {
                        nextPosition.x = _screenSize.width - player->radius();
                    }
                        
                    if (nextPosition.y < player->radius()) {
                        nextPosition.y = player->radius();
                    }
                        
                    if (nextPosition.y > _screenSize.height - player->radius()) {
                        nextPosition.y = _screenSize.height - player->radius();
                    }
                    
                    // keep player inside its court
                    if (player->getPositionY() < _screenSize.height * 0.5f) {
                        if (nextPosition.y > _screenSize.height * 0.5 - player->radius()) {
                            nextPosition.y = _screenSize.height * 0.5 - player->radius();
                        }
                    } else {
                        if (nextPosition.y < _screenSize.height * 0.5 + player->radius()) {
                            nextPosition.y = _screenSize.height * 0.5 + player->radius();
                        }
                    }
                    
                    player->setNextPosition(nextPosition);
                    player->setVector(ccp(tap.x - player->getPositionX(), tap.y - player->getPositionY()));
                }
            }
        }
    }
}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
    CCSetIterator i;
    CCTouch* touch;
    CCPoint tap;
    GameSprite* player;
    
    printf("end");
    
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < _players->count(); p++) {
                player = (GameSprite *)_players->objectAtIndex(p);
                
                if (player->getTouch() != NULL && player->getTouch() == touch) {
                    player->setTouch(NULL);
                    // need to keep its vector, because need to perform spring effect
                    //player->setVector(ccp(0, 0));
                    if (p == 0) {
                        // player 1
                        //player->setPosition(_originalPoint1);
                        // show spring effect
                        this->springEffect(_player1, tap, _originalPoint1);
                    } else {
                        // player 2
                        player->setPosition(_originalPoint2);
                    }
                }
            }
        }
    }

}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

GameLayer::~GameLayer() {
    CC_SAFE_RELEASE(_players);
}
