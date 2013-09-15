#include "GameLayer.h"
#include "../utils/SoundManager.h"
#include "../sprites/PlayerSprite.h"
#include "../sprites/BallSprite.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
    
    // player background
    SoundManager::playBGM();
    
    // show logo at the begining of game
    _isShowLogo = true;
    _player1Score = 0;
    _player2Score = 0;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    // init original player 1 and 2's position Y
    _originalPlayer1Y = _screenSize.height / 4;
    _originalPlayer2Y = _screenSize.height - _originalPlayer1Y;
    
    _court = BaseSprite::gameSpriteWithFile("court.png");
    _court->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    // set Z value to -1, to set background to the bottom
    _court->setZOrder(-1);
    this->addChild(_court);
    
    // create ball sprite
    _player1 = BaseSprite::gameSpriteWithFile("mallet.png");
    _originalPoint1 = ccp(_screenSize.width * 0.5, _originalPlayer1Y);
    _player1->setPosition(_originalPoint1);
    this->addChild(_player1);
    
    _player2 = BaseSprite::gameSpriteWithFile("mallet.png");
    _originalPoint2 = ccp(_screenSize.width * 0.5, _originalPlayer2Y);
    _player2->setPosition(_originalPoint2);
    this->addChild(_player2);
    
    // init attack point
    _attackPoint1 = _originalPoint1;
    _attackPoint2 = _originalPoint2;
    
    ////////////////////////
    // init ball sprite //
    ////////////////////////
    _ball = BallSprite::create("puck.png");
    _ball->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _ball->getRadius()));
    CCRect ballWinRect = CCRect(0, 0, DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
    _ball->setWinRect(ballWinRect);
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
    _logo = BaseSprite::gameSpriteWithFile("logo.png");
    _logo->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
    this->addChild(_logo);
    
    // arrow
    _arrow1 = BaseSprite::gameSpriteWithFile("arrow_8.png");
    this->addChild(_arrow1);
    _arrow2 = BaseSprite::gameSpriteWithFile("arrow_2.png");
    this->addChild(_arrow2);
        
    // partcal system
    _jet = CCParticleSystemQuad::create("cool.plist");
    _jet->setPosition(_ball->getPosition());
    //_jet->setSourcePosition(ccp(-_ball->getRadius() * 1.0f, 0));
    _jet->setAngle(270);
    _jet->stopSystem();
    this->addChild(_jet, Background);
    
    if (_isShowLogo) {
        _court->setVisible(!_isShowLogo);
        _player1->setVisible(!_isShowLogo);
        _player2->setVisible(!_isShowLogo);
        _ball->setVisible(!_isShowLogo);
        _player1ScoreLabel->setVisible(!_isShowLogo);
        _player2ScoreLabel->setVisible(!_isShowLogo);
        _arrow1->setVisible(!_isShowLogo);
        _arrow2->setVisible(!_isShowLogo);
    }
    
    // listen to touch
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(BaseSprite::update));
    
    return true;
}

void GameLayer::draw() {
    //test to draw line of player's fixed track
    if (!_isShowLogo) {
        // become bolder when distance become larger, and start NORMAL_BOLD to MAX_BOLD
        int blod_value_1 = 0.5 * MAX_BOLD;
        int blod_value_2 = 0.5 * MAX_BOLD;
        
        drawLine(ccp(0, _originalPlayer1Y), ccp(_screenSize.width, _originalPlayer1Y), RED, blod_value_1);
        drawLine(ccp(0, _originalPlayer2Y), ccp(_screenSize.width, _originalPlayer2Y), RED, blod_value_2);
    }
    
}

void GameLayer::transformArrow(BaseSprite * arrow, CCPoint start, CCPoint end) {
    // adjust scale
    if (arrow->isVisible()) {
        float distance = ccpDistance(start, end);
        CCSize size = arrow->boundingBox().size;
        float scale = 0;
        
        if (distance > 0) {
            scale = distance / _screenSize.height / 2 * MAX_SCALE;
        }
        
        arrow->setScaleX(scale);
        
        // adjust angle
        float diffx = end.x - start.x;
        float diffy = end.y - start.y;
        
        float radian = -atan2(diffy, diffx);
        float angle = CC_RADIANS_TO_DEGREES(radian);
        
        arrow->setRotation(angle);
        
        // adjust position
        arrow->setPosition(ccpMidpoint(start, end));
    }
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
        
        // should be unvisible
        _logo->setVisible(_isShowLogo);

        // update player's position
        BaseSprite * player;
        // simple collision detect
        for (int p = 0; p < _players->count(); p++) {
            player = (BaseSprite *)_players->objectAtIndex(p);
            _ball->collisionWithPlayer(player);
        }
        
        _ball->update(dt);
        
        
        // update jet partical position
        if (!_jet->isActive()) {
            _jet->resetSystem();
        }
        
        _jet->setPosition(_ball->getPosition());
        _jet->setRotation(_ball->getRotation());

        // check for goals
        /*
        if (ballNextPosition.y < _ball->getRadius() * 2) {
            this->updatePlayerScore(2);
        }

        if (ballNextPosition.y > _screenSize.height + _ball->getRadius() * 2) {
            this->updatePlayerScore(1);
        }
         */

        // update player's position
        _player1->setPosition(_player1->getNextPosition());
        _player2->setPosition(_player2->getNextPosition());    
        //_ball->setPosition(_ball->getNextPosition());
        
        // transform arrow
        this->transformArrow(_arrow1, _attackPoint1, _player1->getPosition());
        this->transformArrow(_arrow2, _attackPoint2, _player2->getPosition());
    }
}

