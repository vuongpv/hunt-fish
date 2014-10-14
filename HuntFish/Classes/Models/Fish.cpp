//
//  Fish.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "Fish.h"
#include<stdio.h>
#include<stdlib.h>
#include"Coin.h"
#include "ItemHunt.h"

bool Fish::init(){
    bool bRect = false;
    do{
		this->fishStopMove = false;
        this->velocity   = 1;
        this->fishDied   = false;
        this->blood      = 10;
        this->point      = 1;
        this->experience = 1;
        this->fishEatBread = false;
		this->loadFishAnimation();
		this->loadFishDie();
        bRect = true;
    }
    while (0);
    return  bRect;
}

Fish* Fish::createFish(CCString *frameName){
    Fish* fishSprite = new Fish();
    if(fishSprite && fishSprite->initWithFile(frameName->getCString())){
        fishSprite->autorelease();
        return fishSprite;
    }
    else
        return NULL;
}

void Fish::loadFishAnimation(){
    this->fishDied = false;
    int countFor = 0;
    switch (this->type) {
        case 1:
			//CA VANG
            this->velocity = TIMEANIMATION1;
            this->point = 1;
            this->experience = 1;
			this->blood = 100 + rand()%200;
            countFor = 4;
            break;
        case 2:
			//CA VANG SOC
            this->velocity = TIMEANIMATION1;
            this->point = 3;
            this->experience = 6;
            countFor = 4;
			this->blood = 200 + rand()%200;
            break;
        case 3:
			//CA DO
            this->velocity = TIMEANIMATION1;
            this->point = 5;
            this->experience = 15;
            countFor = 4;
			this->blood = 400 + rand()%200;
            break;
        case 4:
			//CA XANH
            this->velocity = TIMEANIMATION1;
            this->point = 8;
            this->experience = 32;
			this->blood = 600 + rand()%400;
            countFor = 4;
            break;
        case 5:
			//CA GAI
            this->velocity = TIMEANIMATION1;
            this->point = 10;
            this->experience = 50;
			this->blood = 800 + rand()%400;
            countFor = 4;
            break;
        case 6:
			//SUA 1
            this->velocity = TIMEANIMATION2;
            this->point = 30;
            this->experience = 180;
			this->blood = 2800 + rand()%600;
            countFor = 8;
            break;
        case 7:
			//SUA 2
            this->velocity = TIMEANIMATION3;
            this->point = 30;
            this->experience = 210;
			this->blood = 2800 + rand()%200;
            countFor = 6;
            break;
        case 8:
			//CA SOI DUONG
            this->velocity = TIMEANIMATION1;
            this->point = 40;
            this->experience = 320;
			this->blood = 3500 + rand()%1500;
            countFor = 8;
            break;
        case 9:
			//CA DUOI VANG
            this->velocity = TIMEANIMATION1;
            this->point = 50;
            this->experience = 450;
			this->blood = 5000 + rand()%2000;
            countFor = 6;
            break;
        case 10:
			//RUA
            this->velocity = TIMEANIMATION2;
            this->point = 60;
            this->experience = 600;
			this->blood = 6000 + rand()%2000;
            countFor = 6;
            break;
        case 11:
			//CA MAP XANH
            this->velocity = TIMEANIMATION2;
            this->point = 100;
            this->experience = 1100;
			this->blood = 20000 + rand()%30000;
            countFor = 8;
            break;
        case 12:
			//CA MAP VANG
            this->velocity = TIMEANIMATION2;
            this->point = 100;
            this->experience = 1200;
			this->blood = 30000 + rand()%10000;
            countFor = 8;
            break;
        case 13:
			this->velocity = TIMEANIMATION2;
			this->point = 60;
			this->experience = 780;
			this->blood = 5500 + rand()%1000;
            countFor = 14;
            break;
        case 16:
			this->velocity = TIMEANIMATION2;
			this->point = 0;
			this->experience = 5000;
			this->blood = 50000 + rand()%25000;
            countFor = 12;
            break;
        case 17:
            this->velocity = TIMEANIMATION2;
            this->point = 100;
            this->experience = 6000;
			this->blood = 40000 + rand()%20000;
            countFor = 14;
            break;
        case 19:
			this->velocity = TIMEANIMATION1;
			this->point = 2;
			this->experience = 5;
			this->blood = 280 + rand()%80;
            countFor = 10;
            break;
        case 20:
			this->velocity = TIMEANIMATION2;
			this->blood = 900;
			this->point = 1;
			this->experience = 1;
            countFor = 0;
            break;
            
        default:
            break;
    }
    
    CCSize textureSize;
    CCRect textureRect;
    CCSpriteFrame *spriteFrame;
    CCArray *animationFrames;
    CCAnimate *animate;
    CCTexture2D *texture;
    animationFrames = CCArray::createWithCapacity(3);
    
	if(countFor > 0){
		for(int i = 1;i<=countFor;i++){
	        CCString *stringFile = CCString::createWithFormat("f%d_%i.png",this->type,i);
		    texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
			textureSize = texture->getContentSize();
			textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
			spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
			animationFrames->addObject(spriteFrame);
	    }
    
		CCAnimation *fishMove = CCAnimation::createWithSpriteFrames(animationFrames,this->velocity);
		animate  = CCAnimate::create(fishMove);
		this->repeatFishMove   = CCRepeatForever::create(animate);
	}
}

