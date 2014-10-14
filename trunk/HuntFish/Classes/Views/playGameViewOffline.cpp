//
//  PlayGameView.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "PlayGameViewOffline.h"
#include "LinkResources.h"
#include "ViewMenu.h"
#include "Coin.h"
#include "Gun.h"
#include "Effect.h"
#include "cocos-ext.h"

CCScene* PlayGameViewOffline::scene(){
	CCScene *scene=NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		PlayGameViewOffline *layer = PlayGameViewOffline::create();
        
		CC_BREAK_IF(! layer);
        // add layer as a child to scene
        scene->addChild(layer);
	}
	while(0);
	return scene;
}

bool PlayGameViewOffline::init(){
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCLayer::init());
        
        //////////////////////////////////////////////////////////////////////////
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        // SET UP DEVICE
        
        this->setTouchEnabled(true);
		this->loadLevel();
        this->initBackGround();
        this->initPauseMenu();
        this->initShop();
        this->initGun();
		this->initMissionMenu();
		this->initExitMenu();
		this->initItem();
		this->loadCheckFish();
		srand((unsigned)time(0));
        this->schedule(schedule_selector(PlayGameViewOffline::updateGame),0.2f);
        this->schedule(schedule_selector(PlayGameViewOffline::updateFish),0.05f);
        
        spriteBg->setScaleX(size.width/spriteBg->getContentSize().width);
        spriteBg->setScaleY(size.height/spriteBg->getContentSize().height);
        changePositionWidth = size.width/spriteBg->getContentSize().width;
        changePositionHeight = size.height/spriteBg->getContentSize().height;
        bRet = true;
    } while (0);
    return bRet;
}

