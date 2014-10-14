//
//  PlayGameView.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "PlayGameView.h"
#include "LinkResources.h"
#include "ViewMenu.h"
#include "Coin.h"

CCScene* PlayGameView::scene(){
	CCScene *scene=NULL;
	do{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		PlayGameView *layer = PlayGameView::create();
        
		CC_BREAK_IF(! layer);
        // add layer as a child to scene
        scene->addChild(layer);
	}
	while(0);
	return scene;
}

bool PlayGameView::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCLayer::init());
        
        //////////////////////////////////////////////////////////////////////////
        size = CCDirector::sharedDirector()->getWinSize();
        // SET UP DEVICE
        
        
        this->setTouchEnabled(true);
        this->initBackGround();
        this->initPauseMenu();
        this->initShop();
        this->initGun();
        
        spriteBg->setScaleX(size.width/spriteBg->getContentSize().width);
        spriteBg->setScaleY(size.height/spriteBg->getContentSize().height);
        changePositionWidth = size.width/spriteBg->getContentSize().width;
        changePositionHeight = size.height/spriteBg->getContentSize().height;
        
        ///////ONLINE////////////
        this->connectToAppWarp();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void PlayGameView::startGame()
{
    // Initialize arrays
    _targets = new CCArray();
    _projectiles = new CCArray();
    
    srand((unsigned)time(0));
    this->addFish1();
    this->addFish2();
    this->addFish3();
    this->addFish4();
    this->addFish5();
    
    this->schedule(schedule_selector(PlayGameView::updateGame),0.2f);
    this->schedule(schedule_selector(PlayGameView::updateFish),0.05f);
    
    isConnected = true;
}

void PlayGameView::updateGame(float dt)
{
    CCObject *objectTmp = NULL;
    CCARRAY_FOREACH(spriteBg->getChildren(), objectTmp)
	{
        Fish *fTmp = NULL;
        Web *bTmp = NULL;
        
        fTmp = (Fish*)objectTmp;
        if(fTmp->getTag() <= -10){
            if(fTmp->fishDied) {
                continue;
            }
            CCObject *objectTp = NULL;
            CCARRAY_FOREACH(spriteBg->getChildren(),objectTp)
            {
                bTmp = (Web*)objectTp;
                if(bTmp->getTag()>= 100){
					if(fTmp->boundingBox().containsPoint(bTmp->getPosition()) && bTmp->isCatching && (bTmp->getTag() != fTmp->tagOfWebCatchedFish)){
                        fTmp->tagOfWebCatchedFish = bTmp->getTag();
                        fTmp->blood -= gun->dame;
						//bTmp->isCatching = false;
						//CCLog("BLOOD: %d - BULLET TAG: %d",fTmp->blood,bTmp->getTag());
						if(fTmp->blood <= 0){
                            fTmp->fishDied = true;
                            fTmp->runFishDie(spriteBg);
                        }
                    }
                }
            }
        }
	}
    
    if(callShop && !shop->isEnable){
        callShop = false;
        this->showAndEnableAllButton();

    }
}

