//
//  Fish.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//
#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#define FAST1   7
#define FAST2   11
#define MEDIUM1  13
#define MEDIUM2 17
#define LOW1    15
#define LOW2    20
#define VERYLOW1 25
#define VERYLOW2 30

#define TIMEANIMATION1 0.12f
#define TIMEANIMATION2 0.2f
#define TIMEANIMATION3 0.3f

using namespace cocos2d;

class Fish: public cocos2d::CCSprite
{
    
public:
    static Fish* createFish(CCString *frameName);
    virtual bool init();
    CREATE_FUNC(Fish);
    Fish(void);
    ~Fish(void);
    void loadFishAnimation();
    void loadFishDie();
    void runFishDie(CCSprite *spBG);

    void addPath();
    void addPathF1();
    void addPathF2();
    void addPathF3();
    void addPathF4();
	void addPathF5();
	void addPathF6();
	void addPathF7();
	void addPathF8();
	void addPathF9();
	void addPathF10();
    void addPathF11();
	void addPathF12();
	void addPathF13();
	void addPathF16();
    void addPathF17();
	void addPathF19();
	void addPathF20();
    void addPathMoveAgain();

    void moveWithParabola(CCSprite* mSprite,CCPoint startPoint,CCPoint endPoint,CCPoint controlPoint,float startAngle,float endAngle,float time);
    void moveWithTwoPoint(CCSprite* mSprite,CCPoint startPoint,CCPoint endPoint,float time,float rotation);
    
    void moveToBread();
    void stopFishMove();
	void resumeFishMove();
	void setFishMoveAgain();
    void removeSelf();
	void removeFishDie(CCNode* sender,void *spBG);
    
    ///////////////
    CCRepeatForever *repeatFishMove;
	CCRepeatForever *repeatFishDie;
	CCAnimation *fishDie;
    CCBezierTo *actionMove;
    CCRotateTo *actionRotate;
    CCMoveTo *actionMove2;
	CCSequence *sqMove;
    
    int blood, type, point, level,experience;
    int tagOfWebCatchedFish;
    float velocity;
    bool fishDied, fishStopMove, fishEatBread;
};