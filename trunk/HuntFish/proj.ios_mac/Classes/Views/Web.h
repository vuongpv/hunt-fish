//
//  Bullet.h
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

class Web: public cocos2d::CCSprite
{
    
public:
    
    static Web* createWeb(CCString *stringFrameName);
    virtual bool init();
    
    CREATE_FUNC(Web);
    
    Web(void);
    ~Web(void);
    
    void webMove(float x,float y,CCSprite* bgSprite);
    void showNet(CCNode* sender, void *bgSprite);
    void afterShowNet(CCNode* sender, void *bgSprite);
	void specialBullet();
    void removeBullet();
    
    int velocity, type;
    bool isCatching;
    
};