void PlayGameView::updateFish(float dt){
    CCObject *obTmp = NULL;
    Fish *fTmp;
    countShark  = 0;
    countTurtle = 0;
    int countF1 = 0,countF2 = 0,countF3 = 0,countF4 = 0,countF5 = 0;

    CCARRAY_FOREACH(spriteBg->getChildren(), obTmp){
        fTmp = (Fish*)obTmp;
        
		if(fTmp->type == 10)
            countTurtle ++;
        if(fTmp->type == 11 || fTmp->type == 12)
            countShark ++;
        
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
			

		//if(fTmp->getTag() == -50)
			//countF5++;
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

void PlayGameView::initBackGround(){
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
    actionBar =  CCSprite::create(ACTIONBAR);
    enemyActionBar = CCSprite::create(ACTIONBAR);
    enemyActionBar->setRotation(180);
    levelBar  =  CCSprite::create(LEVELBAR);
    
    butItem      = CCMenuItemImage::create(BUTITEM,BUTITEM ,this,menu_selector(PlayGameView::chooseItem));
    butMission   = CCMenuItemImage::create(BUTMISSION,BUTMISSION,this,menu_selector(PlayGameView::chooseMission));
    butPause     = CCMenuItemImage::create(BUTPAUSE,BUTPAUSEPRESS,this,menu_selector(PlayGameView::choosePause));
    butMinus     = CCMenuItemImage::create(BUTMINUS,BUTMINUSPRESS,this,menu_selector(PlayGameView::chooseMinus));
    butPlus      = CCMenuItemImage::create(BUTPLUS,BUTPLUSPRESS,this,menu_selector(PlayGameView::choosePlus));
    butBoom      = CCMenuItemImage::create(ITEMBOMB,ITEMBOMB,this,menu_selector(PlayGameView::chooseBoom));
    butFood      = CCMenuItemImage::create(ITEMBREAD,ITEMBREAD,this,menu_selector(PlayGameView::chooseFood));
    butFreeze    = CCMenuItemImage::create(ITEMFREEZE,ITEMFREEZE,this,menu_selector(PlayGameView::chooseFreeze));
    //
    //CCMenu *menuGame = CCMenu::create(butItem,butMission,butPause,butMinus,butPlus,butBoom,butFood,butFreeze,NULL);
    CCMenu *menuGame = CCMenu::create(butPause,butMinus,butPlus,NULL);
    menuGame->setPosition(ccp(0,0));
    
    this->addChild(spriteBg);
    spriteBg->setPosition(ccp(size.width/2,size.height/2));
    
    spriteBg->addChild(actionBar,4);
    spriteBg->addChild(enemyActionBar,4);
    //spriteBg->addChild(levelBar,10);
    spriteBg->addChild(menuGame,10);
    
    actionBar->setPosition(ccp(spriteBg->getContentSize().width/2 - 40, 45));
    enemyActionBar->setPosition(ccp(spriteBg->getContentSize().width/2 + 40,435));
    
    levelBar->setPosition(ccp(spriteBg->getContentSize().width - 130,spriteBg->getContentSize().height - 25));
    
    butPause->setPosition(ccp(spriteBg->getContentSize().width - 40,32));
    
    butItem->setPosition(ccp(45,spriteBg->getContentSize().height - 40));
    
    butMission->setPosition(ccp(125, spriteBg->getContentSize().height - 40));
    
    butBoom->setPosition(ccp(spriteBg->getContentSize().width/2 -80,spriteBg->getContentSize().height - 35));
    
    butFreeze->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height -35));
    
    butFood->setPosition(ccp(spriteBg->getContentSize().width/2 + 80, spriteBg->getContentSize().height - 35));
    
    butMinus->setPosition(ccp(spriteBg->getContentSize().width/2 - 65, 25));
    
    butPlus->setPosition(ccp(spriteBg->getContentSize().width/2 + 65, 25));

}

//Add ca vang - loai ca nhieu nhat
void PlayGameView::addFish1(){
	Fish *fish = Fish::createFish(CCString::createWithFormat("f1_1.png"));
	fish->type = 1;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    
    fish->setFlipX(true);
    fish->setTag(-10);
    spriteBg->addChild(fish,3);
}