void PlayGameViewOffline::updateGame(float dt){        
	CCObject *objectTp = NULL;
	Web *bTmp = NULL;
	ItemHunt *itemTmp = NULL;
	int countFishCombo = 0;
	int countPoint = 0;
	CCARRAY_FOREACH(spriteBg->getChildren(),objectTp)
    {
		if(this->chooseItemHunt){
			itemTmp = (ItemHunt*)objectTp;
			if(itemTmp->getTag()== -5){
				CCObject *objectTmp = NULL;
				Fish *fTmp = NULL;
				CCARRAY_FOREACH(spriteBg->getChildren(), objectTmp)
				{
					fTmp = (Fish*)objectTmp;
					if(fTmp->getTag() <= -10){
						if(fTmp->fishDied)
							continue;
						if(itemTmp->typeItem == 1){
                            CCRect rect = CCRect(itemTmp->getPositionX() - 210, itemTmp->getPositionY() - 210, 420, 420);
							if(rect.containsPoint(fTmp->getPosition())){
								//kiem tra cac truong hop dac biet;
								this->checkFishSpecial(fTmp);
								//Cong diem
                                countFishCombo ++;
                                countPoint += fTmp->point;
//								this->coinCount += fTmp->point;
								//cong nang luong
								this->energyCount ++;
								if(this->energyCount <= 300)
									this->powerBar->setPercentage(this->energyCount/3);
								else{
									this->energyCount = 0;
                                    this->buttonShotPower->setVisible(true);
									gun->reloadGun(10,spriteBg->getContentSize().width/2);
                                    
                                    //Effect *effectFullPower = Effect::createEffect(CCString::create(FULLPOWEREFFECT));
									//effectFullPower->loadEffectFullPower(spriteBg);
								}
	
								this->levelCount += fTmp->experience;
								if(this->levelCount<= this->ranger)
									this->levelSlice->setPercentage(this->levelCount*(100/this->ranger));
								else{
									CCLog("PASS LEVEL");
									Effect *effectPass = Effect::createEffect(CCString::create(LEVELUPEFFECT));
									effectPass->loadEffectLevelUpAnimation(spriteBg);
									this->levelCount = 0;
									this->levelSlice->setPercentage(0.0f);
									this->levelGamePlay++;
									CCUserDefault::sharedUserDefault()->setIntegerForKey("level",this->levelGamePlay);
									CCUserDefault::sharedUserDefault()->flush();
									this->loadLevel();
								}

								labelCoin->setString(CCString::createWithFormat("%d",coinCount)->getCString());
								fTmp->fishDied = true;
								fTmp->runFishDie(spriteBg);
							}
						}	
						if(itemTmp->typeItem == 2){
                            CCRect rect = CCRect(itemTmp->getPositionX() - 150, itemTmp->getPositionY() - 150, 300, 300);
							if(rect.containsPoint(fTmp->getPosition()) && !fTmp->fishStopMove){
                                fTmp->stopFishMove();
								fTmp->pauseSchedulerAndActions();
                                fTmp->fishStopMove = true;
                                CCSequence* sq = CCSequence::create(CCDelayTime::create(10.0f), CCCallFuncND::create(this, callfuncND_selector(PlayGameViewOffline::resumeFishStop),(void*)fTmp),NULL);
                                this->runAction(sq);
							}
						}
                        if(itemTmp->typeItem == 3){
                            CCRect rect = CCRect(itemTmp->getPositionX() - 130, itemTmp->getPositionY() - 130, 260, 260);
                            if(rect.containsPoint(fTmp->getPosition()) && !fTmp->fishStopMove){
                                if(!fTmp->fishEatBread){
									fTmp->stopAction(fTmp->sqMove);
									fTmp->fishEatBread = true;
								}
							}

							//Neu chon banh mi thi goi ham 10s sau cho ca boi tiep
							if(itemTmp->itemAdded){
								//CCLog("FISH MOVE AGAIN");
								itemTmp->itemAdded = false;
								CCSequence* sq = CCSequence::create(CCDelayTime::create(8.0f), CCCallFunc::create(this, callfunc_selector(PlayGameViewOffline::resumeFishStopEatBread)),NULL);
                                this->runAction(sq);
							}
                        }
					}
				}
			}        
		}
        
		bTmp = (Web*)objectTp;
        if(bTmp->getTag()>= 100 && bTmp->getTag() <= 500){
			CCObject *objectTmp = NULL;
			Fish *fTmp = NULL;
			CCARRAY_FOREACH(spriteBg->getChildren(), objectTmp)
			{
				fTmp = (Fish*)objectTmp;
				if(fTmp->getTag() <= -10){
					if(fTmp->fishDied)
						continue;
					if(fTmp->boundingBox().containsPoint(bTmp->getPosition()) && bTmp->isCatching && (bTmp->getTag() != fTmp->tagOfWebCatchedFish)){
						fTmp->tagOfWebCatchedFish = bTmp->getTag();
						fTmp->blood -= gun->dame;
						//CCLog("BLOOD: %d - BULLET TAG: %d",fTmp->blood,bTmp->getTag());
						if(fTmp->blood <= 0){
							//kiem tra cac truong hop dac biet;
							this->checkFishSpecial(fTmp);
							//Cong diem
							countFishCombo ++;
							countPoint += fTmp->point;
							//Tang thanh nang luong
							this->energyCount ++;
							if(this->energyCount <= 300)
								this->powerBar->setPercentage(this->energyCount/3);
							else{
								this->energyCount = 0;
                                this->buttonShotPower->setVisible(true);
								gun->reloadGun(10,spriteBg->getContentSize().width/2);
                                
                                //Effect *effectFullPower = Effect::createEffect(CCString::create(FULLPOWEREFFECT));
                                //effectFullPower->loadEffectFullPower(spriteBg);
							}

							//Tang thanh kinh nghiem
							this->levelCount += fTmp->experience;
							if(this->levelCount<= this->ranger)
								this->levelSlice->setPercentage(this->levelCount*(100/this->ranger));
							else{
								CCLog("PASS LEVEL");
								Effect *effectPass = Effect::createEffect(CCString::create(LEVELUPEFFECT));
								effectPass->loadEffectLevelUpAnimation(spriteBg);
								this->levelCount = 0;
								this->levelSlice->setPercentage(0.0f);
								this->levelGamePlay++;
								CCUserDefault::sharedUserDefault()->setIntegerForKey("level",this->levelGamePlay);
								CCUserDefault::sharedUserDefault()->flush();
								this->loadLevel();
							}

							labelCoin->setString(CCString::createWithFormat("%d",coinCount)->getCString());
							fTmp->fishDied = true;
							fTmp->runFishDie(spriteBg);
						}
					}
				}
			}        
		}
        else if(bTmp->getTag() == 1000){
            CCObject *objectTmp = NULL;
			Fish *fTmp = NULL;
			CCARRAY_FOREACH(spriteBg->getChildren(), objectTmp)
			{
				fTmp = (Fish*)objectTmp;
				if(fTmp->getTag() <= -10){
					if(fTmp->fishDied)
						continue;
					if(fTmp->boundingBox().containsPoint(bTmp->getPosition()) && bTmp->isCatching){
                        //kiem tra cac truong hop dac biet;
                        this->checkFishSpecial(fTmp);
                        //Cong diem
                        countFishCombo ++;
                        countPoint += fTmp->point;
                        //Tang thanh nang luong
                        this->energyCount ++;
                        if(this->energyCount <= 300)
                            this->powerBar->setPercentage(this->energyCount/3);
                        else{
                            this->energyCount = 0;
                            this->buttonShotPower->setVisible(true);
                            gun->reloadGun(10,spriteBg->getContentSize().width/2);
                        }
                        
                        //Tang thanh kinh nghiem
                        this->levelCount += fTmp->experience;
                        if(this->levelCount<= this->ranger)
                            this->levelSlice->setPercentage(this->levelCount*(100/this->ranger));
                        else{
                            CCLog("PASS LEVEL");
                            Effect *effectPass = Effect::createEffect(CCString::create(LEVELUPEFFECT));
                            effectPass->loadEffectLevelUpAnimation(spriteBg);
                            this->levelCount = 0;
                            this->levelSlice->setPercentage(0.0f);
                            this->levelGamePlay++;
                            CCUserDefault::sharedUserDefault()->setIntegerForKey("level",this->levelGamePlay);
                            CCUserDefault::sharedUserDefault()->flush();
                            this->loadLevel();
                        }
                            
                        labelCoin->setString(CCString::createWithFormat("%d",coinCount)->getCString());
                        fTmp->fishDied = true;
                        fTmp->runFishDie(spriteBg);
                    }
				}
			}        
        }
	}
    
	if(countFishCombo >= 4){
        CCLog("Numfish combo: %d",countFishCombo);
        if (countFishCombo == 4) {
            this->coinCount += (countPoint*1.1);
        }
        else if(countFishCombo == 5){
            this->coinCount += (countPoint*1.2);
        }
        else if(countFishCombo == 6){
            this->coinCount += (countPoint*1.3);
        }
        else if(countFishCombo == 7){
            this->coinCount += (countPoint*1.4);
        }
        else if(countFishCombo == 8){
            this->coinCount += (countPoint*1.5);
        }
        else if(countFishCombo == 9){
            this->coinCount += (countPoint*1.6);
        }
        else if(countFishCombo == 10){
            this->coinCount += (countPoint*1.7);
        }
        else if(countFishCombo == 11){
            this->coinCount += (countPoint*1.8);
        }
        else if(countFishCombo == 12){
            this->coinCount += (countPoint*1.9);
        }
        else if(countFishCombo >= 13){
            this->coinCount += (countPoint*2);
        }
	}
	else{
		this->coinCount += countPoint;
	}
    
    //Reload lai cac thong so sau khi vao shop
    if(callShop && !shop->isEnable){
        callShop = false;
        this->showAndEnableAllButton();
        gun->numberGunUnlock = this->loadCheckGuns();
        gun->reloadInfoGun();
        this->loadCheckItem();
    }
}
//Kiem tra cac truong hop dac biet khi bat phai ca dac biet
void PlayGameViewOffline::checkFishSpecial(Fish *fish){
	if(fish->type == 1){
		this->checkFish1 ++;
		if(this->checkFish1 == 500){
			this->checkFish1 = 0;
            CCLog("Bat du 500 ca vang!");

		}
		this->setCheckFish();
	}
	else if(fish->type == 5){
		this->checkFish5 ++;
		if(this->checkFish5 == 100){
			this->checkFish5 = 0;
            CCLog("Bat du 100 ca than tien!");
		}
		this->setCheckFish();
	}
	else if(fish->type == 10){
		this->checkFish10 ++;
		if(this->checkFish10 == 100){
			this->checkFish10 = 0;
            CCLog("Bat du 100 rua!");
		}
		this->setCheckFish();
	}
	else if(fish->type == 11){
		this->checkFish11 ++;
		if(this->checkFish11 == 20){
			this->checkFish11 = 0;
            CCLog("Bat du 20 ca map xanh!");
		}
		this->setCheckFish();
	}
	else if(fish->type == 12){
		this->checkFish12 ++;
		if(this->checkFish12 == 30){
			this->checkFish12 = 0;
            CCLog("Bat du 30 ca map vang!");
		}
		this->setCheckFish();
	}
	else if(fish->type == 13){
		this->checkFish13 ++;
		if(this->checkFish13 == 100){
			this->checkFish13 = 0;
            CCLog("Bat du 100 ca duoi gai");
		}
		this->setCheckFish();
	}
	//Ca gay no
	else if(fish->type == 9){
		ItemHunt *itemEffect = ItemHunt::createItem(CCString::createWithFormat("bom1.png"));
		itemEffect->typeItem = 1;
		itemEffect->setTag(-5);
		itemEffect->setPosition(fish->getPosition());
		itemEffect->loadEffectItem();
		spriteBg->addChild(itemEffect,10);
		this->chooseItemHunt = true;
	}
}
//Update so luong ca de them vao 
void PlayGameViewOffline::updateFish(float dt){
    CCObject *obTmp = NULL;
    Fish *fTmp;
    countShark  = 0;
    countTurtle = 0;
    countFisher = 0;
    int countF1 = 0,countF2 = 0,countF3 = 0,countF4 = 0,countF5 = 0;
    
    CCARRAY_FOREACH(spriteBg->getChildren(), obTmp){
        fTmp = (Fish*)obTmp;
        
		if(fTmp->type == 10)
            countTurtle ++;
        if(fTmp->type == 11 || fTmp->type == 12)
            countShark ++;
        if(fTmp->type == 17)
            countFisher ++;
        
        if(fTmp->getTag() == -10)
            countF1++;
		else if(fTmp->getTag() == -20)
			countF2++;
		else if(fTmp->getTag() == -30)
			countF3++;
		else if(fTmp->getTag() == -40)
			countF4++;
		else if(fTmp->getTag() == -50)
			countF5++;
    }
    
	
    if(countF1 < MAX_FISH1) {
        this->addFish1();
    }
	if(countF2 < MAX_FISH2) {
        this->addFish2();
    }
	if(countF3 < MAX_FISH3) {
        this->addFish3();
    }
	if(countF4 < MAX_FISH4) {
        this->addFish4();
    }
	
	if(countF5 < MAX_FISH5) {
        this->addFish5();
    }
}
//Cho cac ca bi te liet chay tro lai
void PlayGameViewOffline::resumeFishStop(CCNode *sender, void *fish){
    Fish *f = (Fish*)fish;
    if(!f->fishDied){
        f->resumeSchedulerAndActions();
        f->fishStopMove = false;
    }    
}
//Cho cac ca dang an moi di chuyen tro lai
void PlayGameViewOffline::resumeFishStopEatBread(){
	CCObject *objectTmp = NULL;
	Fish *fTmp = NULL;
	CCARRAY_FOREACH(spriteBg->getChildren(), objectTmp)
	{
		fTmp = (Fish*)objectTmp;
		if(fTmp->getTag() <= -10){
			if(fTmp->fishDied)
				continue;
			if(fTmp->fishEatBread){
				fTmp->setFishMoveAgain();
				fTmp->fishEatBread = false;
			}
		}
	}       
}
//Khoi tao cac phan tu cho background game play
void PlayGameViewOffline::initBackGround(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int n = rand()%7;
    //	CCLog("MAP: %d",n);
    
    switch (n) {
        case 0:
            spriteBg = CCSprite::create(BGPLAY0);
            break;
        case 1:
            spriteBg = CCSprite::create(BGPLAY1);
            break;
        case 2:
            spriteBg = CCSprite::create(BGPLAY2);
            break;
        case 3:
            spriteBg = CCSprite::create(BGPLAY3);
            break;
        case 4:
            spriteBg = CCSprite::create(BGPLAY4);
            break;
        case 5:
            spriteBg = CCSprite::create(BGPLAY5);
            break;
            //            case 6:
            //                spriteBg = [[CCSprite alloc]initWithFile:BGPLAY6];
            //                break;
            
        default:
            spriteBg =  CCSprite::create(BGPLAY1);
            break;
    }
    this->timeCount = 0;
	this->coinCount = 3000;

    this->actionBar =  CCSprite::create(ACTIONBAR);
    this->levelBar  =  CCSprite::create(LEVELBAR);
    
    this->butItem      = CCMenuItemImage::create(BUTITEM,BUTITEM ,this,menu_selector(PlayGameViewOffline::chooseItem));
    this->butMission   = CCMenuItemImage::create(BUTMISSION,BUTMISSION,this,menu_selector(PlayGameViewOffline::chooseMission));
    this->butPause     = CCMenuItemImage::create(BUTPAUSE,BUTPAUSEPRESS,this,menu_selector(PlayGameViewOffline::choosePause));
    this->butMinus     = CCMenuItemImage::create(BUTMINUS,BUTMINUSPRESS,this,menu_selector(PlayGameViewOffline::chooseMinus));
    this->butPlus      = CCMenuItemImage::create(BUTPLUS,BUTPLUSPRESS,this,menu_selector(PlayGameViewOffline::choosePlus));
    this->buttonShotPower = CCMenuItemImage::create(BUTSHOTPOWER, BUTSHOTPOWER,this,menu_selector(PlayGameViewOffline::shotPower));
    //
    CCMenu *menuGame = CCMenu::create(butItem,butMission,butPause,butMinus,butPlus,buttonShotPower,NULL);
    menuGame->setPosition(ccp(0,0));
    
    this->addChild(this->spriteBg);
    this->spriteBg->setPosition(ccp(size.width/2,size.height/2));
    
    this->spriteBg->addChild(actionBar,4);
    this->spriteBg->addChild(levelBar,10);
    this->spriteBg->addChild(menuGame,10);
    
    this->actionBar->setPosition(ccp(this->spriteBg->getContentSize().width/2 - 40, 45));
    this->levelBar->setPosition(ccp(this->spriteBg->getContentSize().width - 130,this->spriteBg->getContentSize().height - 25));
    
    this->butPause->setPosition(ccp(this->spriteBg->getContentSize().width - 40,32));
    
    this->butItem->setPosition(ccp(45,this->spriteBg->getContentSize().height - 40));
    
    this->butMission->setPosition(ccp(125, this->spriteBg->getContentSize().height - 40));
                
    this->butMinus->setPosition(ccp(this->spriteBg->getContentSize().width/2 - 65, 25));
    
    this->butPlus->setPosition(ccp(this->spriteBg->getContentSize().width/2 + 65, 25));
    
    this->buttonShotPower->setPosition(ccp(this->spriteBg->getContentSize().width/2 + 115, 32));
    this->buttonShotPower->setVisible(false);
    
    this->labelCoin = CCLabelBMFont::create("0", "font-sovang.fnt");
    this->labelTime = CCLabelBMFont::create("10", "font-sothoigian.fnt");
    this->actionBar->addChild(labelCoin,15);
    this->actionBar->addChild(labelTime,15);
    this->labelCoin->setPosition(ccp(actionBar->getContentSize().width/2 - 285,30));
    this->labelTime->setPosition(ccp(actionBar->getContentSize().width/2 - 195,36));

	// CCProgresstimer object (smart pointer) 
	this->powerBar = CCProgressTimer::create(CCSprite::create(POWERSLICE));
	this->powerBar->setType(kCCProgressTimerTypeBar);
	this->powerBar->setPosition(ccp(this->spriteBg->getContentSize().width-187,21));
	this->powerBar->setMidpoint(ccp(0,0));
	this->powerBar->setBarChangeRate(ccp(1,0));
	this->powerBar->setPercentage(0.0f);
	this->spriteBg->addChild(this->powerBar,9);
	//Level bar
	this->levelSlice = CCProgressTimer::create(CCSprite::create(LEVELSLICE));
	this->levelSlice->setType(kCCProgressTimerTypeBar);
	this->levelSlice->setPosition(ccp(this->spriteBg->getContentSize().width - 97,this->spriteBg->getContentSize().height - 20));
	this->levelSlice->setMidpoint(ccp(0,0));
	this->levelSlice->setBarChangeRate(ccp(1,0));
	this->levelSlice->setPercentage(0.0f);
	this->spriteBg->addChild(this->levelSlice,9);
}
//Add ca vang - loa ca nhieu nhat 
void PlayGameViewOffline::addFish1(){
	Fish *fish = Fish::createFish(CCString::createWithFormat("f1_1.png"));
	fish->type = 1;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    
    fish->setFlipX(true);
    fish->setTag(-10);
    spriteBg->addChild(fish,3);
}

