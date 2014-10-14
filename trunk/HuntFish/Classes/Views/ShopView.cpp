//
//  ShopView.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//
#include "ShopView.h"
#include "LinkResources.h"

using namespace cocos2d;
using namespace extension;

bool ShopView::init(){
	bool bRect = false;
	do{
		this->isEnable = false;
		//Nut thoat shop
		this->butExit    = CCMenuItemImage::create(BUTEXIT,BUTEXITPRESS,this,menu_selector(ShopView::exitShop));
		CC_BREAK_IF(!butExit);
		this->butExit->setPosition(ccp(this->getContentSize().width - 25,25));
		//Nut them kim cuong
		this->butAddDiamon = CCMenuItemImage::create(BUTADDDIAMON, BUTADDDIAMONPRESS,this,menu_selector(ShopView::addDiamon));
		CC_BREAK_IF(!butAddDiamon);
		//Nut them tien
		this->butAddMoney  = CCMenuItemImage::create(BUTADDMONEY, BUTADDMONEYPRESS,this,menu_selector(ShopView::addMoney));
		CC_BREAK_IF(!butAddMoney);
		//Menu chua cac nut trong shop
		this->menu = CCMenu::create(butExit,butAddMoney,butAddDiamon, NULL);
		CC_BREAK_IF(!menu);

        //Load thong tin sung
        this->loadInfoGunAndGift();
        
		this->initTapGun();
		this->initTapHelp();
		this->initTapGift();

		this->addChild(menu,9);
		this->menu->setPosition(ccp(0,0));

		CCSprite *rectMoney,*rectRuby,*rectDiamon;
		rectDiamon = CCSprite::create(RECTDIAMON);
		CC_BREAK_IF(!rectDiamon);
		rectMoney  = CCSprite::create(RECTMONEY);
		CC_BREAK_IF(!rectMoney);
		rectRuby   = CCSprite::create(RECTRUBY);
		CC_BREAK_IF(!rectRuby);

		this->addChild(rectRuby);
		this->addChild(rectMoney);
		this->addChild(rectDiamon);

		rectRuby->setPosition(ccp(this->getContentSize().width/2 + 70,this->getContentSize().height + 20));
		rectMoney->setPosition(ccp(this->getContentSize().width/2 + 180,this->getContentSize().height + 20));
		rectDiamon->setPosition(ccp(this->getContentSize().width/2 + 320,this->getContentSize().height + 20));

		butAddMoney->setPosition(ccp(this->getContentSize().width/2 + 250,this->getContentSize().height + 20));
		butAddDiamon->setPosition(ccp(this->getContentSize().width/2 + 388,this->getContentSize().height + 20));

		bRect = true;
	}
	while (0);
	return  bRect;
}

ShopView* ShopView::createShop(CCString *nameFile){
	ShopView* shopSprite = new ShopView();
	if(shopSprite && shopSprite->initWithFile(nameFile->getCString())){
		shopSprite->autorelease();
		return shopSprite;
	}
	else
		return NULL;

}