void Fish::loadFishDie(){
    int countFor = 4;
    switch (this->type) {
        case 1:
            countFor = 5;
            break;
        case 2:
            countFor = 5;
            break;
        case 3:
            countFor = 5;
            break;
        case 4:
            countFor = 5;
            break;
        case 5:
            countFor = 5;
            break;
        case 6:
            countFor = 9;
            break;
        case 7:
            countFor = 7;
            break;
        case 8:
            countFor = 9;
            break;
        case 9:
            countFor = 7;
            break;
        case 10:
            countFor = 7;
            break;
        case 11:
            countFor = 9;
            break;
        case 12:
            countFor = 9;
            break;
        case 13:
            countFor = 0;
            break;
        case 16:
            countFor = 0;
            break;
        case 17:
            countFor = 0;
            break;
		case 20:
			countFor = 0;
			break;
        default:
            break;
    }
    
	if(this->type != 17 && this->type != 13 && this->type != 16 && this->type != 20 && this->type != 19){
        CCSize textureSize;
        CCRect textureRect;
        CCSpriteFrame *spriteFrame;
        CCArray *animationFrames;
        CCAnimate *animate;
        CCTexture2D *texture;//Chua cac anh mario khi chuyen dong
        animationFrames = CCArray::createWithCapacity(3);
        
        for(int i = countFor;i <= countFor + 3;i++){
            CCString *stringFile = CCString::createWithFormat("f%d_%i.png",this->type,i);
            texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
            textureSize = texture->getContentSize();
            textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
            spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
            animationFrames->addObject(spriteFrame);
        }
        
        fishDie = CCAnimation::createWithSpriteFrames(animationFrames,this->velocity);
        animate  = CCAnimate::create(fishDie);
		this->repeatFishDie   = CCRepeatForever::create(animate);
		this->repeatFishDie->retain();
    }   
}

void Fish::runFishDie(CCSprite *spBG){
	this->stopAllActions();
	this->fishDied = true;        

	if(this->type != 17 && this->type != 13 && this->type != 16 && this->type != 20 && this->type != 19){
		this->runAction(this->repeatFishDie);
        this->runAction(cocos2d::CCSequence::create(
                                                    CCDelayTime::create(1.0f),CCCallFuncND::create(this,callfuncND_selector(Fish::removeFishDie),(void*) spBG),NULL));
	}
	else{
		this->runAction(cocos2d::CCSequence::create(
                                                    CCDelayTime::create(1.0f),CCCallFuncND::create(this,callfuncND_selector(Fish::removeFishDie),(void*) spBG),NULL));
	}
}

void Fish::addPath(){
    if(this->type == 11 || this->type == 12)
        this->setScale(0.8f);

//    if(this->type == 17)
//        this->setScale(1.5f);
    
    if(this->type == 10)
        this->setScale(0.8f);
       
	switch(this->type){
		case 1:
			this->addPathF1();
			break;
		case 2:
			this->addPathF2();
			break;
		case 3:
			this->addPathF3();
			break;
		case 4:
			this->addPathF4();
			break;
		case 5:
			this->addPathF5();
			break;
		case 6:
			this->addPathF6();
			break;
		case 7:
			this->addPathF7();
			break;
		case 8:
			this->addPathF8();
			break;
		case 9:
			this->addPathF9();
			break;
		case 10:
			this->addPathF10();
			break;
		case 11:
			this->addPathF11();
			break;
		case 12:
			this->addPathF12();
			break;
		case 13:
			this->addPathF13();
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			this->addPathF16();
			break;
		case 17:
            this->addPathF17();
			break;
		case 19:
			this->addPathF19();
			break;
		case 20:
			this->addPathF20();
			break;
		default:
			break;
	}
}