void PlayGameViewOffline::addFish2(){
	int n = 1;
    //    srand(time( 0 ));
    
	int m = rand()%3;
    
	if(m == 0)
		n = 2;
	else if(m==1)
		n = 3;
	else if(m==2)
		n = 4;
    
	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    
    fish->setFlipX(true);
    fish->setTag(-20);
    spriteBg->addChild(fish,3);
}

void PlayGameViewOffline::addFish3(){
	int n = 1;
	//so luong tb 5,6,7,13,19
    //    srand(time( 0 ));
	int m = rand()%5;
	if(m == 0 && this->levelGamePlay >= 6)
        n = 5;
	else if(m == 1)
		n = 6;
	else if(m == 2)
		n = 7;
	else if(m == 3 && this->levelGamePlay >= 16)
		n = 13;
	else if(m == 4 && this->levelGamePlay >= 4)
        n = 19;
    
	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    
    fish->setFlipX(true);
    fish->setTag(-30);
    spriteBg->addChild(fish,3);
}

void PlayGameViewOffline::addFish4(){
	int n = 1;
	//so luong it: 8,9,10
    //    srand(time( 0 ));
    
	int m = rand()%10;
    
	if(m >= 0 && m<= 4)
		n = 8;
	else if(m >= 5 && m <=7 ){
		if(this->levelGamePlay >= 12)
			n = 9;
	}
	else if(m >= 8){
		if(countTurtle < 2 && this->levelGamePlay >= 10){
			n = 10;
		    countTurtle ++;
        }
        else
			n = 1;
    }
    
	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    fish->setFlipX(true);
    fish->setTag(-40);
    spriteBg->addChild(fish,3);
}