void ShopView::initTapGun(){
    //Button tapGun
	this->butTapGun = CCMenuItemImage::create(BIGBUYBUTTON,BIGBUYBUTTON,this,menu_selector(ShopView::tapGun));
	this->butTapGun->setPosition(ccp(this->getContentSize().width/2 - 260, this->getContentSize().height + 14));
	this->menu->addChild(this->butTapGun);
	this->butTapGun->setScaleX(0.73f);
	this->butTapGun->setScaleY(0.9f);
    //Image button tapGun
	this->spTopGun = CCSprite::create(TAPGUN);
	this->addChild(spTopGun,10);
	this->spTopGun->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height + 20));
	//Khoi tao layer tap gun
    this->gunChoosed = 1;
	this->layerTapGun = CCLayer::create();
	this->layerTapGun->setContentSize(CCSize(this->getContentSize().width,this->getContentSize().height));
	this->layerTapGun->setPosition(this->getPosition());
	this->addChild(this->layerTapGun,9);
    //Layer chua thong tin cac loai sung
    CCLayer *layerInfo = CCLayer::create();
    layerInfo->setContentSize(this->getContentSize());
    layerInfo->setPosition(this->getPosition());
    this->layerTapGun->addChild(layerInfo,10);
    //Layer chua cac sp sung
    CCLayer *layerGun = CCLayer::create();
    //Menu spGuns
    CCMenu *menuSpGun = CCMenu::create();
    menuSpGun->setPosition(CCPointZero);
    layerGun->addChild(menuSpGun,9);
    
    for(int i = 0;i<9;i++){
        //Cac background tung item sung
		this->spBgSlice[i] = CCSprite::create(RECTITEM);
        this->spBgSlice[i]->setPosition(ccp(this->getContentSize().width/2 - 150, 85*(i+1) + 40));
        layerGun->addChild(this->spBgSlice[i],8);
	}
    
    //khoi tao item sung
	for(int i = 0;i<9;i++){
        //Text ten sung
        CCString *stringNameGun = CCString::createWithFormat("Súng x%d",(9-i));
        CCLabelBMFont *nameGun = CCLabelBMFont::create(stringNameGun->getCString(),"font-tendo2x.fnt");
        layerGun->addChild(nameGun,10);
        nameGun->setPosition(ccp(this->getContentSize().width/2 - 180,85*(i+1) + 70));
        
        CCString *stringInfoGun = CCString::createWithFormat("Sức mạnh: %d. Phạm vi: %d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(8-i))->objectAtIndex(((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(8-i))->objectAtIndex(1)))->intValue() + 1)))->intValue(),((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(8-i))->objectAtIndex(12)))->intValue());
        
        this->labelInfoGun = CCLabelBMFont::create(stringInfoGun->getCString(),"font-motado2x.fnt");
        layerGun->addChild(this->labelInfoGun,10);
        this->labelInfoGun->setPosition(ccp(this->getContentSize().width/2 - 105,85*(i+1) + 35));

        //Icon sung
        CCString *tmp = CCString::createWithFormat("slice%d.png",9-i);
        this->itemGun[i] = CCMenuItemImage::create(tmp->getCString(), tmp->getCString(),this,menu_selector(ShopView::showInfoGun));
        this->itemGun[i]->setTag(8-i);
        this->itemGun[i]->setPosition(ccp(this->getContentSize().width/2-290, 85*(i+1) + 45));
		
        if(((CCString*)(CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",9-i))->getCString()) == 0))){
            //Tao cac nut mua sung
            this->butBuyGun[i] = CCMenuItemImage::create(BUTBUYSMALL,BUTBUYSMALLPRESS,this,menu_selector(ShopView::buyGun));
            this->butBuyGun[i]->setTag(9-i);
            this->butBuyGun[i]->setPosition(ccp(this->getContentSize().width/2 - 20,85*(i+1) + 65));
            menuSpGun->addChild(this->butBuyGun[i],8);
        }
        menuSpGun->addChild(this->itemGun[i],14);
        
        //Image gioi thieu ve sung
        this->spBigSlice[i] = CCSprite::create((CCString::createWithFormat("gun%d.png",9-i))->getCString());
        this->layerTapGun->addChild(spBigSlice[i],10);
        this->spBigSlice[i]->setPosition(ccp(this->getContentSize().width/2 + 200, this->getContentSize().height - 100));
        this->spBigSlice[i]->setRotation(-30);
        if(i<8)
            this->spBigSlice[i]->setVisible(false);
	}
	//tao cac icon tien vang cho
    for(int i = 0;i<9;i++){
        this->spIconGold[i] = CCSprite::create(ICONSMALLMONEY);
        this->spIconGold[i]->setPosition(ccp(this->getContentSize().width/2 - 300,15 + 85*(i+1)));
        layerGun->addChild(spIconGold[i],15);
        
        this->spRectMon[i] = CCSprite::create(RECTMONEYSMALL);
        this->spRectMon[i]->setPosition(ccp(this->getContentSize().width/2 - 275,15 + 85*(i+1)));
        layerGun->addChild(spRectMon[i],14);
    }
    
    //Scroll view
    this->scrollViewGun = CCScrollView::create(CCSize(this->getContentSize().width-310,this->getContentSize().height - 80),layerGun);
    this->scrollViewGun->setPosition(ccp(this->getPosition().x,this->getPosition().y + 60));
	this->scrollViewGun->setDirection(kCCScrollViewDirectionVertical);
	this->scrollViewGun->setContentOffset(CCPointZero);
    this->scrollViewGun->setContentSize(CCSize(this->getContentSize().width-310,this->getContentSize().height*2));
    layerGun->setPosition(ccp(this->layerTapGun->getPositionX(),-this->layerTapGun->getContentSize().height - 90));
    this->layerTapGun->addChild(this->scrollViewGun);
   
    
    //Spcoin
    CCSprite *spCoin1 = CCSprite::create(ICONBIGMONEY);
    CCSprite *spCoin2 = CCSprite::create(ICONBIGMONEY);
    spCoin1->setPosition(ccp(this->getContentSize().width/2 + 85,this->getContentSize().height/2 - 20));
    spCoin2->setPosition(ccp(this->getContentSize().width/2 + 85,this->getContentSize().height/2 - 120));
    this->layerTapGun->addChild(spCoin1,10);
    this->layerTapGun->addChild(spCoin2,10);
    
    //Bac suc mang cua sung dang chon hien tai
    int levelGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("lvGun%d",this->gunChoosed))->getCString());
    //Bac toc do cua sung dang chon hien tai
    int velocityGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("veloGun%d",this->gunChoosed))->getCString());
    
    CCString*stringTmp1 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(this->gunChoosed-1))->objectAtIndex(levelGun+2)))->intValue());
    CCString*stringTmp2 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(this->gunChoosed-1))->objectAtIndex(velocityGun+2)))->intValue());

    //Label gia tien nang cap suc manh sung va toc do sung
    this->labelSoTienNangCap = CCLabelBMFont::create(stringTmp1->getCString(),"font-sotien-to.fnt");
    this->labelSoTienTangToc = CCLabelBMFont::create(stringTmp2->getCString(),"font-sotien-to.fnt");
    this->labelSoTienNangCap->setPosition(ccp(this->getContentSize().width/2 + 110,this->getContentSize().height/2 + 50));
    this->labelSoTienTangToc->setPosition(ccp(this->getContentSize().width/2 + 110,this->getContentSize().height/2 - 50));
    this->labelSoTienNangCap->setAnchorPoint(ccp(0,1));
    this->labelSoTienTangToc->setAnchorPoint(ccp(0,1));
    this->layerTapGun->addChild(this->labelSoTienNangCap,10);
    this->layerTapGun->addChild(this->labelSoTienTangToc,10);
    
	//Thong tin suc manh va toc do hien tai cua sung duoc chon
    CCString *stringSucManh = CCString::createWithFormat("Sức mạnh: %d/10",levelGun);
    CCString *stringTocDo = CCString::createWithFormat("Tốc độ: %d/10",velocityGun);
    this->labelSucManhSung = CCLabelBMFont::create(stringSucManh->getCString(), "font-motado-nho.fnt");
    this->labelTocDoSung   = CCLabelBMFont::create(stringTocDo->getCString(), "font-motado-nho.fnt");
    this->labelSucManhSung->setPosition(ccp(this->getContentSize().width/2 + 110,this->getContentSize().height/2 + 65));
    this->labelTocDoSung->setPosition(ccp(this->getContentSize().width/2 + 110,this->getContentSize().height/2 - 35));
    this->labelSucManhSung->setAnchorPoint(ccp(0,1));
    this->labelTocDoSung->setAnchorPoint(ccp(0,1));
    this->layerTapGun->addChild(this->labelSucManhSung,10);
    this->layerTapGun->addChild(this->labelTocDoSung,10);
    
    //Nut tang suc mang sung
	this->butFixGunStrong = CCMenuItemImage::create(BUTFIXGUN, BUTFIXGUNPRESS,this,menu_selector(ShopView::fixGunStrong));
	this->butFixGunStrong->setPosition(ccp(this->getContentSize().width/2 + 250, this->getContentSize().height/2 -20));
	//Nut tang toc do sung
	this->butFixGunVelocity = CCMenuItemImage::create(BUTFIXGUN, BUTFIXGUNPRESS,this,menu_selector(ShopView::fixGunVelocity));
	this->butFixGunVelocity->setPosition(ccp(this->getContentSize().width/2 + 250, this->getContentSize().height/2 - 120));
    this->butFixGunStrong->setScaleX(0.8f);
    this->butFixGunVelocity->setScaleX(0.8f);
    
    //Neu level dat muc 10 thi an so tien can de nang cap sung
    if(levelGun == 10){
        this->labelSoTienNangCap->setVisible(false);
        this->butFixGunStrong->setVisible(false);
    }
    if(velocityGun == 10){
        this->labelSoTienTangToc->setVisible(false);
        this->butFixGunVelocity->setVisible(false);
    }
    //Khoi tao menu chua cac nut trong tapGun
	CCMenu *menuTapGun = CCMenu::create(butFixGunVelocity,butFixGunStrong, NULL);
	menuTapGun->setPosition(ccp(0,0));
	layerInfo->addChild(menuTapGun,9);
    
    //Tao khung select khi chon cac vat pham sung
    this->spItemSelected = CCSprite::create(RECTITEMSELECT);
    layerGun->addChild(this->spItemSelected,10);
    this->spItemSelected->setVisible(false);
}