void PlayGameView::addFish2(){
	int n;
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

void PlayGameView::addFish3(){
	int n;
	//so luong tb 5,6,7,13,19
    //    srand(time( 0 ));
	int m = rand()%5;
	if(m == 0)
		n = 5;
	else if(m == 1)
		n = 6;
	else if(m == 2)
		n = 7;
	else if(m == 3)
		n = 13;
    else if(m == 4)
        n = 6;
    
	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    
    fish->setFlipX(true);
    fish->setTag(-30);
    spriteBg->addChild(fish,3);
}

void PlayGameView::addFish4(){
	int n;
	//so luong it: 8,9,10
    //    srand(time( 0 ));
    
	int m = rand()%10;
    
	if(m >= 0 && m<= 4)
		n = 8;
	else if(m >= 5 && m <=7 )
		n = 9;
	else if(m >= 8){
        if(countTurtle < 2){
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

void PlayGameView::addFish5(){
	int n = 0;
	//rat it 11,12,16,17,20
    //    srand(time( 0 ));
    
    int m = rand()%5;
    if(m == 0){
        if(countShark < 1){
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
    else if(m == 2)
        n = 16;
    else if(m == 3)
        n = 17;
    else if(m == 4)
		n = 1;
    
	Fish *fish = Fish::createFish(CCString::createWithFormat("f%d_1.png",n));
	fish->type = n;
	fish->init();
	fish->runAction(fish->repeatFishMove);
	fish->addPath();
    fish->setFlipX(true);
    fish->setTag(-50);
    spriteBg->addChild(fish,3);
}

void PlayGameView::initGun(){
    countShark = 0;
    countTurtle = 0;
    
    gun = Gun::createGun(CCString::createWithFormat("gun1.png"));
	gun->init();
    gun->changingGun = false;
    if(gun->type == 0)
        gun->type = 9;
    gun->setPosition(ccp(spriteBg->getContentSize().width/2, 45));
	gun->setTag(0);
	gun->createHeadGun(spriteBg,0.0f);
	spriteBg->addChild(gun,11);
    
    ///ENEMYGUN
    enemyGun = Gun::createGun(CCString::createWithFormat("gun1.png"));
	enemyGun->init();
    enemyGun->enemyGun = true;
    enemyGun->setRotation(180.0f);
    enemyGun->changingGun = false;
    if(enemyGun->type == 0)
        enemyGun->type = 9;
    enemyGun->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height - 45));
	enemyGun->setTag(0);
	enemyGun->createHeadGun(spriteBg,180.0f);
	spriteBg->addChild(enemyGun,11);
}

void PlayGameView::initPauseMenu(){
    pauseMenu = CCSprite::create(BG_PAUSE);
    
    pauseMenu->setPosition(ccp(spriteBg->getContentSize().width/2, spriteBg->getContentSize().height + 200));
    butExit            = CCMenuItemImage::create(BUTEXITPLAY,BUTEXITPLAYPRESS,this,menu_selector(PlayGameView::exitGame));
    butPlayContinue    = CCMenuItemImage::create(BUTPLAYCON,BUTPLAYCONPRESS,this,menu_selector(PlayGameView:: playContinue));
    
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
    sliderSoundBG = CCControlSlider::create(VOLUMEBAR,VOLUMEBAR,BUTVOLUME);
    sliderSoundEffect = CCControlSlider::create(VOLUMEBAR,VOLUMEBAR,BUTVOLUME);

    sliderSoundBG->setMinimumValue(0.0f); // Sets the min value of range
    sliderSoundBG->setMaximumValue(1.0f); // Sets the max value of range
    sliderSoundBG->setPosition(ccp(pauseMenu->getContentSize().width/2 + 60, pauseMenu->getContentSize().height - 130));

    sliderSoundEffect->setMinimumValue(0.0f); // Sets the min value of range
    sliderSoundEffect->setMaximumValue(1.0f); // Sets the max value of range
    sliderSoundEffect->setPosition(ccp(pauseMenu->getContentSize().width/2 + 60, pauseMenu->getContentSize().height - 190));


    sliderSoundBG->addTargetWithActionForControlEvents(this,cccontrol_selector(PlayGameView::valueSoundBGChanged), CCControlEventValueChanged);
    
    sliderSoundEffect->addTargetWithActionForControlEvents(this,cccontrol_selector(PlayGameView::valueSoundEffectChanged), CCControlEventValueChanged);
    
    pauseMenu->addChild(sliderSoundBG);
    pauseMenu->addChild(sliderSoundEffect);
}

void PlayGameView::initShop(){
    shop = ShopView::createShop(CCString::createWithFormat(SHOPBG));
    shop->init();
    callShop = false;
    
    shop->setPosition(ccp(spriteBg->getContentSize().width/2 + 1000, spriteBg->getContentSize().height/2 - 20));
    spriteBg->addChild(shop,15);
}

void PlayGameView::valueSoundBGChanged(CCObject* sender,unsigned int controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(pSlider->getValue());
}

void PlayGameView::valueSoundEffectChanged(CCObject* sender,unsigned int controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(pSlider->getValue());
}

void PlayGameView::onEnterTransitionDidFinish()
{
    //SLIDER BAR
    // Create your audio engine
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound_menu.mp3",true);    
    sliderSoundEffect->setValue(1.0f);
    sliderSoundBG->setValue(1.0f);
}

void PlayGameView::callPauseMenu(){
    CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height/2));
    pauseMenu->runAction(move);
}

void PlayGameView::hiddenPauseMenu(){
    CCMoveTo *move = CCMoveTo::create(0.3f,ccp(spriteBg->getContentSize().width/2,spriteBg->getContentSize().height + 200));
    pauseMenu->runAction(move);
    this->showAndEnableAllButton();
}

bool PlayGameView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!gun->changingGun && gun->isVisible() && !gun->shotting){

        CCPoint pos = pTouch->getLocationInView();  //Toa do cham vao tren man hinh   
        pos = CCDirector::sharedDirector()->convertToGL(pos);
        
        float angle = (pos.y - gun->getPosition().y*changePositionHeight)/(pos.x-gun->getPosition().x*changePositionWidth);
        
        angle = atanf(angle)/M_PI*180;
            
        if (angle < 0 && pos.x < 240) {
            gun->setRotation(-(90+angle));
            gun->headGun->setRotation(-(90+angle));
            gun->shot(gun->getPositionX(),gun->getPositionY(),angle);
            this->addBullet(pos.x,pos.y);
                
        }else if (angle > 0 && pos.x >= 240)
        {
            gun->setRotation(90 - angle);
            gun->headGun->setRotation((90-angle));
            gun->shot(gun->getPositionX(),gun->getPositionY(),angle);
            this->addBullet(pos.x,pos.y);
        }

        if (!isConnected)
        {
            return false;
        }
        
        //GUI DU LIEU CHO CAC MAY KHAC
        float length;
        float velocity = 480/1;
        float realMoveDuration = length/velocity;
        this->sendData(pos.x, pos.y, realMoveDuration);
    }
    
    return true;
}