void PlayGameViewOffline::addFish5(){
	int n = 1;
	//rat it 11,12,16,17,20
    //    srand(time( 0 ));
    
    int m = rand()%5;
    if(m == 0){
		if(countShark < 1 && this->levelGamePlay >= 10){
            n = 11;
        }
        else
            n = 3;
    }
    else if(m == 1){
        if(countShark < 1){
            n = 12;
        }
        else
            n = 4;
    }
	else if(m == 2 && this->levelGamePlay >= 14)
        n = 16;
    else if(m == 3){
		if(countFisher <1 && this->levelGamePlay >= 8)
            n = 17;
        else
            n = 4;
    }
	else if(m == 4 && this->levelGamePlay >= 2)
		n = 20;

	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	if(fish->type != 20)
		fish->runAction(fish->repeatFishMove);
	fish->addPath();
    fish->setFlipX(true);
    fish->setTag(-50);
    spriteBg->addChild(fish,3);
}

void PlayGameViewOffline::initGun(){
    this->countShark = 0;
    this->countTurtle = 0;
	this->energyCount = 0;
	this->levelCount = 0;

    this->gun = Gun::createGun(CCString::createWithFormat("gun1.png"));
	this->gun->init();
    this->gun->changingGun = false;
    if(gun->type == 0)
        gun->type = 9;
    this->gun->setPosition(ccp(spriteBg->getContentSize().width/2, 45));
	this->gun->setTag(0);
	this->gun->createHeadGun(spriteBg,0.0f);
	this->spriteBg->addChild(gun,11);
	
    //Kiem tra so sung unlock
    gun->numberGunUnlock = this->loadCheckGuns();
    //Load thong so cua sung
    gun->reloadInfoGun();
}

void PlayGameViewOffline::initItem(){
    //KIEM TRA SO LUONG ITEM HIEN CO
    this->loadCheckItem();
	this->chooseItemHunt = false;
	this->bomb = ItemHunt::createItem(CCString::createWithFormat(ITEMBOMB));
	this->freeze = ItemHunt::createItem(CCString::createWithFormat(ITEMFREEZE));
	this->food = ItemHunt::createItem(CCString::createWithFormat(ITEMBREAD));
	this->bombMove = ItemHunt::createItem(CCString::createWithFormat(ITEMBOMBCHOOSED));
	this->freezeMove = ItemHunt::createItem(CCString::createWithFormat(ITEMFREEZECHOOSED));
	this->foodMove = ItemHunt::createItem(CCString::createWithFormat(ITEMBREADCHOOSED));

	bombMove->init();
	freezeMove->init();
	foodMove->init();
	foodMove->typeItem = 3;
	
	bomb->itemPressed = false;
	freeze->itemPressed = false;
	food->itemPressed = false;

	this->bomb->setPosition(ccp(spriteBg->getContentSize().width/2 -80,spriteBg->getContentSize().height - 50));
	this->freeze->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height -50));
	this->food->setPosition(ccp(spriteBg->getContentSize().width/2 + 80, spriteBg->getContentSize().height -50));

	spriteBg->addChild(bomb,10);
	spriteBg->addChild(freeze,10);
	spriteBg->addChild(food,10);

	this->bombMove->setPosition(ccp(-300,-300));
	this->freezeMove->setPosition(ccp(-300,-300));
	this->foodMove->setPosition(ccp(-300,-300));

	spriteBg->addChild(bombMove,9);
	spriteBg->addChild(freezeMove,9);
	spriteBg->addChild(foodMove,9);
}
//////////////////////MISSION ////////////////////////
void PlayGameViewOffline::initMissionMenu(){
	missionMenu = CCSprite::create(BG_MISSION);
    missionMenu->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height + 200));
	buttonAcceptMission = CCMenuItemImage::create(BUTACCEPTMISSION,BUTACCEPTMISSIONPRS,this,menu_selector(PlayGameViewOffline::acceptMission));
    
	CCMenu *menuGame = CCMenu::create(buttonAcceptMission,NULL);
    menuGame->setPosition(ccp(0,0));    
    missionMenu->addChild(menuGame);
	buttonAcceptMission->setPosition(ccp(missionMenu->getContentSize().width/2, missionMenu->getContentSize().height/2 - 140));
    
    CCLabelBMFont *labelCatch1 = CCLabelBMFont::create("+ Bắt 10 \n\n+ Bắt 10\n\n+ Phần thưởng", "font-nhiemvu.fnt");
    
    //CCLabelBMFont *labelCatch2 = CCLabelBMFont::create("+ Bắt 10", "font-nhiemvu.fnt");
    //CCLabelBMFont *labelCatch3 = CCLabelBMFont::create("+ Phần thưởng", "font-nhiemvu.fnt");
    
    labelCatch1->setPosition(ccp(160,missionMenu->getContentSize().height/2 + 10));
    missionMenu->addChild(labelCatch1,15);
    //labelCatch2->setPosition(ccp(130,missionMenu->getContentSize().height/2));
    //missionMenu->addChild(labelCatch2,15);
    //labelCatch3->setPosition(ccp(130,missionMenu->getContentSize().height/2 - 60));
    //missionMenu->addChild(labelCatch3,15);
    
    CCSprite *spCoin = CCSprite::create(ICONBIGMONEY);
    missionMenu->addChild(spCoin,15);
    spCoin->setPosition(ccp(missionMenu->getContentSize().width/2 + 60,missionMenu->getContentSize().height/2 - 82));
    
    spriteBg->addChild(missionMenu,15);
}