void ShopView::initTapHelp(){
    this->itemChoosed = 1;
	this->numberBoom = CCUserDefault::sharedUserDefault()->getIntegerForKey("numBoom");
	this->numberBread = CCUserDefault::sharedUserDefault()->getIntegerForKey("numBread");
	this->numberFreeze = CCUserDefault::sharedUserDefault()->getIntegerForKey("numFreeze");
	//Khoi tao layer tap gun
	this->layerTapHelp = CCLayer::create();
	this->layerTapHelp->setContentSize(this->getContentSize());
	this->layerTapHelp->setPosition(this->getPosition());
	this->addChild(this->layerTapHelp,9);
	this->layerTapHelp->setVisible(false);
	//Button chon tap help
	this->butTapHelp = CCMenuItemImage::create(BIGBUYBUTTON,BIGBUYBUTTON,this,menu_selector(ShopView::tapHelp));
	this->menu->addChild(this->butTapHelp);
	this->butTapHelp->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height+ 14));
	this->butTapHelp->setScaleY(0.9f);
	this->butTapHelp->setScaleX(0.73f);
	//Image tap help
	this->spTopHelp = CCSprite::create(TAPHELP);
	this->addChild(spTopHelp,10);
	this->spTopHelp->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height + 20));
	this->spTopHelp->setVisible(false);
    //Tao cac sprite vat pham
    this->spBigBoom = CCSprite::create(ITEMBIGBOOM);
    this->spBigFreeze = CCSprite::create(ITEMBIGFREEZE);
    this->spBigBread = CCSprite::create(ITEMBIGBREAD);
    this->layerTapHelp->addChild(this->spBigBoom,10);
    this->layerTapHelp->addChild(this->spBigBread,10);
    this->layerTapHelp->addChild(this->spBigFreeze,10);
    this->spBigBoom->setPosition(ccp(this->getContentSize().width/2 + 195,this->getContentSize().height/2 + 120));
    this->spBigFreeze->setPosition(ccp(this->getContentSize().width/2 + 195,this->getContentSize().height/2 + 120));
    this->spBigBread->setPosition(ccp(this->getContentSize().width/2 + 195,this->getContentSize().height/2 + 120));
    this->spBigBread->setVisible(false);
    this->spBigFreeze->setVisible(false);
    //ICON DIAMOND
    this->iconGold = CCSprite::create(ICONBIGDIAMON);
    this->layerTapHelp->addChild(iconGold,10);
    this->iconGold->setPosition(ccp(this->getContentSize().width/2 + 80, this->getContentSize().height/2 - 120));
	//Nut mua vat pham
	this->butBuyItem = CCMenuItemImage::create(BUTBUYBIG, BUTBUYBIGPRESS,this,menu_selector(ShopView::buyItem));
	this->butBuyItem->setPosition(ccp(this->getContentSize().width/2 + 240, this->getContentSize().height/2 - 120));
    this->butBuyItem->setScaleX(0.8f);
	this->butBuyItem->setVisible(true);
	//Menu chua cac nut
	CCMenu *menuTapHelp = CCMenu::create(this->butBuyItem, NULL);
	menuTapHelp->setPosition(ccp(0,0));
	this->layerTapHelp->addChild(menuTapHelp,9);
    //INFO ITEM
    this->infoItem = CCLabelBMFont::create("Sử dụng bom nổ\n     để bắt cá","font-motado-nho.fnt");
    this->layerTapHelp->addChild(this->infoItem,10);
    this->infoItem->setPosition(ccp(this->getContentSize().width/2 + 195, this->getContentSize().height/2 + 40));
    this->labelNumberItem = CCLabelBMFont::create((CCString::createWithFormat("Số lương: %d",this->numberBoom))->getCString(),"font-motado-nho.fnt");
    this->layerTapHelp->addChild(this->labelNumberItem,10);
    this->labelNumberItem->setPosition(ccp(this->getContentSize().width/2 + 195,this->getContentSize().height/2 - 50));
	//khoi tao khung item chon vat pham tro giup
	for(int i = 0;i<3;i++){
		//Cac background tung item help
		this->bgItemHelp[i] = CCMenuItemImage::create(RECTITEM,RECTITEM,this,menu_selector(ShopView::showInfoItem));
		CC_BREAK_IF(!this->bgItemHelp[i]);
		this->bgItemHelp[i]->setTag(i);
		this->bgItemHelp[i]->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height - 65 - 85*i));
		menuTapHelp->addChild(this->bgItemHelp[i],9);
	}

	//tao cac icon kim cuong cho sung
	for(int i = 0;i<3;i++){
		this->spIconDiamon[i] = CCSprite::create(ICONSMALLDIAMON);
		this->spIconDiamon[i]->setPosition(ccp(this->getContentSize().width/2 - 285, this->getContentSize().height - 85 - 85*i));
		this->layerTapHelp->addChild(spIconDiamon[i],15);
	}
	for(int i = 0;i<3;i++){
		this->spRectDiamon[i] = CCSprite::create(RECTMONEYSMALL);
		this->spRectDiamon[i]->setPosition(ccp(this->getContentSize().width/2 - 275, this->getContentSize().height - 85 - 85*i));
		this->layerTapHelp->addChild(spRectDiamon[i],14);
	}

	//khoi tao sp item vat pham 
	for(int i = 0;i<3;i++){
		CCString *tmp = CCString::createWithFormat("shop-item-%d.png",i+1);
		this->spItem[i] = CCSprite::create(tmp->getCString());
		CC_BREAK_IF(!this->spItem[i]);
		this->layerTapHelp->addChild(this->spItem[i],10);
		if(i<4)
			this->spItem[i]->setPosition(ccp(this->getContentSize().width/2 - 290,this->getContentSize().height - 60 - 85*i));
		else{
			this->spItem[i]->setPosition(ccp(this->getContentSize().width/2 - 290, this->getContentSize().height/2 - 100*(i-4)));
			this->spItem[i]->setVisible(false);
		}
	}

	//Label ten do
	CCLabelBMFont *labelNameBoom = CCLabelBMFont::create("Bom nước","font-tendo2x.fnt");
	CCLabelBMFont *labelNameFreeze = CCLabelBMFont::create("Sấm sét","font-tendo2x.fnt");
	CCLabelBMFont *labelNameBread = CCLabelBMFont::create("Bánh mì","font-tendo2x.fnt");
	this->layerTapHelp->addChild(labelNameBoom,10);
	this->layerTapHelp->addChild(labelNameFreeze,10);
	this->layerTapHelp->addChild(labelNameBread,10);
	labelNameBoom->setAnchorPoint(ccp(0.0,1.0));
	labelNameFreeze->setAnchorPoint(ccp(0.0,1.0));
	labelNameBread->setAnchorPoint(ccp(0.0,1.0));
	labelNameBoom->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 20));
	labelNameFreeze->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 105));
	labelNameBread->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 190));

	this->infoBoom = CCLabelBMFont::create((CCString::createWithFormat("Số lượng đang có: %d",this->numberBoom))->getCString(),"font-motado2x.fnt");
	this->infoFreeze = CCLabelBMFont::create((CCString::createWithFormat("Số lượng đang có: %d",this->numberFreeze))->getCString(),"font-motado2x.fnt");
	this->infoBread = CCLabelBMFont::create((CCString::createWithFormat("Số lượng đang có: %d",this->numberBread))->getCString(),"font-motado2x.fnt");
	this->labelCost = CCLabelBMFont::create((CCString::createWithFormat("14"))->getCString(),"font-sotien-to.fnt");
    
    this->layerTapHelp->addChild(this->infoBoom,10);
	this->layerTapHelp->addChild(this->infoFreeze,10);
	this->layerTapHelp->addChild(this->infoBread,10);
    this->layerTapHelp->addChild(this->labelCost,11);
    
	this->infoBoom->setAnchorPoint(ccp(0.0,1.0));
	this->infoFreeze->setAnchorPoint(ccp(0.0,1.0));
	this->infoBread->setAnchorPoint(ccp(0.0,1.0));
	
    this->infoBoom->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 50));
	this->infoFreeze->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 135));
	this->infoBread->setPosition(ccp(this->getContentSize().width/2 - 230, this->getContentSize().height - 220));
    this->labelCost->setPosition(ccp(this->getContentSize().width/2 + 130, this->getContentSize().height/2 - 95));
    
    //Tao khung select khi chon cac vat pham sung
    this->spHelpSelected = CCSprite::create(RECTITEMSELECT);
    this->addChild(this->spHelpSelected,10);
    this->spHelpSelected->setVisible(false);

}

