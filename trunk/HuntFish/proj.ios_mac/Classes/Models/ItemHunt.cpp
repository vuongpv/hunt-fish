#include "ItemHunt.h"
#include "LinkResources.h"

using namespace cocos2d;

bool ItemHunt:: init(){
	bool bRect = false;
    do{
		this->typeItem = 0;
		this->itemPressed = false;
        this->itemAdded = false;
		this->addEffectChoose();
		bRect = true;
    }
    while (0);
    return  bRect;
}

void ItemHunt::addEffectChoose(){
	this->effectChoose = CCSprite::create(ITEMSCOPE);
	this->addChild(effectChoose,1);
	this->effectChoose->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
	this->effectChoose->setVisible(true);
}

void ItemHunt::loadEffectItem(){
	CCSize textureSize;
    CCRect textureRect;
    CCSpriteFrame *spriteFrame;
    CCArray *animationFrames;
    CCTexture2D *texture;
	CCAnimate *itemAnimate;

	if(this->typeItem == 1){
		//Bomb
		animationFrames = CCArray::createWithCapacity(6);

		for(int i = 1;i<=6;i++){
        CCString *stringFile = CCString::createWithFormat("bom%i.png",i);
        texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
        textureSize = texture->getContentSize();
        textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
        spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
        animationFrames->addObject(spriteFrame);
		
		}
		CCAnimation *bomb = CCAnimation::createWithSpriteFrames(animationFrames,0.1f);
		itemAnimate  = CCAnimate::create(bomb);
		CCSequence *sq = CCSequence::create(itemAnimate,CCCallFunc::create(this,callfunc_selector(ItemHunt::removeSelf)),NULL);
		this->runAction(sq);
    }
	else if(this->typeItem == 2){
		//Freeze
		animationFrames = CCArray::createWithCapacity(5);

		for(int i = 1;i<=5;i++){
			CCString *stringFile = CCString::createWithFormat("set-no-%i.png",i);
			texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
			textureSize = texture->getContentSize();
			textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
			spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
			animationFrames->addObject(spriteFrame);
		}

		CCAnimation *freeze = CCAnimation::createWithSpriteFrames(animationFrames,0.1f);
		itemAnimate  = CCAnimate::create(freeze);

		CCSequence *sq = CCSequence::create(itemAnimate,CCCallFunc::create(this,callfunc_selector(ItemHunt::removeSelf)),NULL);
		this->runAction(sq);
	}
	else if(this->typeItem == 3){
		animationFrames = CCArray::createWithCapacity(4);

		for(int i = 1;i<=4;i++){
			CCString *stringFile = CCString::createWithFormat("animation-item-banhmi-%i.png",i);
			texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
			textureSize = texture->getContentSize();
			textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
			spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
			animationFrames->addObject(spriteFrame);
		}

		CCAnimation *bread = CCAnimation::createWithSpriteFrames(animationFrames,0.1f);
		itemAnimate  = CCAnimate::create(bread);
		CCRepeatForever *itemAnimateRepreat = CCRepeatForever::create(itemAnimate);

		this->runAction(itemAnimateRepreat);
		CCSequence *sq = CCSequence::create(CCDelayTime::create(8.0f),CCCallFunc::create(this,callfunc_selector(ItemHunt::removeSelf)),NULL);
		this->runAction(sq);
	}
}

void ItemHunt::loadEffectThunder(){
	this->setScale(0.8f);
	CCSize textureSize;
    CCRect textureRect;
    CCSpriteFrame *spriteFrame;
    CCArray *animationFrames;
    CCTexture2D *texture;
	CCAnimate *itemAnimate;

	animationFrames = CCArray::createWithCapacity(3);
	for(int i = 1;i<=3;i++){
		CCString *stringFile = CCString::createWithFormat("thunder%i.png",i);
        texture = CCTextureCache::sharedTextureCache()->addImage(stringFile->getCString());
        textureSize = texture->getContentSize();
        textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
        spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
        animationFrames->addObject(spriteFrame);
	}
	
	CCAnimation *bomb = CCAnimation::createWithSpriteFrames(animationFrames,0.1f);
	itemAnimate  = CCAnimate::create(bomb);
	CCRepeatForever *itemAnimateRepreat = CCRepeatForever::create(itemAnimate);

	this->runAction(itemAnimateRepreat);
	CCSequence *sq = CCSequence::create(CCDelayTime::create(10.0f),CCCallFunc::create(this,callfunc_selector(ItemHunt::removeSelf)),NULL);
	this->runAction(sq);
}

void ItemHunt::hiddenSelf(){
	this->setPosition(ccp(-300,-300));
}

void ItemHunt::removeSelf(){
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);	
}

ItemHunt* ItemHunt::createItem(CCString *stringFrameName){
	 ItemHunt* itemSprite = new ItemHunt();
    if(itemSprite && itemSprite->initWithFile(stringFrameName->getCString())){
        itemSprite->autorelease();
        return itemSprite;
    }
    else
        return NULL;
}

ItemHunt::ItemHunt(void)
{
}


ItemHunt::~ItemHunt(void)
{
}