void PlayGameViewOffline::callMissionMenu(){
	 CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2));
    missionMenu->runAction(move);
}

void PlayGameViewOffline::hiddenMissionMenu(){
	CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height + 200));
    missionMenu->runAction(move);
    this->showAndEnableAllButton();
}

void PlayGameViewOffline::chooseMission(CCObject *pSender){
    butPause->setEnabled(false);
    this->hiddenEndUneableAllButton();
    this->callMissionMenu();
}

void PlayGameViewOffline::acceptMission(CCObject *pSender){
	butPause->setEnabled(true);
    this->hiddenMissionMenu();
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////INIT EXIT MENU//////////////////
void PlayGameViewOffline::callExitMenu(){
	CCMoveTo *move = CCMoveTo::create(0.2f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2 - 20));
    exitMenu->runAction(move);
}

void PlayGameViewOffline::initExitMenu(){
	exitMenu = CCSprite::create(EXITDIALOG);
    exitMenu->setPosition(ccp(-250, spriteBg->getContentSize().height/2-20));
	buttonAcceptExit = CCMenuItemImage::create(BUTACCEPTEXIT,BUTACCEPTEXITPRS,this,menu_selector(PlayGameViewOffline::acceptExit));
	buttonCancelExit = CCMenuItemImage::create(BUTCANCELEXIT,BUTCANCELEXITPRS,this,menu_selector(PlayGameViewOffline::cancelExit));

	CCMenu *menuGame = CCMenu::create(buttonAcceptExit,buttonCancelExit, NULL);
    menuGame->setPosition(ccp(0,0));    
    exitMenu->addChild(menuGame);
	buttonAcceptExit->setPosition(ccp(exitMenu->getContentSize().width/2 - 100, exitMenu->getContentSize().height/2 - 80));
	buttonCancelExit->setPosition(ccp(exitMenu->getContentSize().width/2 + 100, exitMenu->getContentSize().height/2 - 80));
	buttonAcceptExit->setScale(0.8f);
	buttonCancelExit->setScale(0.8f);

    CCLabelBMFont *labelAlert = CCLabelBMFont::create("Bạn có chắc muốn\n Thoát khỏi game?", "font-nhiemvu.fnt");
        
	labelAlert->setPosition(ccp(exitMenu->getContentSize().width/2,exitMenu->getContentSize().height/2 + 30));
    exitMenu->addChild(labelAlert,15);
    spriteBg->addChild(exitMenu,15);
}

void PlayGameViewOffline::hiddenExitMenu(){
	CCMoveTo *move = CCMoveTo::create(0.2f,ccp(-250,spriteBg->getContentSize().height/2-20));
	exitMenu->runAction(move);
    //this->showAndEnableAllButton();
}

void PlayGameViewOffline::acceptExit(CCObject *pSender){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCDirector::sharedDirector()->replaceScene(ViewMenu::scene());
}

void PlayGameViewOffline::cancelExit(CCObject *pSender){
    this->hiddenExitMenu();
}

void PlayGameViewOffline::exitGame(CCObject *pSender){
	butPause->setEnabled(false);
    this->hiddenEndUneableAllButton();
	this->callExitMenu();
}

//////////////////////////////////////////////////////////////////

///////////////////////SHOP///////////////////////////////////////
void PlayGameViewOffline::initShop(){
    shop = ShopView::createShop(CCString::createWithFormat(SHOPBG));
    shop->init();
    callShop = false;
    
    shop->setPosition(ccp(spriteBg->getContentSize().width/2 + 1000, spriteBg->getContentSize().height/2 - 20));
    spriteBg->addChild(shop,15);
}

void PlayGameViewOffline::chooseItem(CCObject *pSender){
    CCLog("CHOOSE ITEM");
    if(!shop->isEnable){
        callShop = true;
        this->hiddenEndUneableAllButton();
        shop->appearShopView(spriteBg->getContentSize().width/2 - 10);
        
        shop->numberBoom = CCUserDefault::sharedUserDefault()->getIntegerForKey("numBoom");
        shop->numberBread = CCUserDefault::sharedUserDefault()->getIntegerForKey("numBread");
        shop->numberFreeze = CCUserDefault::sharedUserDefault()->getIntegerForKey("numFreeze");
    
        shop->labelNumberItem->setString((CCString::createWithFormat("Số lương: %d",shop->numberBoom))->getCString());
        shop->infoBoom->setString((CCString::createWithFormat("Số lượng đang có: %d",shop->numberBoom))->getCString(),"font-motado2x.fnt");
        shop->infoFreeze->setString((CCString::createWithFormat("Số lượng đang có: %d",shop->numberFreeze))->getCString(),"font-motado2x.fnt");
        shop->infoBread->setString((CCString::createWithFormat("Số lượng đang có: %d",shop->numberBread))->getCString(),"font-motado2x.fnt");

    }
}

//////////////////////////////////////////////////////////////////

///////////////////////PAUSE MENU/////////////////////////////////
void PlayGameViewOffline::initPauseMenu(){
    pauseMenu = CCSprite::create(BG_PAUSE);
    
    pauseMenu->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height + 200));
    butExit            = CCMenuItemImage::create(BUTEXITPLAY,BUTEXITPLAYPRESS,this,menu_selector(PlayGameViewOffline::exitGame));
    butPlayContinue    = CCMenuItemImage::create(BUTPLAYCON,BUTPLAYCONPRESS,this,menu_selector(PlayGameViewOffline:: playContinue));
    
    CCMenu *menuGame = CCMenu::create(butPlayContinue,butExit,NULL);
    menuGame->setPosition(ccp(0,0));
    pauseMenu->addChild(menuGame);
    CCSprite *banner = CCSprite::create(TEXTPAUSE);
    pauseMenu->addChild(banner);
    banner->setPosition(ccp(pauseMenu->getContentSize().width/2, pauseMenu->getContentSize().height - 30));
    butExit->setPosition(ccp(pauseMenu->getContentSize().width/2, pauseMenu->getContentSize().height/2 - 130));
    butPlayContinue->setPosition(ccp(pauseMenu->getContentSize().width/2, pauseMenu->getContentSize().height/2 - 50));
    
    spriteBg->addChild(pauseMenu,15);
    
    // Create the slider
    CCControlSlider *sliderSoundBG = CCControlSlider::create(VOLUMEBAR,VOLUMEBAR,BUTVOLUME);
    CCControlSlider *sliderSoundEffect = CCControlSlider::create(VOLUMEBAR,VOLUMEBAR,BUTVOLUME);
    
	sliderSoundBG->setMinimumValue(0.0f); // Sets the min value of range
    sliderSoundBG->setMaximumValue(1.0f); // Sets the max value of range
    sliderSoundBG->setPosition(ccp(pauseMenu->getContentSize().width/2 + 65, pauseMenu->getContentSize().height - 140));
    
    sliderSoundEffect->setMinimumValue(0.0f); // Sets the min value of range
    sliderSoundEffect->setMaximumValue(1.0f); // Sets the max value of range
    sliderSoundEffect->setPosition(ccp(pauseMenu->getContentSize().width/2 + 65, pauseMenu->getContentSize().height - 200));
    
    sliderSoundBG->addTargetWithActionForControlEvents(this,cccontrol_selector(PlayGameViewOffline::valueSoundBGChanged), CCControlEventValueChanged);
    sliderSoundEffect->addTargetWithActionForControlEvents(this,cccontrol_selector(PlayGameViewOffline::valueSoundEffectChanged), CCControlEventValueChanged);
    
	sliderSoundEffect->setValue(0.5f);
	sliderSoundBG->setValue(0.5f);
    pauseMenu->addChild(sliderSoundBG,15);
    pauseMenu->addChild(sliderSoundEffect,15);

	CCLabelBMFont *fontPause1 = CCLabelBMFont::create("Nhạc nền","font-nhiemvu.fnt");
	CCLabelBMFont *fontPause2 = CCLabelBMFont::create("Hiệu ứng","font-nhiemvu.fnt");

	pauseMenu->addChild(fontPause1,15);
	fontPause1->setPosition(ccp(pauseMenu->getContentSize().width/2 - 110,pauseMenu->getContentSize().height - 130));
	pauseMenu->addChild(fontPause2,15);
	fontPause2->setPosition(ccp(pauseMenu->getContentSize().width/2 - 110,pauseMenu->getContentSize().height - 190));
}