void ShopView::initTapGift(){
    this->scrollviewVisible = 3;
	//Khoi tao layer tap gift
	this->layerTapGift = CCLayer::create();
	this->layerTapGift->setContentSize(this->getContentSize());
	this->layerTapGift->setPosition(this->getPosition());
	this->addChild(this->layerTapGift,9);

	this->butTapGift = CCMenuItemImage::create(BIGBUYBUTTON,BIGBUYBUTTON,this,menu_selector(ShopView:: tapGift));
	this->butTapGift->setPosition(ccp(this->getContentSize().width/2 - 35, this->getContentSize().height+ 14));
	this->butTapGift->setScaleY(0.9f);
	this->butTapGift->setScaleX(0.73f);
	this->menu->addChild(this->butTapGift);

	this->spTopGift = CCSprite::create(TAPDANHHIEU);
	this->addChild(this->spTopGift,10);
	this->spTopGift->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height + 20));
	this->spTopGift->setVisible(false);

    //Nut sang trang danh hieu
    this->butBackPage = CCMenuItemImage::create(BUTBACKDIARY, BUTBACKDIARYPRS,this, menu_selector(ShopView::backpageGift));
    this->butNextPage = CCMenuItemImage::create(BUTNEXTDIARY, BUTNEXTDIARYPRS,this, menu_selector(ShopView::nextPageGift));
    this->butBackPage->setPosition(ccp(this->layerTapGift->getContentSize().width/2 - 220, this->layerTapGift->getContentSize().height/2 - 190));
    this->butNextPage->setPosition(ccp(this->layerTapGift->getContentSize().width/2 - 50, this->layerTapGift->getContentSize().height/2 - 190));
    //Menu chua cac button
    CCMenu *menuButton = CCMenu::create(this->butNextPage, this->butBackPage,NULL);
    menuButton->setPosition(CCPointZero);
    this->layerTapGift->addChild(menuButton,10);
    
    //LAYER DANH HIEU TIEN BAC
    CCLayer *layerDanhHieuTienBac;
    CCLayer *layerInfoDanhHieuTienBac;
   
    layerDanhHieuTienBac = CCLayer::create();
    layerInfoDanhHieuTienBac = CCLayer::create();
    layerInfoDanhHieuTienBac->setPosition(this->getPosition());
    layerInfoDanhHieuTienBac->setContentSize(this->getContentSize());
    layerDanhHieuTienBac->setPosition(this->getPosition());
    
    CCMenu *menuButtonItem = CCMenu::create();
    menuButtonItem->setPosition(CCPointZero);
    layerDanhHieuTienBac->addChild(menuButtonItem,11);
    //Nen cac o vuong chua danh hieu
    CCMenuItem *buttonBgItemTienBac[10];
    CCSprite *spBgItemTienBac[10];
    CCSprite *spImageItem[10];
    int indexGiftInArray;
    
    for(int i = 0;i<10;i++){
        buttonBgItemTienBac[i] = CCMenuItemImage::create(ICONDANHHIEU,ICONDANHHIEU,this,menu_selector(ShopView::showInfoGift));
        buttonBgItemTienBac[i]->setPosition(ccp(this->getContentSize().width/2 - 270, 85*(i+1) + 42));
        buttonBgItemTienBac[i]->setTag(i);
        menuButtonItem->addChild(buttonBgItemTienBac[i],11);
        
        spBgItemTienBac[i] = CCSprite::create(RECTITEM);
        spBgItemTienBac[i]->setPosition(ccp(this->getContentSize().width/2 - 150,85*(i+1) + 40));
        layerDanhHieuTienBac->addChild(spBgItemTienBac[i],10);
        
        spImageItem[i] = CCSprite::create((CCString::createWithFormat("tb%d.png",i+1))->getCString());
        spImageItem[i]->setPosition(ccp(this->getContentSize().width/2 - 270,85*(10-i) + 42));
        layerDanhHieuTienBac->addChild(spImageItem[i],11);
        
        //Set ten do
        indexGiftInArray = i;
        CCString*stringTmp = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(indexGiftInArray))->objectAtIndex(0)))->getCString());
        CCLabelBMFont *nameGift = CCLabelBMFont::create(stringTmp->getCString(), "font-tendo2x.fnt");
        nameGift->setPosition(ccp(this->getContentSize().width/2 - 205,85*(10-i) + 85));
        nameGift->setAnchorPoint(ccp(0,1.0f));
        layerDanhHieuTienBac->addChild(nameGift,15);
    }
    
    //tao cac icon kim cuong cho vat pham
    CCSprite *iconSmallDiamonTienBac[10];
    CCSprite *rectSmallDiamonTienBac[10];
    for(int i = 0;i<10;i++){
        iconSmallDiamonTienBac[i] = CCSprite::create(ICONSMALLGIFT);
        iconSmallDiamonTienBac[i]->setPosition(ccp(this->getContentSize().width/2 - 35,85*(i+1) + 42));
        layerDanhHieuTienBac->addChild(iconSmallDiamonTienBac[i],15);
        
        rectSmallDiamonTienBac[i] = CCSprite::create(RECTMONEYSMALL);
        rectSmallDiamonTienBac[i]->setPosition(ccp(this->getContentSize().width/2 - 10,85*(i+1) + 42));
        layerDanhHieuTienBac->addChild(rectSmallDiamonTienBac[i],14);
    }
    
    //Scroll view
    this->scrollView_TienBac = CCScrollView::create(CCSize(this->getContentSize().width-310,this->getContentSize().height - 80),layerDanhHieuTienBac);
    this->scrollView_TienBac->setPosition(ccp(this->getPosition().x,this->getPosition().y + 60));
	this->scrollView_TienBac->setDirection(kCCScrollViewDirectionVertical);
	this->scrollView_TienBac->setContentOffset(CCPointZero);
    this->scrollView_TienBac->setContentSize(CCSize(this->getContentSize().width-310,this->getContentSize().height*2 + 100));
    layerDanhHieuTienBac->setPosition(ccp(this->layerTapGift->getPositionX(),-this->layerTapGift->getContentSize().height - 170));
    this->layerTapGift->addChild(this->scrollView_TienBac,10);
    
    //LAYER DANH HIEU PHAM CHAT
    CCLayer *layerDanhHieuPhamChat;
    CCLayer *layerInfoDanhHieuPhamChat;
    
    layerDanhHieuPhamChat = CCLayer::create();
    layerInfoDanhHieuPhamChat = CCLayer::create();
    layerInfoDanhHieuPhamChat->setPosition(this->getPosition());
    layerInfoDanhHieuPhamChat->setContentSize(this->getContentSize());
    layerDanhHieuPhamChat->setPosition(this->getPosition());
    
    CCMenu *menuButtonItemPhamChat = CCMenu::create();
    menuButtonItemPhamChat->setPosition(CCPointZero);
    layerDanhHieuPhamChat->addChild(menuButtonItemPhamChat,11);
    //Nen cac o vuong chua danh hieu
    CCMenuItem *buttonBgItemPhamChat[16];
    CCSprite *spBgItemPhamChat[16];
    CCSprite *spImageItemPhamChat[16];
    
    for(int i = 0;i<16;i++){
        buttonBgItemPhamChat[i] = CCMenuItemImage::create(ICONDANHHIEU,ICONDANHHIEU,this,menu_selector(ShopView::showInfoGift));
        buttonBgItemPhamChat[i]->setPosition(ccp(this->getContentSize().width/2 - 270, 85*(i+1) + 42));
        buttonBgItemPhamChat[i]->setTag(i+10);
        menuButtonItemPhamChat->addChild(buttonBgItemPhamChat[i],11);
        
        spBgItemPhamChat[i] = CCSprite::create(RECTITEM);
        spBgItemPhamChat[i]->setPosition(ccp(this->getContentSize().width/2 - 150,85*(i+1) + 40));
        layerDanhHieuPhamChat->addChild(spBgItemPhamChat[i],10);
        
        spImageItemPhamChat[i] = CCSprite::create((CCString::createWithFormat("pc%d.png",i+1))->getCString());
        spImageItemPhamChat[i]->setPosition(ccp(this->getContentSize().width/2 - 270,85*(16-i) + 42));
        layerDanhHieuPhamChat->addChild(spImageItemPhamChat[i],11);
        
        //Set ten do
        indexGiftInArray = i + 10;
        CCString*stringTmp = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(indexGiftInArray))->objectAtIndex(0)))->getCString());
        CCLabelBMFont *nameGift = CCLabelBMFont::create(stringTmp->getCString(), "font-tendo2x.fnt");
        nameGift->setPosition(ccp(this->getContentSize().width/2 - 205,85*(16-i) + 85));
        nameGift->setAnchorPoint(ccp(0,1.0f));
        layerDanhHieuPhamChat->addChild(nameGift,15);
    }
    
    //tao cac icon kim cuong cho vat pham
    CCSprite *iconSmallDiamonPhamChat[10];
    CCSprite *rectSmallDiamonPhamChat[10];
    for(int i = 0;i<16;i++){
        iconSmallDiamonPhamChat[i] = CCSprite::create(ICONSMALLGIFT);
        iconSmallDiamonPhamChat[i]->setPosition(ccp(this->getContentSize().width/2 - 35,85*(i+1) + 42));
        layerDanhHieuPhamChat->addChild(iconSmallDiamonPhamChat[i],15);
        
        rectSmallDiamonPhamChat[i] = CCSprite::create(RECTMONEYSMALL);
        rectSmallDiamonPhamChat[i]->setPosition(ccp(this->getContentSize().width/2 - 10,85*(i+1) + 42));
        layerDanhHieuPhamChat->addChild(rectSmallDiamonPhamChat[i],14);
    }
    
    //Scroll view
    this->scrollView_PhamChat = CCScrollView::create(CCSize(this->getContentSize().width-310,this->getContentSize().height - 80),layerDanhHieuPhamChat);
    this->scrollView_PhamChat->setPosition(ccp(this->getPosition().x,this->getPosition().y + 60));
	this->scrollView_PhamChat->setDirection(kCCScrollViewDirectionVertical);
	this->scrollView_PhamChat->setContentOffset(CCPointZero);
    this->scrollView_PhamChat->setContentSize(CCSize(this->getContentSize().width-310,this->getContentSize().height*3 + 180));
    layerDanhHieuPhamChat->setPosition(ccp(this->layerTapGift->getPositionX(),-this->layerTapGift->getContentSize().height - 680));
    this->layerTapGift->addChild(this->scrollView_PhamChat,10);
    this->scrollView_PhamChat->setVisible(false);
    
    //LAYER DANH HIEU DANH VONG
    CCLayer *layerDanhHieuDanhVong;
    CCLayer *layerInfoDanhHieuDanhVong;
    
    layerDanhHieuDanhVong = CCLayer::create();
    layerInfoDanhHieuDanhVong = CCLayer::create();
    layerInfoDanhHieuDanhVong->setPosition(this->getPosition());
    layerInfoDanhHieuDanhVong->setContentSize(this->getContentSize());
    layerDanhHieuDanhVong->setPosition(this->getPosition());
    
    CCMenu *menuButtonItemDanhVong = CCMenu::create();
    menuButtonItemDanhVong->setPosition(CCPointZero);
    layerDanhHieuDanhVong->addChild(menuButtonItemDanhVong,11);
    //Nen cac o vuong chua danh hieu
    CCMenuItem *buttonBgItemDanhVong[9];
    CCSprite *spBgItemDanhVong[9];
    CCSprite *spImageItemDanhVong[9];
    
    for(int i = 0;i<9;i++){
        buttonBgItemDanhVong[i] = CCMenuItemImage::create(ICONDANHHIEU,ICONDANHHIEU,this,menu_selector(ShopView::showInfoGift));
        buttonBgItemDanhVong[i]->setPosition(ccp(this->getContentSize().width/2 - 270, 85*(i+1) + 42));
        buttonBgItemDanhVong[i]->setTag(i+26);
        menuButtonItemDanhVong->addChild(buttonBgItemDanhVong[i],11);
        
        spBgItemDanhVong[i] = CCSprite::create(RECTITEM);
        spBgItemDanhVong[i]->setPosition(ccp(this->getContentSize().width/2 - 150,85*(i+1) + 40));
        layerDanhHieuDanhVong->addChild(spBgItemDanhVong[i],10);
        
        spImageItemDanhVong[i] = CCSprite::create((CCString::createWithFormat("dv%d.png",i+1))->getCString());
        spImageItemDanhVong[i]->setPosition(ccp(this->getContentSize().width/2 - 270,85*(9-i) + 42));
        layerDanhHieuDanhVong->addChild(spImageItemDanhVong[i],11);
        
        //Set ten do
        indexGiftInArray = i + 26;
        CCString*stringTmp = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(indexGiftInArray))->objectAtIndex(0)))->getCString());
        CCLabelBMFont *nameGift = CCLabelBMFont::create(stringTmp->getCString(), "font-tendo2x.fnt");
        nameGift->setPosition(ccp(this->getContentSize().width/2 - 205,85*(9-i) + 85));
        nameGift->setAnchorPoint(ccp(0,1.0f));
        layerDanhHieuDanhVong->addChild(nameGift,15);
    }
    //tao cac icon kim cuong cho vat pham
    CCSprite *iconSmallDiamonDanhVong[10];
    CCSprite *rectSmallDiamonDanhVong[10];
    for(int i = 0;i<9;i++){
        iconSmallDiamonDanhVong[i] = CCSprite::create(ICONSMALLGIFT);
        iconSmallDiamonDanhVong[i]->setPosition(ccp(this->getContentSize().width/2 - 35,85*(i+1) + 42));
        layerDanhHieuDanhVong->addChild(iconSmallDiamonDanhVong[i],15);
        
        rectSmallDiamonDanhVong[i] = CCSprite::create(RECTMONEYSMALL);
        rectSmallDiamonDanhVong[i]->setPosition(ccp(this->getContentSize().width/2 - 10,85*(i+1) + 42));
        layerDanhHieuDanhVong->addChild(rectSmallDiamonDanhVong[i],14);
    }
    //Scroll view
    this->scrollView_DanhVong = CCScrollView::create(CCSize(this->getContentSize().width-310,this->getContentSize().height - 80),layerDanhHieuDanhVong);
    this->scrollView_DanhVong->setPosition(ccp(this->getPosition().x,this->getPosition().y + 60));
	this->scrollView_DanhVong->setDirection(kCCScrollViewDirectionVertical);
	this->scrollView_DanhVong->setContentOffset(CCPointZero);
    this->scrollView_DanhVong->setContentSize(CCSize(this->getContentSize().width-310,this->getContentSize().height*2));
    layerDanhHieuDanhVong->setPosition(ccp(this->layerTapGift->getPositionX(),-this->layerTapGift->getContentSize().height - 90));
    this->layerTapGift->addChild(this->scrollView_DanhVong,10);
    this->scrollView_DanhVong->setVisible(false);
    
    //LAYER DANH HIEU NGAY SINH
    CCLayer *layerDanhHieuCung;
    CCLayer *layerInfoDanhHieuCung;
    
    layerDanhHieuCung = CCLayer::create();
    layerInfoDanhHieuCung = CCLayer::create();
    layerInfoDanhHieuCung->setPosition(this->getPosition());
    layerInfoDanhHieuCung->setContentSize(this->getContentSize());
    layerDanhHieuCung->setPosition(this->getPosition());
    
    CCMenu *menuButtonItemCung = CCMenu::create();
    menuButtonItemCung->setPosition(CCPointZero);
    layerDanhHieuCung->addChild(menuButtonItemCung,11);
    //Nen cac o vuong chua danh hieu
    CCMenuItem *buttonBgItemCung[12];
    CCSprite *spBgItemCung[12];
    CCSprite *spImageCung[12];
    
    for(int i = 0;i<12;i++){
        buttonBgItemCung[i] = CCMenuItemImage::create(ICONDANHHIEU,ICONDANHHIEU,this,menu_selector(ShopView::showInfoGift));
        buttonBgItemCung[i]->setPosition(ccp(this->getContentSize().width/2 - 270, 85*(i+1) + 42));
        buttonBgItemCung[i]->setTag(i+35);
        menuButtonItemCung->addChild(buttonBgItemCung[i],11);
        
        spBgItemCung[i] = CCSprite::create(RECTITEM);
        spBgItemCung[i]->setPosition(ccp(this->getContentSize().width/2 - 150,85*(i+1) + 40));
        layerDanhHieuCung->addChild(spBgItemCung[i],10);
        
        spImageCung[i] = CCSprite::create((CCString::createWithFormat("cung%d.png",i+1))->getCString());
        spImageCung[i]->setPosition(ccp(this->getContentSize().width/2 - 270,85*(12-i) + 42));
        layerDanhHieuCung->addChild(spImageCung[i],11);
        
        //Set ten do
        indexGiftInArray = i + 35;
        CCString*stringTmp = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(indexGiftInArray))->objectAtIndex(0)))->getCString());
        CCLabelBMFont *nameGift = CCLabelBMFont::create(stringTmp->getCString(), "font-tendo2x.fnt");
        nameGift->setPosition(ccp(this->getContentSize().width/2 - 205,85*(12-i) + 85));
        nameGift->setAnchorPoint(ccp(0,1.0f));
        layerDanhHieuCung->addChild(nameGift,15);
    }
    //tao cac icon kim cuong cho vat pham
    CCSprite *iconSmallDiamonNgaySinh[10];
    CCSprite *rectSmallDiamonNgaySinh[10];
    for(int i = 0;i<12;i++){
        iconSmallDiamonNgaySinh[i] = CCSprite::create(ICONSMALLGIFT);
        iconSmallDiamonNgaySinh[i]->setPosition(ccp(this->getContentSize().width/2 - 35,85*(i+1) + 42));
        layerDanhHieuCung->addChild(iconSmallDiamonNgaySinh[i],15);
        
        rectSmallDiamonNgaySinh[i] = CCSprite::create(RECTMONEYSMALL);
        rectSmallDiamonNgaySinh[i]->setPosition(ccp(this->getContentSize().width/2 - 10,85*(i+1) + 42));
        layerDanhHieuCung->addChild(rectSmallDiamonNgaySinh[i],14);
    }
    
    //Scroll view
    this->scrollView_NgaySinh = CCScrollView::create(CCSize(this->getContentSize().width-310,this->getContentSize().height - 80),layerDanhHieuCung);
    this->scrollView_NgaySinh->setPosition(ccp(this->getPosition().x,this->getPosition().y + 60));
	this->scrollView_NgaySinh->setDirection(kCCScrollViewDirectionVertical);
	this->scrollView_NgaySinh->setContentOffset(CCPointZero);
    this->scrollView_NgaySinh->setContentSize(CCSize(this->getContentSize().width-310,this->getContentSize().height*2 + 265));
    layerDanhHieuCung->setPosition(ccp(this->layerTapGift->getPositionX(),-this->layerTapGift->getContentSize().height - 340));
    this->layerTapGift->addChild(this->scrollView_NgaySinh,10);
    this->scrollView_NgaySinh->setVisible(false);
    
    //An tap khi vao shop
    this->layerTapGift->setVisible(false);

	this->spGiftSelected1 = CCSprite::create(RECTITEMSELECT);
	this->scrollView_TienBac->addChild(this->spGiftSelected1,10);
	this->spGiftSelected1->setVisible(false);

	this->spGiftSelected2 = CCSprite::create(RECTITEMSELECT);
	this->scrollView_PhamChat->addChild(this->spGiftSelected2,10);
	this->spGiftSelected2->setVisible(false);

	this->spGiftSelected3 = CCSprite::create(RECTITEMSELECT);
	this->scrollView_DanhVong->addChild(this->spGiftSelected3,10);
	this->spGiftSelected3->setVisible(false);

	this->spGiftSelected4 = CCSprite::create(RECTITEMSELECT);
	this->scrollView_NgaySinh->addChild(this->spGiftSelected4,10);
	this->spGiftSelected4->setVisible(false);
}