void PlayGameView::addBullet(float x, float y){
    Web *bullet;
    CCString *tmp;
	if(gun->type<= 6)
		tmp = CCString::createWithFormat("bullet%d.png",gun->type);
	else 
		tmp = CCString::createWithFormat("bullet6.png");

    bullet = Web::createWeb(tmp);
	bullet->setPosition(ccp(gun->getPosition().x,gun->getPosition().y));
	bullet->type = gun->type;
	bullet->isCatching = false;
	bullet->setScale(0.6f);
	bullet->setTag(100 + (rand()%200 + rand()%200));
    bullet->setRotation(gun->getRotation());
    bullet->webMove(x/changePositionWidth, y/changePositionHeight, spriteBg);
}

void PlayGameView::chooseFreeze(CCObject *pSender){
    CCLog("CHOOSE FREEZE");
}

void PlayGameView::chooseBoom(CCObject *pSender){
    CCLog("CHOOSE BOOM");
}

void PlayGameView::chooseFood(CCObject *pSender){
    CCLog("CHOOSE FOOD");
}

void PlayGameView::chooseItem(CCObject *pSender){
    CCLog("CHOOSE ITEM");
    if(!shop->isEnable){
        callShop = true;
        this->hiddenEndUneableAllButton();
        shop->appearShopView(spriteBg->getContentSize().width/2 - 10);
    }
}

void PlayGameView::chooseMinus(CCObject *pSender){
    if(!gun->changingGun){
        if(gun->type > 1)
            gun->reloadGun(gun->type - 1, spriteBg->getContentSize().width/2);
        else
            gun->reloadGun(9,spriteBg->getContentSize().width/2);
    }
}

void PlayGameView::chooseMission(CCObject *pSender){
    CCLog("CHOOSE MISSION");
}