void Fish::addPathF1(){
//    srand((unsigned)time(0));
	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 10);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 10);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 10);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 7);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 10);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 7);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 11);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 10);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 7);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 7);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 6);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 7);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 7);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 7);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 7);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 7);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 7);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 11);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 11);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 11);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 11);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 5);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 5);
			break;
    }
}

void Fish::addPathF2(){
//    srand((unsigned)time(0));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF3(){
//    srand((unsigned)time(0));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF4(){
//    srand(time( 0 ));

    int path = rand()%23;
    switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF5(){
//    srand(time( 0 ));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF6(){
//    srand(time( 0 ));

	int path = rand()%23;
	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF7(){
//    srand(time( 0 ));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(300, 600),ccp(350,-150), 0, 0,rand()%3 + LOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,250), -30,-30,rand()%3 + LOW2);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,250),290,290,rand()%3 + LOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(600,480),240,240, rand()%3 + LOW1);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 50,50,rand()%3 + LOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(350,50), 30,30,rand()%3 + LOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,100),40,40,rand()%3 + LOW2);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(450,300), 180,180,rand()%3 + LOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(200,200),190,190,rand()%3 + LOW1);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(150,200), 140,140,rand()%3 + LOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(200,250),-90,-90,rand()%3 + LOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(550,210),170, 170,rand()%3 + LOW1);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(600,200), 40,40,rand()%3 + LOW1);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(370,300),0,0,rand()%3 + LOW1);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(100,100),0,0,rand()%3 + LOW1);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(250,360),90,90,rand()%3 + LOW1);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,100),180,180,rand()%3 + LOW1);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,500),150,150,rand()%3 + LOW2);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(550,350),90,90,rand()%3 + LOW2);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(400,340),-30,-30,rand()%3 + LOW2);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(400,100),-90,-90,rand()%3 + LOW2);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,100),-90,-90,rand()%3 + LOW1);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(500,400),0,0,rand()%3 + LOW1);
			break;
    }
}

void Fish::addPathF8(){
//    srand(time( 0 ));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 17);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 17);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 17);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 17);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 17);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 17);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 17);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 17);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 15);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 18);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 15);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 15);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 14);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 15);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 15);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 15);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 15);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 15);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 15);
			break;
    }
}

void Fish::addPathF9(){
//    srand(time( 0 ));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + LOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + LOW2);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + LOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + LOW1);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + LOW1);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + LOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + LOW2);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + LOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + LOW1);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + LOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + LOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + LOW1);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + LOW1);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + LOW1);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + LOW1);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + LOW1);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + LOW1);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + LOW2);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + LOW2);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + LOW2);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + LOW1);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + LOW1);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + LOW1);
			break;
    }
}

void Fish::addPathF10(){
//    srand(time( 0 ));

	int path = rand()%23;

	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + MEDIUM2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + MEDIUM2);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + MEDIUM2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + MEDIUM1);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + MEDIUM2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + MEDIUM1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + MEDIUM2);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + MEDIUM2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + MEDIUM1);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + MEDIUM1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + MEDIUM1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + MEDIUM1);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + MEDIUM1);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + MEDIUM1);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + MEDIUM1);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + MEDIUM1);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + MEDIUM1);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + MEDIUM2);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + MEDIUM2);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + MEDIUM2);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + MEDIUM2);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + MEDIUM1);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + MEDIUM1);
			break;
    }
}