void ShopView::nextPageGift(CCObject *pSender){
	this->scrollviewVisible++;
	if(this->scrollviewVisible > 3)
		this->scrollviewVisible = 0;

	if(this->scrollviewVisible == 0){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(true);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(false);
		CCLog("PHAM CHAT");
    }
    else if(this->scrollviewVisible == 1){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(true);
        this->scrollView_DanhVong->setVisible(false);
        CCLog("NGAY SINH");
    }
    else if(this->scrollviewVisible == 2){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(true);
        CCLog("DANH VONG");
    }
    else if(this->scrollviewVisible == 3){
        this->scrollView_TienBac->setVisible(true);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(false);
        CCLog("TIEN BAC");
    }
	
}

void ShopView::backpageGift(CCObject *pSender){
	this->scrollviewVisible--;
	if(this->scrollviewVisible < 0)
		this->scrollviewVisible = 3;

    if(this->scrollviewVisible == 0){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(true);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(false);
        CCLog("PHAM CHAT");
    }
    else if(this->scrollviewVisible == 1){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(true);
        this->scrollView_DanhVong->setVisible(false);
        CCLog("NGAY SINH");
    }
    else if(this->scrollviewVisible == 2){
        this->scrollView_TienBac->setVisible(false);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(true);
        CCLog("DANH VONG");
    }
    else if(this->scrollviewVisible == 3){
        this->scrollView_TienBac->setVisible(true);
        this->scrollView_PhamChat->setVisible(false);
        this->scrollView_NgaySinh->setVisible(false);
        this->scrollView_DanhVong->setVisible(false);
        CCLog("TIEN BAC");
    }
}
//Load cac thong tin sung lan dau vao shop
void ShopView::loadInfoGunAndGift(){
    this->gunsInfoArray = CCArray::createWithContentsOfFile(FILECONFIGGUNS);
    this->gunsInfoArray->retain();
    
    this->giftInfoArray = CCArray::createWithContentsOfFile(FILECONFIGGIFTS);
    this->giftInfoArray->retain();
}

