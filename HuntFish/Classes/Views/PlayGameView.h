//
//  PlayGameView.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//
#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"
#include "Gun.h"
#include "Web.h"
#include "cocos-ext.h"
#include "ShopView.h"
#include "Player.h"
#include "playGameViewOffline.h"



using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;

class PlayGameView: public cocos2d::CCLayer
{
public:
	PlayGameView(void);
	~PlayGameView(void);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
    
    void updateGame(float dt);
    void updateFish(float dt);
    void initBackGround();
	void addFish1();//add ca rat nhieu
	void addFish2();//add ca nhieu
	void addFish3();//add ca trung binh
	void addFish4();//add ca it
	void addFish5();//add ca rat it
    void initGun();
    void initPauseMenu();
    void initShop();
    void valueSoundBGChanged(CCObject* sender,unsigned int controlEvent);
    void valueSoundEffectChanged(CCObject* sender,unsigned int controlEvent);
    void callPauseMenu();
    void hiddenPauseMenu();
    void addBullet(float x, float y);
    void chooseFreeze(CCObject *pSender);
    void chooseBoom(CCObject *pSender);
    void chooseFood(CCObject *pSender);
    void chooseItem(CCObject *pSender);
    void chooseMinus(CCObject *pSender);
    void chooseMission(CCObject *pSender);
    void choosePause(CCObject *pSender);
    void choosePlus(CCObject *pSender);
    void exitGame(CCObject *pSender);
    void playContinue(CCObject *pSender);
    void hiddenEndUneableAllButton();
    void showAndEnableAllButton();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    /////PLAY ONLINE//////////////////////////
//    CCArray *_targets;
//    CCArray *_projectiles;
//    int _projectilesDestroyed;
//    Player *player;
//    Player *enemy;
//    int score;
//    bool isEnemyAdded;
//    bool isConnected;
//    std::string userName;
//
//    // there's no 'id' in cpp, so we recommend to return the class instance pointer
//    void connectToAppWarp();
//    // a selector callback
//    void startGame();
//    void updateEnemyStatus(cocos2d::CCPoint pos,float duration);
//    //void spriteMoveFinished(cocos2d::CCSprite* pSender);
//    void sendData(float x, float y, float duration);
//    
//    // preprocessor macro for "static create()" constructor ( node() deprecated )    
//    void onConnectDone(int res);

    //////////////////////////////////////////
    
    bool callShop;
    Gun *gun,*enemyGun;
    ShopView *shop;
    CCSprite *spriteBg, *actionBar, *toolBar, *levelBar, *pauseMenu;
    CCSprite *enemyActionBar;
    CCMenuItem *butItem, *butMission, *butBoom, *butFreeze, *butFood, *butMinus, *butPlus, *butPause, *butExit,*butPlayContinue;
    CCControlSlider *sliderSoundBG;
    CCControlSlider *sliderSoundEffect;
    
    float changePositionWidth;
    float changePositionHeight;
    int countTurtle, countShark;
    CCSize size;
    CREATE_FUNC(PlayGameView);
};