void PlayGameViewOffline::callPauseMenu(){
    CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2));
    pauseMenu->runAction(move);
}

void PlayGameViewOffline::hiddenPauseMenu(){
    CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height + 200));
    pauseMenu->runAction(move);
    this->showAndEnableAllButton();
}

void PlayGameViewOffline::choosePause(CCObject *pSender){
    //CCLog("CHOOSE PAUSE");
    butPause->setEnabled(false);
    this->hiddenEndUneableAllButton();
    this->callPauseMenu();
}

void PlayGameViewOffline::playContinue(CCObject *pSender){
    butPause->setEnabled(true);
    this->hiddenPauseMenu();
}

//Change value of sound background
void PlayGameViewOffline::valueSoundBGChanged(CCObject* sender,CCControlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(pSlider->getValue());
}

//Change value of sound effect
void PlayGameViewOffline::valueSoundEffectChanged(CCObject* sender,CCControlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(pSlider->getValue());
}

void PlayGameViewOffline::onEnterTransitionDidFinish(){
    // Create your audio engine
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound_menu.mp3",true);
}

/////////////////////////////////////////////////////////////////

bool PlayGameViewOffline::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if(this->gun->isVisible()){
        CCPoint pos = pTouch->getLocationInView();  //Toa do cham vao tren man hinh
        pos = CCDirector::sharedDirector()->convertToGL(pos);
        CCPoint point = CCPointMake(pos.x/changePositionWidth,pos.y/changePositionHeight);
        
        if(bomb->boundingBox().containsPoint(point) && this->numBoom > 0)
        {// touch b sprite
            bomb->setVisible(false);
            bomb->itemPressed = true;
            bombMove->setPosition(point);
            return true;
        }
        else if(freeze->boundingBox().containsPoint(point) && this->numFreeze > 0)
        {// touch b sprite
            freeze->setVisible(false);
            freeze->itemPressed = true;
            freezeMove->setPosition(point);
            return true;
        }
        else if(food->boundingBox().containsPoint(point) && this->numBread > 0)
        {// touch b sprite
            food->setVisible(false);
            food->itemPressed = true;
            foodMove->setPosition(point);
            return true;
        }
        
        if(!this->gun->changingGun && !this->gun->shotting && !bomb->itemPressed && !this->gun->shottingLaze){
            float angle = (pos.y -this->gun->getPosition().y*changePositionHeight)/(pos.x-this->gun->getPosition().x*changePositionWidth);
            angle = atanf(angle)/M_PI*180;
            //CCLog("ANGLE: %f",angle);
            if (angle < 0 && pos.x < 240) {
                this->gun->setRotation(-(90+angle));
                this->gun->headGun->setRotation(-(90+angle));
                this->gun->shot(this->gun->getPositionX(),this->gun->getPositionY(),angle);
                if(this->gun->type <=9){
                    this->addBullet(pos.x,pos.y);
                }
            }else if (angle > 0 && pos.x >= 240)
            {
                this->gun->setRotation(90 - angle);
                this->gun->headGun->setRotation((90-angle));
                this->gun->shot(this->gun->getPositionX(),this->gun->getPositionY(),angle);
                if(this->gun->type <= 9){
                    this->addBullet(pos.x,pos.y);
                }
            }
            //CCLog("ROTATION: %f",gun->getRotation());
        }
        return  true;
    }
	else
        return false;
}

void PlayGameViewOffline::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	if (!bomb->itemPressed && !freeze->itemPressed && !food->itemPressed)
    {
        return;
    }
	else{
		CCPoint touchLocation = pTouch->getLocationInView();    
		//CCPoint prevLocation = pTouch->getPreviousLocationInView();    
		touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
		//prevLocation = CCDirector::sharedDirector()->convertToGL( prevLocation );
		CCPoint point = CCPointMake(touchLocation.x/changePositionWidth,touchLocation.y/changePositionHeight);

		if(bomb->itemPressed && !freeze->itemPressed && !food->itemPressed){
			bombMove->setPosition(point);
		}
		else if(!bomb->itemPressed && freeze->itemPressed && !food->itemPressed){
			freezeMove->setPosition(point);
		}
		else if(!bomb->itemPressed && !freeze->itemPressed && food->itemPressed){
			foodMove->setPosition(point);
		}
	}
}