void ShopView::appearShopView(int positionX){
	CCMoveTo *move = CCMoveTo::create(.5f,ccp(positionX,this->getPosition().y));
	this->runAction(move);
	this->isEnable = true;
}

void ShopView::hiddenShopView(int positionX){
	CCMoveTo *move = CCMoveTo::create(.5f,ccp(positionX,this->getPosition().y));

	CCSequence *sq = CCSequence::create(move, CCCallFunc::create(this,callfunc_selector(ShopView::setShopUnEnable)),NULL);
	this->runAction(sq);
}

void ShopView::setShopUnEnable(){
	this->isEnable = false;

}

void ShopView::tapGun(CCObject *pSender){
//	CCLog("TAP GUN");
    this->spHelpSelected->setVisible(false);
    this->spItemSelected->setVisible(false);
	this->layerTapGift->setVisible(false);
	this->layerTapGun->setVisible(true);
	this->layerTapHelp->setVisible(false);

	spTopHelp->setVisible(false);
	spTopGift->setVisible(false);
	spTopGun->setVisible(true);
}

void ShopView::tapHelp(CCObject *pSender){
//	CCLog("TAP HELP");
    this->spHelpSelected->setVisible(false);
    this->spItemSelected->setVisible(false);
	this->layerTapGift->setVisible(false);
	this->layerTapGun->setVisible(false);
	this->layerTapHelp->setVisible(true);

	spTopGift->setVisible(false);
	spTopGun->setVisible(false);
	spTopHelp->setVisible(true);
}