void Fish::addPathF11(){
//    srand(time( 0 ));
	int path = rand()%20;
       
	switch(path)
    {
            //Goc phai duoi
		case 0:
			this->moveWithParabola(this,ccp(1000, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + VERYLOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(1000, -100),ccp(-250, 230),ccp(700,400), 60,-10,rand()%3 + VERYLOW2);
			break;
            //Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(1000, 550), ccp(-250,200),ccp(700,180),290,10,rand()%3 + VERYLOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
            break;
            //Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-250, -50),ccp(1000, 350),ccp(450,480), 150,180,rand()%3 + VERYLOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-250,-50), ccp(1000,250),ccp(50,300),140,180,rand()%3 + VERYLOW2);
            break;
            //Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-250, 600),ccp(1000, -100),ccp(250,400), 195,220,rand()%3 + VERYLOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-200,550),ccp(430,-200),ccp(390,450),190,250,rand()%3 + VERYLOW1);
			break;
            //Tren
		case 9:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-250, 100),ccp(450,150),-90,0,rand()%3 + VERYLOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
			break;
            //Duoi
		case 12:
            this->moveWithTwoPoint(this, ccp(250,-200), ccp(1000,600), VERYLOW1,140);
			break;
		case 13:
			this->moveWithTwoPoint(this, ccp(200,-200), ccp(350,600), VERYLOW1, 100);
            break;
		case 14:
            this->moveWithTwoPoint(this, ccp(400,-200), ccp(-200,300), VERYLOW1, 30);
			break;
            //Trai
		case 15:
			this->moveWithTwoPoint(this, ccp(-200,100),ccp(1000,550) , VERYLOW1, 160);
			break;
		case 16:
			this->moveWithTwoPoint(this, ccp(-200,400), ccp(550,-200), VERYLOW1, 230);
			break;
		case 17:
            this->moveWithTwoPoint(this, ccp(-200,400), ccp(1000,-200), VERYLOW2, 215);
			break;
        //Phai
		case 18:
            this->moveWithTwoPoint(this, ccp(1000,400), ccp(-200,-100), VERYLOW2, -20);
			break;
		case 19:
            this->moveWithTwoPoint(this, ccp(1000,100), ccp(-200,600), VERYLOW2, 20);
			break;
    }

}

void Fish::addPathF12(){
//    srand(time( 0 ));

    int path = rand()%20;
	switch(path)
    {
            //Goc phai duoi
		case 0:
			this->moveWithParabola(this,ccp(1000, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + VERYLOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(1000, -100),ccp(-250, 230),ccp(700,400), 60,-10,rand()%3 + VERYLOW2);
			break;
            //Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(1000, 550), ccp(-250,200),ccp(700,180),290,10,rand()%3 + VERYLOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
            break;
            //Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-250, -50),ccp(1000, 350),ccp(450,480), 150,180,rand()%3 + VERYLOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-250,-50), ccp(1000,250),ccp(50,300),140,180,rand()%3 + VERYLOW2);
            break;
            //Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-250, 600),ccp(1000, -100),ccp(250,400), 195,220,rand()%3 + VERYLOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-200,550),ccp(430,-200),ccp(390,450),190,250,rand()%3 + VERYLOW1);
			break;
            //Tren
		case 9:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-250, 100),ccp(450,150),-90,0,rand()%3 + VERYLOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
			break;
            //Duoi
		case 12:
            this->moveWithTwoPoint(this, ccp(250,-200), ccp(1000,600), VERYLOW1,140);
			break;
		case 13:
			this->moveWithTwoPoint(this, ccp(200,-200), ccp(350,600), VERYLOW1, 100);
            break;
		case 14:
            this->moveWithTwoPoint(this, ccp(400,-200), ccp(-200,300), VERYLOW1, 30);
			break;
            //Trai
		case 15:
			this->moveWithTwoPoint(this, ccp(-200,100),ccp(1000,550) , VERYLOW1, 160);
			break;
		case 16:
			this->moveWithTwoPoint(this, ccp(-200,400), ccp(550,-200), VERYLOW1, 230);
			break;
		case 17:
            this->moveWithTwoPoint(this, ccp(-200,400), ccp(1000,-200), VERYLOW2, 215);
			break;
            //Phai
		case 18:
            this->moveWithTwoPoint(this, ccp(1000,400), ccp(-200,-100), VERYLOW2, -20);
			break;
		case 19:
            this->moveWithTwoPoint(this, ccp(1000,100), ccp(-200,600), VERYLOW2, 20);
			break;
    }    
}

void Fish::addPathF13(){
//    srand(time( 0 ));

    int path = rand()%23;
    
	switch(path)
    {
            //Goc phai duoi
		case 0:
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + LOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + LOW2);
			break;
            //Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + LOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + LOW1);
            break;
            //Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + LOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + LOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + LOW2);
            break;
            //Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + LOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + LOW1);
			break;
            //Tren
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + LOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + LOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + LOW1);
			break;
            //Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + LOW1);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + LOW1);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + LOW1);
			break;
            //Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + LOW1);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + LOW1);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + LOW2);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + LOW2);
			break;
            //Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + LOW2);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + LOW2);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + LOW1);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + LOW1);
			break;
    }

}

