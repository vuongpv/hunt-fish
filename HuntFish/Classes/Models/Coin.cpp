//
//  Coin.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/24/13.
//
//

#include "Coin.h"
Coin* Coin::createCoin(CCString *frameName){
	Coin* coinSprite = new Coin();
    if(coinSprite && coinSprite->initWithFile(frameName->getCString())){
        coinSprite->autorelease();
        return coinSprite;
    }
    else
        return NULL;
}

void Coin::loadCoinAnimation(int type, CCSprite *bg, int money){
    CCSize textureSize;
    CCRect textureRect;
    CCSpriteFrame *spriteFrame;
    CCArray *animationFrames;
    CCAnimate *animate;
    CCTexture2D *texture;
    animationFrames = CCArray::createWithCapacity(3);
    
    for(int i = 1;i<=10;i++){
        CCString *stringFile;
		if(type == 1)
			stringFile = CCString::createWithFormat("goldCoin_%i.png",i);
		else if(type == 2)
			stringFile = CCString::createWithFormat("silverCoin_%i.png",i);

        texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
        textureSize = texture->getContentSize();
        textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
        spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
        animationFrames->addObject(spriteFrame);
    }
    
	CCAnimation *coinAnimation = CCAnimation::createWithSpriteFrames(animationFrames,0.05f);
	CCMoveTo *moveCoin = CCMoveTo::create(2.0f,ccp(220,0));
	CCSequence *sq = CCSequence::create(moveCoin,CCCallFunc::create(this,callfunc_selector(Coin::removeSelf)),NULL);
	animate  = CCAnimate::create(coinAnimation);
	bg->addChild(this,3);

    if(type == 1)
        this->setScale(0.7f);
	else
        this->setScale(0.5f);

	CCString *stringMoney = CCString::createWithFormat("+%d",money);
	this->labelCountGold = CCLabelBMFont::create(stringMoney->getCString(),"font-sotiencong.fnt");
	this->labelCountGold->setScale(0.7);
	this->labelCountGold->setPosition(this->getPosition());
    bg->addChild(this->labelCountGold,3);
	CCMoveTo *moveLabel = CCMoveTo::create(1.5f,ccp(this->labelCountGold->getPositionX() + 10, this->labelCountGold->getPositionY() + 25));
	this->labelCountGold->runAction(moveLabel);

    this->repeatCoinMove   = CCRepeatForever::create(animate);
	this->runAction(repeatCoinMove);
	this->runAction(sq);
}


void Coin::removeSelf(){
	this->stopAllActions();
	this->labelCountGold->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
}

Coin::Coin(void){
}

Coin::~Coin(void){
}