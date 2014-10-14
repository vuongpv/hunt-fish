//
//  ViewMenu.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "ViewMenu.h"
#include "LinkResources.h"
//#include "PlayGameView.h"
#include "playGameViewOffline.h"

CCScene* ViewMenu::scene(){
	CCScene *scene=NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		ViewMenu *layer = ViewMenu::create();
        
		CC_BREAK_IF(! layer);
        // add layer as a child to scene
        scene->addChild(layer);
	}
	while(0);
	return scene;
}

bool ViewMenu::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCLayer::init());
        
        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        
        // Get window size and place the label upper.
        CCSize size = CCDirector::sharedDirector()->getWinSize();
                
        spriteBg      = CCSprite::create(BGPLAY7);
        CC_BREAK_IF(!spriteBg);

        CCSprite *spriteLogo    = CCSprite::create(LOGO);
        CC_BREAK_IF(!spriteLogo);
        
        this->addChild(spriteBg,0);
        
        spriteBg->setPosition(ccp(size.width/2,size.height/2));
        
		//init button in menu view
		butPlay         = CCMenuItemImage ::create (BUTPLAY,BUTPLAYPRESS,this,menu_selector(ViewMenu::playGame));
		CC_BREAK_IF(! butPlay);
        
		butPlayOnline	= CCMenuItemImage ::create (BUTPLAYONLINE,BUTPLAYONLINEPRESS,this,menu_selector(ViewMenu::playGameOnline));
		CC_BREAK_IF(! butPlayOnline);
        
		butInfo         = CCMenuItemImage ::create (BUTINFO,BUTINFOPRESS,this,menu_selector(ViewMenu::infoGame));
		CC_BREAK_IF(! butInfo);
        
		butExit         = CCMenuItemImage ::create (BUTEXIT, BUTEXITPRESS,this,menu_selector(ViewMenu::exitGame));
		CC_BREAK_IF(! butExit);
        
        butShare      = CCMenuItemImage ::create (BUTSHARE, BUTSHAREPRESS, this, menu_selector(ViewMenu::shareGame));
        CC_BREAK_IF(! butShare);
        
        butDownload      = CCMenuItemImage ::create (BUTDOWN, BUTDOWNPRESS, this, menu_selector(ViewMenu::downGame));
        CC_BREAK_IF(! butShare);
		
        butDiary      = CCMenuItemImage ::create (BUTDIARY, BUTDIARYPRESS, this, menu_selector(ViewMenu::diaryGame));
        CC_BREAK_IF(! butDiary);
		
        
		CCMenu *menuGame = CCMenu::create(butPlayOnline,butPlay,butDiary,butDownload,butShare,butInfo,butExit, NULL);
        menuGame->setPosition(CCPointZero);
        CC_BREAK_IF(!menuGame);
        
        spriteBg->addChild(spriteLogo);
        spriteBg->addChild(menuGame);
        
        spriteLogo->setPosition(ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2 + 100));
        butPlay->setPosition(ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2 - 70));
        butPlayOnline->setPosition(ccp(spriteBg->getContentSize().width/2 - 140,spriteBg->getContentSize().height/2 - 180));
        butDiary->setPosition(ccp(spriteBg->getContentSize().width/2 + 140,spriteBg->getContentSize().height/2 - 180));
        butDownload->setPosition(ccp(spriteBg->getContentSize().width - 60, spriteBg->getContentSize().height - 100));
        butShare->setPosition(ccp(spriteBg->getContentSize().width - 60, spriteBg->getContentSize().height - 190));
        butInfo->setPosition(ccp(spriteBg->getContentSize().width - 60, spriteBg->getContentSize().height - 280));
        butExit->setPosition(ccp(spriteBg->getContentSize().width - 60, spriteBg->getContentSize().height - 370));
        
        spriteBg->setScaleX(size.width/spriteBg->getContentSize().width);
        spriteBg->setScaleY(size.height/spriteBg->getContentSize().height);

		this->initExitMenu();
        this->initDiary();
        this->schedule(schedule_selector(ViewMenu::update), 0.2f);
        bRet = true;
    } while (0);
    
    return bRet;
}

//update khi goi xem nhat ki san bat ca
void ViewMenu::update(float dt){
//    if(this->callDiary && !this->diary->isEnable){
//        this->callDiary = false;
//        this->showAndEnableAllButton();
//    }
}