void ShopView::tapGift(CCObject *pSender){
//	CCLog("TAP GIFT");
    this->spHelpSelected->setVisible(false);
    this->spItemSelected->setVisible(false);
	this->layerTapGift->setVisible(true);
	this->layerTapGun->setVisible(false);
	this->layerTapHelp->setVisible(false);

	spTopHelp->setVisible(false);
	spTopGun->setVisible(false);
	spTopGift->setVisible(true);
}

void ShopView::showInfoGun(CCObject *pSender){
	CCMenuItem *item = (CCMenuItem *)pSender;
	this->spItemSelected->setVisible(true);
    this->spItemSelected->setPosition(ccp(item->getPositionX() + 140, item->getPositionY()-5));
    
    //Neu sung da unlock thi hien thong tin sung
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",item->getTag()+1))->getCString()) == 1){
        for (int i=0;i<=8;i++) {
            this->spBigSlice[i]->setVisible(false);
        }
        
        this->spBigSlice[8-item->getTag()]->setVisible(true);
        this->gunChoosed = item->getTag() + 1;
        
        //Bac suc mang cua sung dang chon hien tai
        int levelGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("lvGun%d",this->gunChoosed))->getCString());
        //Bac toc do cua sung dang chon hien tai
        int velocityGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("veloGun%d",this->gunChoosed))->getCString());
        
        CCLog("\nGUN: %d",this->gunChoosed);
        CCLog("Unlock: %d",CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",this->gunChoosed))->getCString()));
        CCLog("LevelGun: %d", levelGun);
        CCLog("veloGun: %d", velocityGun);
        
        if(levelGun <10){
            this->butFixGunStrong->setVisible(true);
            this->labelSoTienNangCap->setVisible(true);
        }
        else{
            this->butFixGunStrong->setVisible(false);
            this->labelSoTienNangCap->setVisible(false);
        }
        if(velocityGun <10){
            this->butFixGunVelocity->setVisible(true);
            this->labelSoTienTangToc->setVisible(true);
        }
        else{
            this->butFixGunVelocity->setVisible(false);
            this->labelSoTienTangToc->setVisible(false);
        }
        
        CCString*stringTmp1 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(item->getTag()))->objectAtIndex(levelGun+2)))->intValue());
        CCString*stringTmp2 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(item->getTag()))->objectAtIndex(velocityGun+2)))->intValue());
        
        //Label gia tien nang cap suc manh sung va toc do sung
        this->labelSoTienNangCap->setString(stringTmp1->getCString());
        this->labelSoTienTangToc->setString(stringTmp2->getCString());
        //Thong tin suc manh va toc do hien tai cua sung duoc chon
        CCString *stringSucManh = CCString::createWithFormat("Sức mạnh: %d/10",levelGun);
        CCString *stringTocDo = CCString::createWithFormat("Tốc độ: %d/10",velocityGun);
        
        this->labelTocDoSung->setVisible(true);
        this->labelSucManhSung->setVisible(true);
        this->labelSucManhSung->setString(stringSucManh->getCString());
        this->labelTocDoSung->setString(stringTocDo->getCString());
    }
    else{
        for (int i=0;i<=8;i++) {
            this->spBigSlice[i]->setVisible(false);
        }
        this->labelSucManhSung->setVisible(false);
        this->labelTocDoSung->setVisible(false);
        this->labelSoTienNangCap->setVisible(false);
        this->labelSoTienTangToc->setVisible(false);
        this->butFixGunStrong->setVisible(false);
        this->butFixGunVelocity->setVisible(false);
        CCLog("GUN UNLOCKED! PLEASE BUY IT!");
    }
}

void ShopView::reloadInfoGun(CCObject *pSender){
    
}

void ShopView::showInfoItem(CCObject *pSender){
    CCMenuItem *item = (CCMenuItem *)pSender;
    this->spHelpSelected->setVisible(true);
    this->spHelpSelected->setPosition(ccp(this->getContentSize().width/2 - 150, this->getContentSize().height - 65 - 85*(item->getTag())));
    if(item->getTag() == 0){
        this->spBigBoom->setVisible(true);
        this->spBigBread->setVisible(false);
        this->spBigFreeze->setVisible(false);
        this->infoItem->setString((CCString::createWithFormat("Sử dụng bom nổ\n     để bắt cá"))->getCString());
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberBoom))->getCString());
        this->labelCost->setString((CCString::createWithFormat("14"))->getCString());
        this->itemChoosed = 1;
        CCLog("BOOM");
    }
    else if(item->getTag() == 1){
        this->spBigBoom->setVisible(false);
        this->spBigBread->setVisible(false);
        this->spBigFreeze->setVisible(true);
        this->infoItem->setString((CCString::createWithFormat("Sử dụng bom điện\n  làm tê liệt cá"))->getCString());
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberFreeze))->getCString());
        this->labelCost->setString((CCString::createWithFormat("10"))->getCString());
        this->itemChoosed = 2;
        CCLog("SET");
    }
    else if(item->getTag() == 2){
        this->spBigBoom->setVisible(false);
        this->spBigBread->setVisible(true);
        this->spBigFreeze->setVisible(false);
        this->infoItem->setString((CCString::createWithFormat("Sử dụng mồi nhử\n     để dụ cá"))->getCString());
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberBread))->getCString());
        this->labelCost->setString((CCString::createWithFormat("12"))->getCString());
        this->itemChoosed = 3;
        CCLog("BANH MI");
    }
}

void ShopView::showInfoGift(CCObject *pSender){
    CCMenuItem *item = (CCMenuItem *)pSender;

	this->spGiftSelected1->setVisible(false);
	this->spGiftSelected2->setVisible(false);
	this->spGiftSelected3->setVisible(false);
	this->spGiftSelected4->setVisible(false);

    int index = 0;
	if(item->getTag()<10){
		this->spGiftSelected1->setVisible(true);
		this->spGiftSelected1->setPosition(ccp(item->getPositionX() - 65, item->getPositionY()-45));
        index = 9 - item->getTag();
	}
	else if(item->getTag() >= 10 && item->getTag() < 26){
		this->spGiftSelected2->setVisible(true);
		this->spGiftSelected2->setPosition(ccp(item->getPositionX() - 65, item->getPositionY()-45));
        index = 25-item->getTag() + 10;
	}
	else if(item->getTag() >= 26 && item->getTag() < 35 ){
		this->spGiftSelected3->setVisible(true);
		this->spGiftSelected3->setPosition(ccp(item->getPositionX() - 65, item->getPositionY()-45));
        index = 34 -item->getTag() + 26;
	}
	else	if(item->getTag() >= 35 && item->getTag() < 47){
		this->spGiftSelected4->setVisible(true);
		this->spGiftSelected4->setPosition(ccp(item->getPositionX() - 65, item->getPositionY()-45));
        index = 46 -item->getTag() + 35;
	}
    
    CCString*stringTmp = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(index))->objectAtIndex(0)))->getCString());
    CCString*stringDanhVong  = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(index))->objectAtIndex(1)))->getCString());
    CCString*stringLevelUnLock = CCString::createWithFormat("%s",((CCString*)(((CCArray*)this->giftInfoArray->objectAtIndex(index))->objectAtIndex(2)))->getCString());;
    
    CCLog("Danh hieu:%s - Diem danh vong: %s - LevelUnlock: %s",stringTmp->getCString(),stringDanhVong->getCString(), stringLevelUnLock->getCString());
}

