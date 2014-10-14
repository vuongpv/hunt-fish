//
//  ViewMenu.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
//#include "DiaryView.h"

using namespace cocos2d;
class ViewMenu : public cocos2d::CCLayer
{
public:
	ViewMenu(void);
	~ViewMenu(void);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void playGame(CCObject* pSender);
    void playGameOnline(CCObject* pSender);
    void diaryGame(CCObject *pSender);
    void downGame(CCObject *pSender);
    void shareGame(CCObject *pSender);
    void infoGame(CCObject *pSender);
    void exitGame(CCObject *pSender);
	void initExitMenu();
	void callExitMenu();
	void hiddenExitMenu();
	void acceptExit(CCObject *pSender);
	void cancelExit(CCObject *pSender);
    void hiddenAndUneableAllButton();
    void showAndEnableAllButton();
    void initDiary();
    void update(float dt);
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	CCSprite *exitMenu;
	CCSprite *spriteBg;
    CCMenuItem *butPlay,*butPlayOnline,*butDiary,*butInfo,*butExit,*butDownload,*butSound,*butShare,*buttonAcceptExit, *buttonCancelExit;
    int chooseAlert;
    bool callDiary;
//    DiaryView *diary;
    
    CREATE_FUNC(ViewMenu);
};