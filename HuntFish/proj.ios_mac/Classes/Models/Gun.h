//
//  Gun.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//
#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;

class Gun: public cocos2d::CCSprite
{
    
public:
    int velocity, type, price, point_minus, time_shot,dame, numberGunUnlock;
    int levelBullet,leveVelocity;//bac suc manh va toc do cua sung khi duoc nang cap
    int currentGun;//Sung hien tai dang dung, de reload sau khi dung sung laze
    bool changingGun,shotting, shottingLaze;
    bool enemyGun;
	CCPoint oldPositionHeadGun;
	CCSprite *headGun;
	CCAnimate *animateShot;
	CCArray *gunsInfoArray;
    
    static Gun* createGun(CCString *stringFrameName);
    virtual bool init();
    void shot(float x, float y,float rotation);
    void reloadGun(int typeGun, float positionX);
    void reloadDisplayGun();
    void setFinishShot();
	void setFinishChangeGun();
    void reloadInfoGun();
    void createHeadGun(CCSprite *spBG,float rotation);
    void reloadNormalGun(CCSprite *spBg);
    void callReloadNormalGun(CCNode* sender, void *spBg);
    CREATE_FUNC(Gun);
    Gun(void);
    ~Gun(void);
};