void Fish::addPathF16(){
	int path = rand()%20;
       
	switch(path)
    {
            //Goc phai duoi
		case 0:
			this->moveWithParabola(this,ccp(1000, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + VERYLOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(1000, -100),ccp(-250, 230),ccp(700,400), 60,-10,rand()%3 + VERYLOW2);
			break;
            //Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(1000, 550), ccp(-250,200),ccp(700,180),290,10,rand()%3 + VERYLOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
            break;
            //Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-250, -50),ccp(1000, 350),ccp(450,480), 150,180,rand()%3 + VERYLOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-250,-50), ccp(1000,250),ccp(50,300),140,180,rand()%3 + VERYLOW2);
            break;
            //Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-250, 600),ccp(1000, -100),ccp(250,400), 195,220,rand()%3 + VERYLOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-200,550),ccp(430,-200),ccp(390,450),190,250,rand()%3 + VERYLOW1);
			break;
            //Tren
		case 9:
			this->moveWithParabola(this,ccp(-250, -50),ccp(450, 600),ccp(470,50), 180,100,rand()%3 + VERYLOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-250, 100),ccp(450,150),-90,0,rand()%3 + VERYLOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(1000, 550), ccp(400,-250), ccp(450,480),-10,-70, rand()%3 + VERYLOW1);
			break;
            //Duoi
		case 12:
            this->moveWithTwoPoint(this, ccp(250,-200), ccp(1000,600), VERYLOW1,140);
			break;
		case 13:
			this->moveWithTwoPoint(this, ccp(200,-200), ccp(350,600), VERYLOW1, 100);
            break;
		case 14:
            this->moveWithTwoPoint(this, ccp(400,-200), ccp(-200,300), VERYLOW1, 30);
			break;
            //Trai
		case 15:
			this->moveWithTwoPoint(this, ccp(-200,100),ccp(1000,550) , VERYLOW1, 160);
			break;
		case 16:
			this->moveWithTwoPoint(this, ccp(-200,400), ccp(550,-200), VERYLOW1, 230);
			break;
		case 17:
            this->moveWithTwoPoint(this, ccp(-200,400), ccp(1000,-200), VERYLOW2, 215);
			break;
        //Phai
		case 18:
            this->moveWithTwoPoint(this, ccp(1000,400), ccp(-200,-100), VERYLOW2, -20);
			break;
		case 19:
            this->moveWithTwoPoint(this, ccp(1000,100), ccp(-200,600), VERYLOW2, 20);
			break;
    }
}

void Fish::addPathF17(){
//    srand(time( 0 ));
    int path = rand()%23;
   // CCLog("PATH: %d",path);
	switch(path)
    {
            //Goc phai duoi
		case 0:
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + LOW2);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + LOW2);
			break;
            //Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + LOW2);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + LOW1);
            break;
            //Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + LOW2);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + LOW1);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + LOW2);
            break;
            //Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + LOW2);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + LOW1);
			break;
            //Tren
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + LOW1);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + LOW1);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + LOW1);
			break;
            //Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + LOW1);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + LOW1);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + LOW1);
			break;
            //Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + LOW1);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + LOW1);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + LOW2);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + LOW2);
			break;
            //Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + LOW2);
			break;
		case 20:
			this->moveWithParabola(this,ccp(870,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + LOW2);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + LOW1);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + LOW1);
			break;
    }
    

}

