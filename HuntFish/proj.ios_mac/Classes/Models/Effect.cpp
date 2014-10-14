//
//  Coin.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/24/13.
//
//

#include "Effect.h"
Effect* Effect::createEffect(CCString *frameName){
	Effect* EffectSprite = new Effect();
    if(EffectSprite && EffectSprite->initWithFile(frameName->getCString())){
        EffectSprite->autorelease();
        return EffectSprite;
    }
    else
        return NULL;
}

void Effect::loadEffectLevelUpAnimation(CCSprite *bg){
	bg->addChild(this,15);
    CCPoint pos = CCPointMake(bg->getContentSize().width/2, bg->getContentSize().height/2);
    this->setPosition(pos);
    CCMoveTo *moveEffect = CCMoveTo::create(3.0f,ccp(this->getPositionX() + 10,this->getPositionY() + 30));
	CCSequence *sq = CCSequence::create(moveEffect,CCCallFunc::create(this,callfunc_selector(Effect::removeSelf)),NULL);
	this->runAction(sq);
}


void Effect::loadEffectFullPower(CCSprite *bg){
    bg->addChild(this,15);
    CCPoint pos = CCPointMake(bg->getContentSize().width/2, bg->getContentSize().height/2);
    this->setPosition(pos);
    CCMoveTo *moveEffect = CCMoveTo::create(3.0f,ccp(this->getPositionX() + 10,this->getPositionY() + 30));
	CCSequence *sq = CCSequence::create(moveEffect,CCCallFunc::create(this,callfunc_selector(Effect::removeSelf)),NULL);
	this->runAction(sq);
}

void Effect::removeSelf(){
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}

Effect::Effect(void){
}

Effect::~Effect(void){
}