void GameLayer::doSpringEffect(BaseSprite * sprite, cocos2d::CCPoint start, cocos2d::CCPoint end) {
    float targetX = (end.x - start.x) * 2.5 + start.x;
    float targetY = (end.y - start.y) * 2.5 + start.y;
    
    CCActionInterval * actionTo = CCMoveTo::create(0.4, ccp(targetX, targetY));
    CCActionInterval * actionBack = CCMoveTo::create(0.15, end);
   
    sprite->runAction(CCSequence::create(actionTo, actionBack, NULL));
    printf("%f, %f", sprite->getVector().x, sprite->getVector().y);

}

int GameLayer::getGestureDicrection(cocos2d::CCPoint start, cocos2d::CCPoint end, int playerIndex) {
    CCAssert(playerIndex == 0 or playerIndex == 1, "player index is fiexed as 0 or 1");
    int result = -1;
    switch (playerIndex) {
        case 0:
            // player 1
            if (end.y >= start.y) {
                result = UP;
            } else {
                result = DOWN;
            }
            break;
        case 1:
            // player 2
            if (end.y >= start.y) {
                result = DOWN;
            } else {
                result = UP;
            }
            break;
        default:
            break;
    }
    return result;
}

void GameLayer::updatePlayerScore(int player) {
    SoundManager::playSE(SCORE_SE);
    _ball->setVector(ccp(0, 0));
    
    // get back to original position
    char score_buffer[10];
    if (player == 1) {
        _player1Score++;
        sprintf(score_buffer, "%i", _player1Score);
        _player1ScoreLabel->setString(score_buffer);
        _ball->setNextPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 + 2 * _ball->getRadius()));
    } else {
        _player2Score++;
        sprintf(score_buffer, "%i", _player2Score);
        _player2ScoreLabel->setString(score_buffer);
        _ball->setNextPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _ball->getRadius()));
    }
    
    // clear touch obj and set player to origin position
    _player1->setPosition(_originalPoint1);
    _player2->setPosition(_originalPoint2);
    _player1->setTouch(NULL);
    _player2->setTouch(NULL);
    _arrow1->setVisible(false);
    _arrow2->setVisible(false);
}

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
    CCSetIterator i;
    CCTouch* touch;
    CCPoint tap;
    BaseSprite* player;
    
    _isShowLogo = false;
    
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < 2; p++) {
                player = (BaseSprite *)_players->objectAtIndex(p);
                // if touch on player, set touch object onto player
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
    BaseSprite* player;
    int direction = -1;
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < _players->count(); p++) {
                player = (BaseSprite *)_players->objectAtIndex(p);
                // if player contains a touch
                if (player->getTouch() != NULL && player->getTouch() == touch) {
                    CCPoint nextPosition = tap;
                    switch (p) {
                            // detect gesture for player 1, make y position a little lower than original position
                        case 0:
                            direction = this->getGestureDicrection(ccp(_originalPoint1.x, _originalPoint1.y - _ball->getRadius()), tap, p);
                            break;
                        case 1:
                            // detect gesture for player 2, make y position a little higher than original position
                            direction = this->getGestureDicrection(ccp(_originalPoint2.x, _originalPoint2.y + _ball->getRadius()), tap, p);
                            break;
                    }
                    // if touch is out of court, push it back
                    if (nextPosition.x < player->getRadius()) {
                        nextPosition.x = player->getRadius();
                    }
                    
                    if (nextPosition.x > _screenSize.width - player->getRadius()) {
                        nextPosition.x = _screenSize.width - player->getRadius();
                    }
                        
                    if (nextPosition.y < player->getRadius()) {
                        nextPosition.y = player->getRadius();
                    }
                        
                    if (nextPosition.y > _screenSize.height - player->getRadius()) {
                        nextPosition.y = _screenSize.height - player->getRadius();
                    }
                    
                    if (player->getPositionY() < _screenSize.height * 0.5f) {
                        // update player 1's position Y
                        switch (direction) {
                            case UP:
                                nextPosition.y = _originalPlayer1Y;
                                _arrow1->setVisible(false);
                                // update attack start position
                                _attackPoint1 = player->getPosition();
                                printf("UP\n");
                                break;
                            case DOWN:
                                _arrow1->setVisible(true);
                                printf("DOWN\n");
                                break;
                            default:
                                break;
                        }
                                                
                    } else {
                        // update player 2's position Y
                        switch (direction) {
                            case UP:
                                nextPosition.y = _originalPlayer2Y;
                                _arrow2->setVisible(false);
                                // update attack start position
                                _attackPoint2 = player->getPosition();
                                break;
                            case DOWN:
                                _arrow2->setVisible(true);
                                break;
                            default:
                                break;
                        }
                    }
                    
                    // update position and vector to player
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
    BaseSprite* player;
    
    printf("end");
    
    for (i = pTouches->begin(); i != pTouches->end(); i++) {
        touch = (CCTouch *)(*i);
        if (touch) {
            tap = touch->getLocation();
            for (int p = 0; p < _players->count(); p++) {
                player = (BaseSprite *)_players->objectAtIndex(p);
                
                if (player->getTouch() != NULL && player->getTouch() == touch) {
                    player->setTouch(NULL);
                    // need to keep its vector, because need to perform spring effect
                    if (p == 0) {
                        // player 1
                        player->setPosition(_attackPoint1);
                        // show spring effect
                        if (_arrow1->isVisible()) {
                            this->doSpringEffect(_player1, tap, _attackPoint1);
                        }
                    } else {
                        // player 2
                        player->setPosition(_attackPoint2);
                        // show spring effect
                        if (_arrow2->isVisible()) {
                            this->doSpringEffect(_player2, tap, _attackPoint2);
                        }
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