void Fish::addPathF19(){
//    srand(time( 0 ));

	int path = rand()%23;
	switch(path)
    {
		//Goc phai duoi
		case 0:		
			this->moveWithParabola(this,ccp(850, -100),ccp(200, 600),ccp(300,-150), -10,90,rand()%3 + 15);
            break;
		case 1:
			this->moveWithParabola(this,ccp(850, -100),ccp(-50, 230),ccp(800,450), 60,-10,rand()%3 + 15);
			break;
		//Goc phai tren
		case 2:
			this->moveWithParabola(this,ccp(850, 550), ccp(-70,200),ccp(700,180),290,10,rand()%3 + 15);
            break;
        case 3:
			this->moveWithParabola(this,ccp(850, 550), ccp(400,-70), ccp(450,480),-10,-70, rand()%3 + 11);
            break;
		//Goc trai duoi
        case 4:
			this->moveWithParabola(this,ccp(-50, -50),ccp(850, 350),ccp(450,480), 110,180,rand()%3 + 15);
            break;
        case 5:
			this->moveWithParabola(this,ccp(-50, -50),ccp(450, 500),ccp(470,50), 210,100,rand()%3 + 11);
            break;
        case 6:
			this->moveWithParabola(this,ccp(-50,-50), ccp(850,250),ccp(50,300),110,170,rand()%3 + 15);
            break;
		//Goc trai tren
		case 7:
			this->moveWithParabola(this,ccp(-50, 550),ccp(850, -100),ccp(250,400), 195,210,rand()%3 + 15);
			break;
		case 8:
			this->moveWithParabola(this,ccp(-70,550),ccp(430,-100),ccp(390,450),190,250,rand()%3 + 11);
			break;
		//Tren 
		case 9:
			this->moveWithParabola(this,ccp(0, 550),ccp(450, -100),ccp(850,500), 140,300,rand()%3 + 11);
			break;
		case 10:
			this->moveWithParabola(this,ccp(550, 550), ccp(-100, 100),ccp(450,150),-90,0,rand()%3 + 10);
			break;
		case 11:
			this->moveWithParabola(this,ccp(300,550), ccp(850,150),ccp(420,210),300, 170,rand()%3 + 11);
			break;
		//Duoi
		case 12:
			this->moveWithParabola(this,ccp(450, -100),ccp(850, 480),ccp(300,400), 40,170,rand()%3 + 10);
			break;
		case 13:
			this->moveWithParabola(this,ccp(350,-100),ccp(400,550),ccp(450,350),100,80,rand()%3 + 11);
			break;
		case 14:
			this->moveWithParabola(this,ccp(350,-100),ccp(-100,250),ccp(300,230),80,20,rand()%3 + 11);
			break;
		//Trai
		case 15:
			this->moveWithParabola(this,ccp(-150,250),ccp(440,550),ccp(350,260),180,140,rand()%3 + 11);
			break;
		case 16:
			this->moveWithParabola(this,ccp(-150,200), ccp(450,-100), ccp(280,250),180,220,rand()%3 + 11);
			break;
		case 17:
			this->moveWithParabola(this,ccp(-150,220),ccp(850,-100),ccp(100,300),180,195,rand()%3 + 15);
			break;
		case 18:
			this->moveWithParabola(this,ccp(-150,200),ccp(850,520),ccp(450,170),180,150,rand()%3 + 15);
			break;
		//Phai
		case 19:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,500),ccp(300,140),-10,30,rand()%3 + 15);
			break;
		case 20:
			this->moveWithParabola(this,ccp(850,200),ccp(-150,-100),ccp(280,250),0,-25,rand()%3 + 15);
			break;
		case 21:
			this->moveWithParabola(this,ccp(850,230),ccp(380,-100),ccp(500,250),0,-40,rand()%3 + 10);
			break;
		case 22:
			this->moveWithParabola(this,ccp(850,230),ccp(300,520),ccp(350,280),-20,50,rand()%3 + 10);
			break;
    }
}

void Fish::addPathF20(){
	int path = rand()%4;
	switch (path)
	{
		case 0:
			this->moveWithTwoPoint(this,ccp(-100,-100),ccp(900,500),MEDIUM2,0);
			break;
		case 1:
			this->moveWithTwoPoint(this,ccp(900,-100),ccp(-100,500),MEDIUM2,0);
			break;
		case 2:
			this->moveWithTwoPoint(this,ccp(-100,500),ccp(900,-100),MEDIUM2,0);
			break;
		case 3:
			this->moveWithTwoPoint(this,ccp(900,500),ccp(-100,-100),MEDIUM2,0);
			break;
		default:
			break;
	}
}

