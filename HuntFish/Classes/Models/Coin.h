//
//  Coin.h
//  HuntFish
//
//  Created by Trinh Van Duong on 10/24/13.
//
//

#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Coin: public cocos2d::CCSprite
{
    
public:
    static Coin* createCoin(CCString *frameName);
    CREATE_FUNC(Coin);
    Coin(void);
    ~Coin(void);
    void loadCoinAnimation(int type,CCSprite *bg, int money);
    void removeSelf();
    
    ///////////////
	CCLabelBMFont *labelCountGold;
    CCRepeatForever *repeatCoinMove;
    CCBezierTo *actionMove;
};