void ShopView::buyItem(CCObject *pSender){
    if(this->itemChoosed == 1){
        this->numberBoom++;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numBoom", this->numberBoom);
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberBoom))->getCString());
        this->infoBoom->setString((CCString::createWithFormat("Số lượng đang có: %d",this->numberBoom))->getCString(),"font-motado2x.fnt");
    }
    else if(this->itemChoosed == 2){
        this->numberFreeze++;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numFreeze", this->numberFreeze);
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberFreeze))->getCString());
        this->infoFreeze->setString((CCString::createWithFormat("Số lượng đang có: %d",this->numberFreeze))->getCString(),"font-motado2x.fnt");
    }
    else if(this->itemChoosed == 3){
        this->numberBread ++;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numBread", this->numberBread);
        this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberBread))->getCString());
    	this->infoBread->setString((CCString::createWithFormat("Số lượng đang có: %d",this->numberBread))->getCString(),"font-motado2x.fnt");
    }
}

void ShopView::exitShop(CCObject *pSender){
    this->spItemSelected->setVisible(false);
    this->spHelpSelected->setVisible(false);
    this->spBigBoom->setVisible(true);
    this->spBigBread->setVisible(false);
    this->spBigFreeze->setVisible(false);
    this->infoItem->setString((CCString::createWithFormat("Sử dụng bom nổ\n     để bắt cá"))->getCString());
    this->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",this->numberBoom))->getCString());
	this->isEnable = false;
    this->itemChoosed = 1;
	this->hiddenShopView(this->getPosition().x + 1000);
}

void ShopView::addMoney(CCObject *pSender){
	CCLog("ADD MONEY");
}

void ShopView::addDiamon(CCObject *pSender){
	CCLog("ADD DIAMON");
}

void ShopView::fixGunVelocity(CCObject *pSender){
    //Bac toc do cua sung dang chon hien tai
    int velocityGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("veloGun%d",this->gunChoosed))->getCString());
    CCUserDefault::sharedUserDefault()->setIntegerForKey((CCString::createWithFormat("veloGun%d",this->gunChoosed))->getCString(),++velocityGun);
    CCUserDefault::sharedUserDefault()->flush();
    
    //An nut nang cap khi dat den muc 10
    CCMenuItem *item = (CCMenuItem*)pSender;
    if(velocityGun == 10){
        item->setVisible(false);
        this->labelSoTienTangToc->setVisible(false);
    }
    else{
        CCString*stringTmp2 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(this->gunChoosed-1))->objectAtIndex(velocityGun+2)))->intValue());
        //Label gia tien nang cap suc manh sung va toc do sung
        this->labelSoTienTangToc->setVisible(true);
        this->labelSoTienTangToc->setString(stringTmp2->getCString());
    }
    //Thong tin suc manh va toc do hien tai cua sung duoc chon
    CCString *stringTocDo = CCString::createWithFormat("Tốc độ: %d/10",velocityGun);
    this->labelTocDoSung->setVisible(true);
    this->labelTocDoSung->setString(stringTocDo->getCString());
    
    CCLog("FIX VELOCITY GUN: %d to level: %d",this->gunChoosed,velocityGun);
}

void ShopView::fixGunStrong(CCObject *pSender){
    //Bac suc mang cua sung dang chon hien tai
    int levelGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("lvGun%d",this->gunChoosed))->getCString());
    CCUserDefault::sharedUserDefault()->setIntegerForKey((CCString::createWithFormat("lvGun%d",this->gunChoosed))->getCString(),++levelGun);
    CCUserDefault::sharedUserDefault()->flush();
    
    //An nut nang cap khi den muc 10
    CCMenuItem *item = (CCMenuItem*)pSender;
    if(levelGun == 10){
        item->setVisible(false);
        this->labelSoTienNangCap->setVisible(false);
    }
    else{
        CCString*stringTmp1 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(this->gunChoosed-1))->objectAtIndex(levelGun+2)))->intValue());
        //Label gia tien nang cap suc manh sung va toc do sung
        this->labelSoTienNangCap->setVisible(true);
        this->labelSoTienNangCap->setString(stringTmp1->getCString());
    }
    //Thong tin suc manh va toc do hien tai cua sung duoc chon
    CCString *stringSucManh = CCString::createWithFormat("Sức mạnh: %d/10",levelGun);    
    this->labelSucManhSung->setVisible(true);
    this->labelSucManhSung->setString(stringSucManh->getCString());
    
    CCLog("FIX BULLET GUN: %d to level: %d",this->gunChoosed,levelGun);
}

void ShopView::buyGun(CCObject *pSender){
    CCMenuItem *item = (CCMenuItem*)pSender;
	this->spItemSelected->setVisible(true);
    this->spItemSelected->setPosition(ccp(item->getPositionX()-130, item->getPositionY()-25));
    
    item->setVisible(false);
    CCUserDefault::sharedUserDefault()->setIntegerForKey((CCString::createWithFormat("gun%d",item->getTag()))->getCString(),1);
    CCUserDefault::sharedUserDefault()->flush();
    
    CCLog("BUY GUN: %d",item->getTag());
    
    this->gunChoosed = item->getTag();
    for (int i=0;i<=8;i++) {
        this->spBigSlice[i]->setVisible(false);
    }
    this->spBigSlice[8-(item->getTag()-1)]->setVisible(true);
    
    //Bac suc mang cua sung dang chon hien tai
    int levelGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("lvGun%d",this->gunChoosed))->getCString());
    //Bac toc do cua sung dang chon hien tai
    int velocityGun = CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("veloGun%d",this->gunChoosed))->getCString());
    
    CCLog("\nGUN: %d",this->gunChoosed);
    CCLog("Unlock: %d",CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",this->gunChoosed))->getCString()));
    CCLog("LevelGun: %d", levelGun);
    CCLog("veloGun: %d", velocityGun);
    
    this->butFixGunStrong->setVisible(true);
    this->labelSoTienNangCap->setVisible(true);
    this->butFixGunVelocity->setVisible(true);
    this->labelSoTienTangToc->setVisible(true);

    CCString*stringTmp1 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(item->getTag()-1))->objectAtIndex(levelGun+2)))->intValue());
    CCString*stringTmp2 = CCString::createWithFormat("%d",((CCString*)(((CCArray*)this->gunsInfoArray->objectAtIndex(item->getTag()-1))->objectAtIndex(velocityGun+2)))->intValue());
    
    //Label gia tien nang cap suc manh sung va toc do sung
    this->labelSoTienNangCap->setString(stringTmp1->getCString());
    this->labelSoTienTangToc->setString(stringTmp2->getCString());
    //Thong tin suc manh va toc do hien tai cua sung duoc chon
    CCString *stringSucManh = CCString::createWithFormat("Sức mạnh: %d/10",levelGun);
    CCString *stringTocDo = CCString::createWithFormat("Tốc độ: %d/10",velocityGun);
    
    this->labelTocDoSung->setVisible(true);
    this->labelSucManhSung->setVisible(true);
    this->labelSucManhSung->setString(stringSucManh->getCString());
    this->labelTocDoSung->setString(stringTocDo->getCString());
}

void ShopView::scrollViewDidScroll(CCScrollView * view){
    
}

void ShopView::scrollViewDidZoom(CCScrollView *view){
    
}

ShopView::ShopView(void){

}

ShopView::~ShopView(void){

}