void Fish::addPathMoveAgain(){
    float time = 6 + rand()%4;
    float endX = 300, endY = 300;
    CCPoint endPoint;
    //int path = rand()%8;
    if(this->getRotationX() <0)
        this->setRotation(this->getRotationX() + 360);

	if(this->getRotationX()>= 0 && this->getRotationX()< 90){
		endPoint = ccp(-endX,endY);
	}
	else if(this->getRotationX()>= 90 && this->getRotationX()<180){
		endPoint = ccp(endX,endY);
	}
	else if(this->getRotationX()>= 180 && this->getRotationX()<270){
		endPoint = ccp(endX,-endY);
	}
	else if(this->getRotationX()>= 270 && this->getRotationX()<360){
		endPoint = ccp(-endX,-endY);
	}
    
    CCMoveBy *moveAgain = CCMoveBy::create(time,endPoint);
    CCSequence *sq = CCSequence::create(moveAgain, CCCallFunc::create(this,callfunc_selector(Fish::removeSelf)),NULL);
    this->runAction(sq);
    this->fishStopMove = false;
}

void Fish::moveWithParabola(CCSprite* mSprite,CCPoint startPoint,CCPoint endPoint,CCPoint controlPoint, float startAngle,float endAngle,float time){
    
    float sx = startPoint.x + rand()%100;
    float sy = startPoint.y + rand()%100;
    float ex = endPoint.x + rand()%50;
    float ey = endPoint.y + rand()%150;
    
    CCPoint pos = CCPointMake(sx,sy);
    mSprite->setPosition(pos);
    mSprite->setRotation(startAngle);

	ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(sx, sy);
	bezier.controlPoint_2 = ccp(controlPoint.x, controlPoint.y);
    bezier.endPosition = ccp(ex, ey);
    
    actionMove = CCBezierTo::create(time, bezier);
    actionRotate = CCRotateTo::create(time, endAngle);
    
    CCActionInterval * action = CCSpawn::create(actionMove, actionRotate, NULL);
    sqMove = CCSequence::create(action, CCCallFunc::create(this,callfunc_selector(Fish::removeSelf)),NULL);
    mSprite->runAction(sqMove);
}

void Fish::moveWithTwoPoint(CCSprite* mSprite,CCPoint startPoint,CCPoint endPoint,float time,float rotation){
    float sx = startPoint.x + rand()%100;
    float sy = startPoint.y + rand()%100;
    float ex = endPoint.x + rand()%50;
    float ey = endPoint.y + rand()%150;
    
    this->setRotation(rotation);
    CCPoint pos = CCPointMake(sx,sy);
    mSprite->setPosition(pos);
    
    actionMove2 = CCMoveTo::create(time, ccp(ex,ey));
    sqMove = CCSequence::create(actionMove2, CCCallFunc::create(this,callfunc_selector(Fish::removeSelf)),NULL);
    mSprite->runAction(sqMove);
}

//Stop fish when use freeze
void Fish::stopFishMove(){
    ItemHunt *itemThunder = ItemHunt::createItem(CCString::createWithFormat("thunder1.png"));
    itemThunder->loadEffectThunder();
    itemThunder->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(itemThunder,15);
}

//Stop fish and move it to bread
void Fish::moveToBread(){
    this->stopAction(sqMove);
    this->fishEatBread = true;
    

    //CCLog("eat bread");
}

//Resume fish after fish eated bread
void Fish::resumeFishMove(){
	CCSequence *sq = CCSequence::create(CCDelayTime::create(5.0f),CCCallFunc::create(this,callfunc_selector(Fish::setFishMoveAgain)),NULL);
	this->runAction(sq);
}

//Set path for fish after it eated bread
void Fish::setFishMoveAgain(){
    this->addPathMoveAgain();
}

void Fish::removeFishDie(CCNode* sender,void *spBG){
	CCString *tmp;
    if(this->type <= 3)
        tmp = CCString::createWithFormat("silverCoin_1.png");
	else
        tmp = CCString::createWithFormat("goldCoin_1.png");

    
    Coin *coin = Coin::createCoin(tmp);
	coin->setPosition(this->getPosition());

    if(this->type<=3)
		coin->loadCoinAnimation(2,(CCSprite*)spBG,this->point);
    else
		coin->loadCoinAnimation(1, (CCSprite*)spBG,this->point);
    
	this->removeFromParentAndCleanup(false);
	if(this->type != 17 && this->type != 13 && this->type != 16 && this->type != 20 && this->type != 19)
		this->repeatFishDie->release();
}

void Fish::removeSelf(){    
	this->removeFromParentAndCleanup(true);
	if(this->type != 17 && this->type != 13 && this->type != 16 && this->type != 20 && this->type != 19)
		this->repeatFishDie->release();
}

Fish::Fish(void){
    
}

Fish::~Fish(void){
    
}