void PlayGameViewOffline::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	if(bomb->itemPressed)
    {
		CCPoint touchLocation = pTouch->getLocationInView();    
        touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
		CCPoint point = CCPointMake(touchLocation.x/changePositionWidth,touchLocation.y/changePositionHeight);

		bomb->itemPressed = false;
		bomb->setVisible(true);
		bombMove->setPosition(ccp(-300,-300));

		ItemHunt *itemEffect = ItemHunt::createItem(CCString::createWithFormat("bom1.png"));
		itemEffect->typeItem = 1;
		itemEffect->setTag(-5);
		itemEffect->setPosition(point);
		itemEffect->loadEffectItem();
		spriteBg->addChild(itemEffect,10);
		this->chooseItemHunt = true;
        //Luu lai so bom hien co
        this->numBoom --;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numBoom", this->numBoom);
        CCUserDefault::sharedUserDefault()->flush();
	}
	if(freeze->itemPressed)
    {
		CCPoint touchLocation = pTouch->getLocationInView();    
        touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
		CCPoint point = CCPointMake(touchLocation.x/changePositionWidth,touchLocation.y/changePositionHeight);

		freeze->itemPressed = false;
		freeze->setVisible(true);
		freezeMove->setPosition(ccp(-300,-300));

		ItemHunt *itemEffect = ItemHunt::createItem(CCString::createWithFormat("set-no-1.png"));
		itemEffect->typeItem = 2;
		itemEffect->setTag(-5);
		itemEffect->setPosition(point);
		itemEffect->loadEffectItem();
		spriteBg->addChild(itemEffect,10);
		this->chooseItemHunt = true;
        //Luu lai so set hien co
        this->numFreeze --;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numFreeze", this->numFreeze);
        CCUserDefault::sharedUserDefault()->flush();
    } 
	if(food->itemPressed)
    {
		CCPoint touchLocation = pTouch->getLocationInView();    
        touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
		CCPoint point = CCPointMake(touchLocation.x/changePositionWidth,touchLocation.y/changePositionHeight);

		food->itemPressed = false;
		food->setVisible(true);
		foodMove->setPosition(ccp(-300,-300));

		ItemHunt *itemEffect = ItemHunt::createItem(CCString::createWithFormat("animation-item-banhmi-1.png"));
		itemEffect->init();
		itemEffect->typeItem = 3;
		itemEffect->setTag(-5);
		itemEffect->setPosition(point);
		itemEffect->loadEffectItem();
		itemEffect->itemAdded = true;
		spriteBg->addChild(itemEffect,10);
		this->chooseItemHunt = true;
        //Luu lai so banh mi hien co
        this->numBread --;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("numBread", this->numBread);
        CCUserDefault::sharedUserDefault()->flush();
    } 
}

//Ban tia set khi thanh nang luong full
void PlayGameViewOffline::shotPower(CCObject *pSender){
	CCMenuItem *item = (CCMenuItem*)pSender;
	item->setVisible(false);
    
    float angle = 0;
    float pHx,pHy;

    if(this->gun->getRotation() < 0)
        angle = -(this->gun->getRotation() + 90);
    else
        angle = 90 - this->gun->getRotation();    
    angle = angle/180*M_PI;

	Web *bullet = Web::createWeb(CCString::createWithFormat("specialBulletShot.png"));
    bullet->isCatching = true;
    bullet->setRotation(gun->getRotation());
    bullet->type = 10;
    bullet->setTag(1000);
    bullet->specialBullet();
    
    //Dau dan laze
    this->spriteBg->addChild(bullet,10);
    if(angle>0){
        pHx = 90*cosf(angle);
        pHy = 90 - 90*sinf(angle);
        bullet->setPosition(ccp(this->gun->getPositionX()+pHx,135 - pHy));
    }
    else if(angle<0){
        pHx = 90*cosf(angle);
        pHy = 90 - 90*sinf(-angle);
        bullet->setPosition(ccp(this->gun->getPositionX()-pHx,135 - pHy));
    }
    
    //Tao dan laze
    for(int i = 2;i<8;i++){
        Web *laze = Web::createWeb(CCString::createWithFormat("specialBulletLaze.png"));
        laze->isCatching = true;
        laze->cocos2d::CCNode::setRotation(this->gun->getRotation());
        laze->setTag(1000);
        laze->specialBullet();
        this->spriteBg->addChild(laze,11);
    
        float delta = 90*i;
        if(angle>0){
            pHx = delta*cosf(angle);
            pHy = delta*(1 - sinf(angle));
            laze->setPosition(ccp(this->gun->getPositionX()+pHx,45 + delta - pHy));
        }
        else if(angle<0){
            pHx = delta*cosf(angle);
            pHy = delta*(1 - sinf(-angle));
            laze->setPosition(ccp(this->gun->getPositionX()-pHx,45 + delta - pHy));
        }
    }
        
    this->gun->reloadNormalGun(this->spriteBg);
    this->gun->shottingLaze = true;
}

//Add bullet khi ban
void PlayGameViewOffline::addBullet(float x, float y){
    CCString *tmp;
    Web *bullet;
	if(gun->type<= 6)
		tmp = CCString::createWithFormat("bullet%d.png",gun->type);
	else
		tmp = CCString::createWithFormat("bullet7.png");
    
    bullet = Web::createWeb(tmp);
	bullet->setPosition(ccp(gun->getPosition().x,gun->getPosition().y));
	bullet->type = gun->type;
	bullet->isCatching = false;
	bullet->setScale(0.6f);
	bullet->setTag(100 + (rand()%200 + rand()%200));
    bullet->setRotation(gun->getRotation());
    bullet->webMove(x/changePositionWidth, y/changePositionHeight, spriteBg);
}

//Doi sung manh hon
void PlayGameViewOffline::chooseMinus(CCObject *pSender){
    if(!this->gun->changingGun && this->gun->type != 10){
        if(this->gun->type > 1){
            int check = 0;
            for(int i = (this->gun->type-1);i>=1;i--){
                if(CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",i))->getCString()) == 1){
                    gun->reloadGun(i, spriteBg->getContentSize().width/2);
                    check = 1;
                    break;
                }
            }
            if(check == 0)
                this->gun->reloadGun(1, spriteBg->getContentSize().width/2);
        }
        else{
            for(int i = 9;i>=1;i--){
                if(CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",i))->getCString()) == 1){
                    this->gun->reloadGun(i, spriteBg->getContentSize().width/2);
                    break;
                }
            }
        }
    }
}

//Doi sung yeu hon
void PlayGameViewOffline::choosePlus(CCObject *pSender){
    if(!this->gun->changingGun && this->gun->type != 10){
        if(this->gun->type < 9){
            int check = 0;
            for(int i = (this->gun->type+1);i<=9;i++){
                if(CCUserDefault::sharedUserDefault()->getIntegerForKey((CCString::createWithFormat("gun%d",i))->getCString()) == 1){
                    gun->reloadGun(i, spriteBg->getContentSize().width/2);
                    check = 1;
                    break;
                }
            }
            if(check == 0)
                this->gun->reloadGun(1, spriteBg->getContentSize().width/2);
        }
        else
            this->gun->reloadGun(1, spriteBg->getContentSize().width/2);
    }
}

//An cac nut cua man hinh game play
void PlayGameViewOffline::hiddenEndUneableAllButton(){
    this->butMinus->setVisible(false);
    this->butPlus->setVisible(false);
    this->gun->setVisible(false);
    this->butItem->setVisible(false);
    this->butMission->setVisible(false);
    this->bomb->setVisible(false);
    this->food->setVisible(false);
    this->freeze->setVisible(false);
    this->butPause->setVisible(false);
    this->levelBar->setVisible(false);
    this->actionBar->setVisible(false);
    this->levelSlice->setVisible(false);
    this->powerBar->setVisible(false);
}

//Hien thi cac nut cua man hinh game play
void PlayGameViewOffline::showAndEnableAllButton(){
    this->butItem->setVisible(true);
    this->butMission->setVisible(true);
    this->bomb->setVisible(true);
    this->food->setVisible(true);
    this->freeze->setVisible(true);
    this->butPause->setVisible(true);
    this->levelBar->setVisible(true);
    this->actionBar->setVisible(true);;
    this->butPlus->setVisible(true);
    this->butMinus->setVisible(true);
    this->gun->setVisible(true);
    this->levelSlice->setVisible(true);
    this->powerBar->setVisible(true);
}

