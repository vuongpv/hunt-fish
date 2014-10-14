//
//  Bullet.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "Web.h"
#include "LinkResources.h"

bool Web::init(){
    bool bRect = false;
    do{
        this->velocity   = 0;
        this->type       = 0;
        this->isCatching = false;
        bRect = true;
    }
    while (0);
    return  bRect;
}

Web* Web::createWeb(CCString *stringFrameName){
    Web* WebSprite = new Web();
    if(WebSprite && WebSprite->initWithFile(stringFrameName->getCString())){
        WebSprite->autorelease();
        return WebSprite;
    }
    else
        return NULL;
}

void Web::webMove(float x, float y, CCSprite* bgSprite){
    CCMoveTo *move = CCMoveTo::create(1.0f, ccp(x,y));
	CCSequence* sq = CCSequence::create(move, CCCallFuncND::create(this, callfuncND_selector(Web::showNet),(void*)bgSprite),NULL);
    
    this->runAction(sq);
    bgSprite->addChild(this,9);
}

void Web::showNet(CCNode* sender,void *bgSprite){
	CCSprite *bg = (CCSprite*)bgSprite;
    bg->removeChild(this, false);
    this->isCatching = true;
    
    CCString *tmp = CCString::createWithFormat("web%d.png",this->type);
    if(this->type<=5)
		tmp = CCString::createWithFormat("web%d.png",this->type);
	else
		tmp = CCString::createWithFormat("web5.png");

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(tmp->getCString());
    CCSize textureSize = texture->getContentSize();
    CCRect textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
    CCSpriteFrame *spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
    this->setDisplayFrame(spriteFrame);
    
    CCScaleTo* scale0 = CCScaleTo::create(0.1f,1.1f);
    CCScaleTo* scale1 = CCScaleTo::create(0.1f,1.0f);
    
    CCSequence* netSequence = CCSequence::create(scale0, scale1, scale0, scale1,CCCallFuncND::create(this, callfuncND_selector(Web::afterShowNet),(void*)bg),NULL);
    
    this->runAction(netSequence);
    bg->addChild(this,9);
}

void Web::afterShowNet(CCNode* sender, void *sheet)
{
	CCSprite *gunsSheet = (CCSprite*)sheet;
    this->isCatching = false;
    gunsSheet->removeChild(this,false);
}

//Dan laze
void Web::specialBullet(){
    CCSequence* sq = CCSequence::create(CCDelayTime::create(4.0f),CCCallFunc::create(this,callfunc_selector(Web::removeBullet)),NULL);
    this->runAction(sq);
}

//Remove bullet from parent
void Web::removeBullet(){
    this->isCatching = false;
    this->removeFromParent();
}

Web::Web(void){
    
}

Web::~Web(void){
    
}