void ViewMenu::initDiary(){
//    this->callDiary = false;
//    this->diary = DiaryView::createDiary(CCString::createWithFormat(DIARYBG));
//    this->diary->init();
//    this->spriteBg->addChild(this->diary,15);
//    this->diary->setPosition(ccp(this->spriteBg->getContentSize().width/2, this->spriteBg->getContentSize().height + 250));
}

void ViewMenu::playGame(CCObject *pSender){
    CCLog("SINGLE PLAYER");
    CCTransitionTurnOffTiles *trans = CCTransitionTurnOffTiles::create(1.0f, PlayGameViewOffline::scene());
    CCDirector::sharedDirector()->replaceScene(trans);
}

void ViewMenu::playGameOnline(CCObject *pSender){
//    CCLog("MULTI PLAYER");
//    CCTransitionTurnOffTiles *trans = CCTransitionTurnOffTiles::create(1.0f, PlayGameView::scene());
//    CCDirector::sharedDirector()->replaceScene(trans);
}

void ViewMenu::infoGame(CCObject *pSender){
    
}

void ViewMenu::shareGame(CCObject *pSender){
    
}

void ViewMenu::downGame(CCObject *pSender){
    
}

void ViewMenu::diaryGame(CCObject *pSender){
//    if(!this->diary->isEnable){
//        this->callDiary = true;
//        this->hiddenAndUneableAllButton();
//        this->diary->appearDiary(this->spriteBg->getContentSize().height/2);
//    }
}

///////////////////////////////////INIT EXIT MENU//////////////////
void ViewMenu::callExitMenu(){
	CCMoveTo *move = CCMoveTo::create(0.2f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2 - 20));
    exitMenu->runAction(move);
}

inline void ViewMenu::initExitMenu(){
	exitMenu = CCSprite::create(EXITDIALOG);
    exitMenu->setPosition(ccp(-250, spriteBg->getContentSize().height/2-20));
	buttonAcceptExit = CCMenuItemImage::create(BUTACCEPTEXIT,BUTACCEPTEXITPRS,this,menu_selector(ViewMenu::acceptExit));
	buttonCancelExit = CCMenuItemImage::create(BUTCANCELEXIT,BUTCANCELEXITPRS,this,menu_selector(ViewMenu::cancelExit));

	CCMenu *menuGame = CCMenu::create(buttonAcceptExit,buttonCancelExit, NULL);
    menuGame->setPosition(ccp(0,0));    
    exitMenu->addChild(menuGame);
	buttonAcceptExit->setPosition(ccp(exitMenu->getContentSize().width/2 - 100, exitMenu->getContentSize().height/2 - 80));
	buttonCancelExit->setPosition(ccp(exitMenu->getContentSize().width/2 + 100, exitMenu->getContentSize().height/2 - 80));
	buttonAcceptExit->setScale(0.8f);
	buttonCancelExit->setScale(0.8f);

    CCLabelBMFont *labelAlert = CCLabelBMFont::create("Bạn có chắc muốn \n thoát game không?", "font-nhiemvu.fnt");

	labelAlert->setPosition(ccp(exitMenu->getContentSize().width/2,exitMenu->getContentSize().height/2 + 30));
    exitMenu->addChild(labelAlert,15);
    spriteBg->addChild(exitMenu,15);
}

void ViewMenu::hiddenExitMenu(){
	CCMoveTo *move = CCMoveTo::create(0.2f,ccp(-250,spriteBg->getContentSize().height/2-20));
	exitMenu->runAction(move);
    this->showAndEnableAllButton();
}

void ViewMenu::showAndEnableAllButton(){
	this->butDiary->setVisible(true);
	this->butPlay->setVisible(true);
	this->butPlayOnline->setVisible(true);
	this->butDownload->setVisible(true);
	this->butInfo->setVisible(true);
	this->butExit->setVisible(true);
	this->butShare->setVisible(true);
}

void ViewMenu::hiddenAndUneableAllButton(){
	this->butDiary->setVisible(false);
	this->butPlay->setVisible(false);
	this->butPlayOnline->setVisible(false);
	this->butDownload->setVisible(false);
	this->butInfo->setVisible(false);
	this->butExit->setVisible(false);
	this->butShare->setVisible(false);
}

void ViewMenu::acceptExit(CCObject *pSender){
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ViewMenu::cancelExit(CCObject *pSender){
    this->hiddenExitMenu();
}


//////////////////////////////////////////////////////////////////

void ViewMenu::exitGame(CCObject *pSender){
	this->hiddenAndUneableAllButton();
	this->callExitMenu();
    

}


ViewMenu::ViewMenu(void)
{
    
}

ViewMenu::~ViewMenu(void){
    
}
