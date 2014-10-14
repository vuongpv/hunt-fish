//
//  DiaryView.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 11/22/13.
//
//

#include "DiaryView.h"
#include "LinkResources.h"


bool DiaryView::init(){
    bool bRect = false;
    do{
        this->buttonExitDiary = CCMenuItemImage::create(BUTEXITDIARY, BUTEXITDIARYPRS,this,menu_selector(DiaryView::exitDiary));
        CC_BREAK_IF(!this->buttonExitDiary);
        this->buttonNext = CCMenuItemImage::create(BUTNEXTDIARY, BUTNEXTDIARYPRS,this,menu_selector(DiaryView::nextPage));
        CC_BREAK_IF(!this->buttonNext);
        this->buttonBack = CCMenuItemImage::create(BUTBACKDIARY, BUTBACKDIARYPRS, this, menu_selector(DiaryView::backPage));
        CC_BREAK_IF(!this->buttonBack);
        this->buttonShare = CCMenuItemImage::create(BUTSHAREDIARY, BUTSHAERDIARYPRS,this,menu_selector(DiaryView::shareDiary));
        CC_BREAK_IF(!this->buttonShare);
        this->menuButton = CCMenu::create(buttonExitDiary,buttonNext,buttonBack,buttonShare,NULL);
        CC_BREAK_IF(!this->menuButton);
        this->addChild(this->menuButton,10);
        this->menuButton->setPosition(CCPointZero);
        this->buttonExitDiary->setPosition(ccp(this->getContentSize().width - 20,this->getContentSize().height - 50));
        this->buttonShare->setPosition(ccp(this->getContentSize().width/2 + 200, 40));
        this->buttonBack->setPosition(ccp(this->getContentSize().width/2 - 250, 40));
        this->buttonNext->setPosition(ccp(this->getContentSize().width/2 - 30, 40));
        
        this->isEnable = false;
        
        this->initLayerFish();
    }
    while (0);
    return  bRect;
}

void DiaryView::initLayerFish(){
    this->loadNumberFish();
    this->layerFish1 = CCLayer::create();
    this->layerFish1->setContentSize(this->getContentSize());
    this->layerFish1->setPosition(this->getPosition());
    this->layerFish2 = CCLayer::create();
    this->layerFish2->setContentSize(this->getContentSize());
    this->layerFish2->setPosition(this->getPosition());
    
    this->addChild(layerFish1,10);
    this->addChild(layerFish2,10);
    
    CCSprite *fishImage[16];
    
    for(int i = 0;i<16;i++){
        fishImage[i] = CCSprite::create((CCString::createWithFormat("fd%d.png",i+1))->getCString());
        this->labelNumberFish[i] = CCLabelBMFont::create((CCString::createWithFormat("x%d",this->numFish[i])->getCString()), "font-so.fnt");
        this->labelNumberFish[i]->setAnchorPoint(ccp(0,1));
        this->layerFish1->addChild(fishImage[i],10);
        this->layerFish1->addChild(this->labelNumberFish[i],10);
    }
    
    for(int i = 0;i<6;i++){
        fishImage[i]->setPosition(ccp(this->getContentSize().width/2 - 260,this->getContentSize().height/2 + 125 - i*50));
        this->labelNumberFish[i]->setPosition(ccp(this->getContentSize().width/2 - 210,this->getContentSize().height/2 + 190 - i*50));
    }
    for(int i = 6;i<11;i++){
        fishImage[i]->setPosition(ccp(this->getContentSize().width/2 - 60,this->getContentSize().height/2 + 115 - (i-6)*60));
        this->labelNumberFish[i]->setPosition(ccp(this->getContentSize().width/2 - 10,this->getContentSize().height/2 + 180 - (i-6)*60));
    }
    for(int i = 11;i<16;i++){
        fishImage[i]->setPosition(ccp(this->getContentSize().width/2 + 140,this->getContentSize().height/2 + 115 - (i-11)*60));
        this->labelNumberFish[i]->setPosition(ccp(this->getContentSize().width/2 + 210,this->getContentSize().height/2 + 180 - (i-11)*60));
    }
}

DiaryView* DiaryView::createDiary(CCString *nameFile){
    DiaryView *diary = new DiaryView();
    if(diary && diary->initWithFile(nameFile->getCString())){
        diary->autorelease();
        return diary;
    }
    else
        return  NULL;
}

void DiaryView::loadNumberFish(){
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    for(int i = 0;i<12;i++){
        this->numFish[i] = defaults->getIntegerForKey((CCString::createWithFormat("totalFish%d",i+1))->getCString());
    }
    this->numFish[12] = defaults->getIntegerForKey((CCString::createWithFormat("totalFish16"))->getCString());
    this->numFish[13] = defaults->getIntegerForKey((CCString::createWithFormat("totalFish17"))->getCString());
    this->numFish[14] = defaults->getIntegerForKey((CCString::createWithFormat("totalFish19"))->getCString());
    this->numFish[15] = defaults->getIntegerForKey((CCString::createWithFormat("totalFish20"))->getCString());
}

void DiaryView::exitDiary(CCObject *pSender){
    this->hiddenDiary(this->getPositionY() + 500);
}

void DiaryView::appearDiary(int positionY){
    CCMoveTo *move = CCMoveTo::create(.5f, ccp(this->getPosition().x, positionY));
    this->runAction(move);
    this->isEnable = true;
}

void DiaryView::hiddenDiary(int positionY){
    CCMoveTo *move = CCMoveTo::create(0.5f,ccp(this->getPosition().x,positionY));
    CCSequence *sq = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(DiaryView::setDiaryUnenalbe)), NULL);
    this->runAction(sq);
}

void DiaryView::setDiaryUnenalbe(){
    this->isEnable = false;
}

void DiaryView::shareDiary(CCObject *pSender){
    
}

void DiaryView::nextPage(CCObject *pSender){
    
}

void DiaryView::backPage(CCObject *pSender){
    
}


DiaryView::DiaryView(void){
}

DiaryView::~DiaryView(void){
}