//
//  ShopView.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#define __HuntFish__ShopView__
#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class ShopView: public cocos2d::CCSprite, public cocos2d :: extension :: CCScrollViewDelegate
{
public:
    void scrollViewDidScroll (CCScrollView * view);
    void scrollViewDidZoom (CCScrollView * view);
    
public:
    static ShopView* createShop(CCString *nameFile);
    virtual bool init();
    CREATE_FUNC(ShopView);
    ShopView(void);
    ~ShopView(void);
    
    void appearShopView(int positionX);
    void hiddenShopView(int positionX);
    void tapGun(CCObject *pSender);
    void tapHelp(CCObject *pSender);
    void tapGift(CCObject *pSender);
    void exitShop(CCObject *pSender);
    void addMoney(CCObject *pSender);
    void addDiamon(CCObject *pSender);
    void fixGunStrong(CCObject *pSender);
    void fixGunVelocity(CCObject *pSender);
    void buyItem(CCObject *pSender);
	void showInfoGun(CCObject *pSender);
    void reloadInfoGun(CCObject *pSender);
	void showInfoItem(CCObject *pSender);
	void showInfoGift(CCObject *pSender);
    void nextPageGift(CCObject *pSender);
    void backpageGift(CCObject *pSender);
	void buyGun(CCObject *pSender);
	void initTapGun();
	void initTapHelp();
	void initTapGift();
    void loadInfoGunAndGift();
	void setShopUnEnable();
    
    CCMenuItem *butTapGun, *butTapHelp, *butTapGift, *butExit;
    CCMenuItem *butAddMoney;
    CCMenuItem *butAddDiamon;
	CCMenu *menu;
    
	//Layer Help
	CCLayer *layerTapHelp;
	CCLabelBMFont *infoBoom, *labelNumberItem, *infoFreeze,  *infoBread, *labelCost, *infoItem;
	CCMenuItem *bgItemHelp[3];
    CCMenuItem *butBuyItem;
	CCSprite *spTopHelp,*spItem[3], *spIconDiamon[3],*spRectDiamon[3],*spBigBoom,*spBigFreeze,*spBigBread,*iconGold;
	CCSprite *spHelpSelected;
    int numberBoom, numberFreeze, numberBread;
    int itemChoosed;
	//Layer Gun
    CCScrollView *scrollViewGun;
	CCLayer *layerTapGun;
    CCMenuItem *butFixGunStrong;
    CCMenuItem *butFixGunVelocity;
	CCMenuItem *butBuyGun[9];
	CCMenuItem *itemGun[9];
	CCSprite *spTopGun, *spBgSlice[9], *spIconGold[11],*spRectMon[9],*spBigSlice[9];
    CCSprite *spItemSelected;
    CCArray *gunsInfoArray, *giftInfoArray;
    int gunChoosed;
    CCLabelBMFont *labelInfoGun, *labelSoTienNangCap,*labelSoTienTangToc,*labelSucManhSung,*labelTocDoSung;
	//Layer Gift
	CCLayer *layerTapGift;
    CCScrollView *scrollView_TienBac, *scrollView_PhamChat, *scrollView_NgaySinh, *scrollView_DanhVong;
	CCSprite *spTopGift;
    CCSprite *spGiftSelected1,*spGiftSelected2,*spGiftSelected3,*spGiftSelected4;
    CCMenuItem *butNextPage, *butBackPage;
    int scrollviewVisible;
    CCLabelBMFont *labelInfoGift;
    
    bool isEnable;
};