void PlayGameViewOffline::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

//Load level man choi va ranger cua level tuong ung
void PlayGameViewOffline::loadLevel(){
	 CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if(defaults->getIntegerForKey("firstrun") == 0){
        this->levelGamePlay = 1;
		defaults->setIntegerForKey("level",1);
		this->ranger = 205;
        CCLog("Chay ung dung lan dau tien");
        
        //Thiet lap cac du lieu lan dau
        defaults->setIntegerForKey("firstrun", 1);
        //So luong ca bat duoc
		defaults->setIntegerForKey("numFish1",0);
		defaults->setIntegerForKey("numFish5",0);
		defaults->setIntegerForKey("numFish10",0);
		defaults->setIntegerForKey("numFish11",0);
		defaults->setIntegerForKey("numFish12",0);
		defaults->setIntegerForKey("numFish13",0);
        //Ghi nho tong so ca da bat duoc
        defaults->setIntegerForKey("totalFish1",0);
		defaults->setIntegerForKey("totalFish2",0);
		defaults->setIntegerForKey("totalFish3",0);
		defaults->setIntegerForKey("totalFish4",0);
		defaults->setIntegerForKey("totalFish5",0);
		defaults->setIntegerForKey("totalFish6",0);
        defaults->setIntegerForKey("totalFish7",0);
		defaults->setIntegerForKey("totalFish8",0);
		defaults->setIntegerForKey("totalFish9",0);
		defaults->setIntegerForKey("totalFish10",0);
		defaults->setIntegerForKey("totalFish11",0);
		defaults->setIntegerForKey("totalFish12",0);
        defaults->setIntegerForKey("totalFish13",0);
		defaults->setIntegerForKey("totalFish16",0);
		defaults->setIntegerForKey("totalFish17",0);
		defaults->setIntegerForKey("totalFish19",0);
		defaults->setIntegerForKey("totalFish20",0);        
        //Thiet lap sung
        defaults->setIntegerForKey("gun1",1);
        defaults->setIntegerForKey("lvGun1",1);
		defaults->setIntegerForKey("veloGun1",1);
        
		defaults->setIntegerForKey("gun2",0);
        defaults->setIntegerForKey("lvGun2",1);
		defaults->setIntegerForKey("veloGun2",1);
        
		defaults->setIntegerForKey("gun3",0);
		defaults->setIntegerForKey("lvGun3",1);
		defaults->setIntegerForKey("veloGun3",1);
        
        defaults->setIntegerForKey("gun4",0);
        defaults->setIntegerForKey("lvGun4",1);
		defaults->setIntegerForKey("veloGun4",1);
        
		defaults->setIntegerForKey("gun5",0);
		defaults->setIntegerForKey("lvGun5",1);
		defaults->setIntegerForKey("veloGun5",1);
        
        defaults->setIntegerForKey("gun6",0);
        defaults->setIntegerForKey("lvGun6",1);
		defaults->setIntegerForKey("veloGun6",1);
        
		defaults->setIntegerForKey("gun7",0);
        defaults->setIntegerForKey("lvGun7",1);
		defaults->setIntegerForKey("veloGun7",1);
        
        defaults->setIntegerForKey("gun8",0);
        defaults->setIntegerForKey("lvGun8",1);
		defaults->setIntegerForKey("veloGun8",1);
        
		defaults->setIntegerForKey("gun9",0);
        defaults->setIntegerForKey("lvGun9",1);
		defaults->setIntegerForKey("veloGun9",1);
        
        //So luong vat pham hien co
        defaults->setIntegerForKey("numBoom", 3);
        defaults->setIntegerForKey("numFreeze", 3);
        defaults->setIntegerForKey("numBread", 3);
    }
    else{
		CCLog("Chay lan hai");
		this->levelGamePlay = defaults->getIntegerForKey("level");
        CCArray *pConfInfo;
        pConfInfo = CCArray::createWithContentsOfFile(FILECONFIGLEVEL);
        this->ranger = ((CCString*)pConfInfo->objectAtIndex(this->levelGamePlay - 1))->floatValue();
	}
    CCUserDefault::sharedUserDefault()->flush();
    CCLog("level: %d - ranger: %f",this->levelGamePlay,this->ranger);
}

//Load so ca dac biet da bat duoc
void PlayGameViewOffline::loadCheckFish(){
	CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    
    this->checkFish1    = defaults->getIntegerForKey("numFish1");
    this->checkFish5    = defaults->getIntegerForKey("numFish5");
    this->checkFish10    = defaults->getIntegerForKey("numFish10");
    this->checkFish11    = defaults->getIntegerForKey("numFish11");
    this->checkFish12    = defaults->getIntegerForKey("numFish12");
    this->checkFish13    = defaults->getIntegerForKey("numFish13");
}
//Luu lai gia tri so ca dac biet bat duoc
void PlayGameViewOffline::setCheckFish(){
	 CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
	 defaults->setIntegerForKey("numFish1",this->checkFish1);
	 defaults->setIntegerForKey("numFish5",this->checkFish5);
	 defaults->setIntegerForKey("numFish10",this->checkFish10);
	 defaults->setIntegerForKey("numFish11",this->checkFish11);
	 defaults->setIntegerForKey("numFish12",this->checkFish12);
	 defaults->setIntegerForKey("numFish13",this->checkFish13);
	 CCUserDefault::sharedUserDefault()->flush();
	 
    //CCLog("\n\nYELLOW FISH: %d\nFAIRY FISH: %d\nTURTLE: %d\nBLUE SHARK: %d\nYELLOW SHARK: %d\nFISH 13: %d",this->checkFish1,this->checkFish5,this->checkFish10,this->checkFish11,this->checkFish12,this->checkFish13);
}

int PlayGameViewOffline::loadCheckGuns(){
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    int count = 0;
    
    for (int i = 1; i<=9 ;i++) {
        CCString *str = CCString::createWithFormat("gun%d",i);
        if(defaults->getIntegerForKey(str->getCString()) == 1)
            count++;
    }
    CCLog("number gun unlock: %d",count);
    return count;
}

void PlayGameViewOffline::setCheckGuns(){
    
}
//Load so luong vat pham hien co
void PlayGameViewOffline::loadCheckItem(){
    CCUserDefault*defaults = CCUserDefault::sharedUserDefault();
    this->numBoom   = defaults->getIntegerForKey("numBoom");
    this->numFreeze = defaults->getIntegerForKey("numFreeze");
    this->numBread  = defaults->getIntegerForKey("numBread");
    CCLog("Co: %d boom - %d Freeze - %d bread",this->numBoom, this->numFreeze, this->numBread);
}

PlayGameViewOffline::PlayGameViewOffline(void){
    
}

PlayGameViewOffline::~PlayGameViewOffline(void){
    
}
