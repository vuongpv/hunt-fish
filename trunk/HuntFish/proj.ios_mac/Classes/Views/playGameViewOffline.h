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
#include "ItemHunt.h"


using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;

class PlayGameViewOffline: public cocos2d::CCLayer
{
public:
	PlayGameViewOffline(void);
	~PlayGameViewOffline(void);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
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
	void initMissionMenu();
	void initItem();
	void initExitMenu();
    void valueSoundBGChanged(CCObject* sender,CCControlEvent);
    void valueSoundEffectChanged(CCObject* sender,CCControlEvent);
    void callPauseMenu();
	void callMissionMenu();
    void hiddenPauseMenu();
	void callExitMenu();
	void hiddenExitMenu();
    void addBullet(float x, float y);
    void chooseItem(CCObject *pSender);
    void chooseMinus(CCObject *pSender);
    void chooseMission(CCObject *pSender);
    void choosePause(CCObject *pSender);
    void choosePlus(CCObject *pSender);
    void shotPower(CCObject *pSender);
    void exitGame(CCObject *pSender);
    void playContinue(CCObject *pSender);
	void acceptMission(CCObject *pSender);
	void acceptExit(CCObject *pSender);
	void cancelExit(CCObject *pSender);
    void hiddenEndUneableAllButton();
	void hiddenMissionMenu();
    void showAndEnableAllButton();
    void resumeFishStop(CCNode* sender, void *fish);
	void resumeFishStopEatBread();
	void loadLevel();
	void checkFishSpecial(Fish *fish);
	void loadCheckFish();
	void setCheckFish();
    int loadCheckGuns();
    void setCheckGuns();
    void loadCheckItem();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    bool callShop;
    Gun *gun;
    ShopView *shop;
	ItemHunt *freeze,*bomb,*food, *freezeMove,*bombMove,*foodMove;

    CCSprite *spriteBg, *actionBar, *toolBar, *levelBar, *pauseMenu, *missionMenu, *exitMenu;
    CCMenuItem *butItem, *butMission, *butMinus, *butPlus, *butPause, *butExit,*butPlayContinue, *buttonAcceptMission, *buttonAcceptExit, *buttonCancelExit, *buttonShotPower;
    CCLabelBMFont *labelTime, *labelCoin;
    CCProgressTimer *powerBar, *levelSlice;

    float changePositionWidth;
    float changePositionHeight;
    int countTurtle, countShark, countFisher, timeCount, coinCount,levelGamePlay;
	float energyCount,levelCount,ranger;
	bool chooseItemHunt;
	//Cac bien check ca dac biet
	int checkFish5; //100 ca nhan 2 diem trong 30 phat
	int checkFish10;//100 rua duoc ban sung cuc dai
	int checkFish11;//20 blue shark duoc ban 100 dan bang giam toc do
	int checkFish12;//30 yellow shark duoc x2 dame cho sung trong 30 phat
	int checkFish13;//100 ca duoc tang ngau nhien vat pham
	int checkFish1; //500 ca thi xuat hien dan ca loai 19
    int numBoom, numFreeze, numBread;
    
    CREATE_FUNC(PlayGameViewOffline);
};



/****NOTE TAG OBJECTS IN SPRITES*****
fish -10,-20,-30,-40.-50
gun 0
bullet tag >= 100;
bomb -5
freeze -5
bread -5

************************************/