void PlayGameView::choosePause(CCObject *pSender){
    CCLog("CHOOSE PAUSE");
    butPause->setEnabled(false);
    this->hiddenEndUneableAllButton();
    this->callPauseMenu();
}

void PlayGameView::choosePlus(CCObject *pSender){
    if(!gun->changingGun){
        if(gun->type < 9)
            gun->reloadGun(gun->type + 1, spriteBg->getContentSize().width/2);
        else
            gun->reloadGun(1, spriteBg->getContentSize().width/2);
    }
}

void PlayGameView::exitGame(CCObject *pSender){
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCDirector::sharedDirector()->replaceScene(ViewMenu::scene());
}

void PlayGameView::playContinue(CCObject *pSender){
    butPause->setEnabled(true);
    this->hiddenPauseMenu();
}

void PlayGameView::hiddenEndUneableAllButton(){
    butMinus->setVisible(false);
    butPlus->setVisible(false);
    gun->setVisible(false);
    //butItem->setVisible(false);
    //butMission->setVisible(false);
    //butBoom->setVisible(false);
    //butFood->setVisible(false);
    //butFreeze->setVisible(false);
    butPause->setVisible(false);
    //levelBar->setVisible(false);
    actionBar->setVisible(false);
}

void PlayGameView::showAndEnableAllButton(){
    //butItem->setVisible(true);
    //butMission->setVisible(true);
    //butBoom->setVisible(true);
    //butFood->setVisible(true);
    //butFreeze->setVisible(true);
    butPause->setVisible(true);
    //levelBar->setVisible(true);
    actionBar->setVisible(true);;
    butPlus->setVisible(true);
    butMinus->setVisible(true);
    gun->setVisible(true);
}

void PlayGameView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

std::string genRandom()
{
	std::string charStr;
	srand (time(NULL));
    
	for (int i = 0; i < 10; ++i) {
		charStr += (char)(65+(rand() % (26)));
	}
    
	return charStr;
}

/////ONLINE//////////////////
/***
 * AppWarp Helper Methods
 */

void PlayGameView::updateEnemyStatus(CCPoint destination,float actualDuration)
{
    if(!enemyGun->changingGun && enemyGun->isVisible() && !enemyGun->shotting){
        isEnemyAdded = true;
        CCString *tmp;
        if(enemyGun->type<= 6)
            tmp = CCString::createWithFormat("bullet%d.png",enemyGun->type);
        else
            tmp = CCString::createWithFormat("bullet6.png");
        Web *bullet = Web::createWeb(tmp);
        
        float desY = destination.y;
        float desX = destination.x;
        
        float f = (size.height/2 - destination.y);
        
        desY = desY + 2*f;
                
        float angle = (desY - enemyGun->getPosition().y*changePositionHeight)/(desX-enemyGun->getPosition().x*changePositionWidth);
        angle = atanf(angle)/M_PI*180 + 180;
        
        
        if (angle > 180 && desX < size.width/2) {
            enemyGun->setRotation(-(270 + angle));
            enemyGun->headGun->setRotation(-(270+angle));
            enemyGun->shot(enemyGun->getPositionX(),enemyGun->getPositionY(),angle);            
        }else if (angle < 180 && destination.x >= size.width/2)
        {
            enemyGun->setRotation(270 - angle);
            enemyGun->headGun->setRotation((270-angle));
            enemyGun->shot(enemyGun->getPositionX(),enemyGun->getPositionY(),angle);
        }
        
        bullet->setPosition(ccp(enemyGun->getPosition().x,enemyGun->getPosition().y));
        bullet->type = enemyGun->type;
        bullet->isCatching = false;
        bullet->setScale(0.6f);
        bullet->setTag(100 + (rand()%200 + rand()%200));
        bullet->setRotation(enemyGun->getRotation());
        bullet->webMove(desX/changePositionWidth, desY/changePositionHeight, spriteBg);
        _targets->addObject(bullet);
    }
}

/////////////////////////////

PlayGameView::PlayGameView(void){
    
}

PlayGameView::~PlayGameView(void){
    
}
