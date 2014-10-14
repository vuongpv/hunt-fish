//
//  Gun.cpp
//  HuntFish
//
//  Created by Trinh Van Duong on 10/17/13.
//
//

#include "Gun.h"
#include "LinkResources.h"

using namespace cocos2d;

bool Gun::init(){
    bool bRect = false;
    do{
        this->velocity      = 1;
        this->price         = 1;
        this->time_shot     = 10;
        this->type          = 1;
        this->point_minus   = 1;
        this->changingGun   = false;
        this->dame          = 100;
		this->shotting		= false;
        this->enemyGun      = false;
        this->numberGunUnlock = 1;
        this->levelBullet   = 1;
        this->leveVelocity  = 1;
        this->shottingLaze  = false;
        this->currentGun    = 1;
        bRect = true;
    }
    while (0);
    return  bRect;
}

Gun* Gun::createGun(CCString *stringFrameName){
    Gun* gunSprite = new Gun();
    if(gunSprite && gunSprite->initWithFile(stringFrameName->getCString())){
        gunSprite->autorelease();
        return gunSprite;
    }
    else
        return NULL;
}
//Tao dau sung
void Gun::createHeadGun(CCSprite *spBG,float rotation){
	CCString *tmp = CCString::createWithFormat("hGun%d.png",this->type);
	headGun = CCSprite::create(tmp->getCString());
	spBG->addChild(headGun,10);
    if(rotation == 0)
        headGun->setPosition(ccp(this->getPositionX(),this->getPositionY()+ 55));
	else{
        headGun->setPosition(ccp(this->getPositionX(),this->getPositionY()- 55));
        headGun->setRotation(rotation);
    }
    
    headGun->setRotation(this->getRotation());
	oldPositionHeadGun = ccp(headGun->getPositionX(),headGun->getPositionY());
}

void Gun::shot(float x, float y,float rotation){
	this->shotting = true;
	float m,n,mH,nH;
	float tmp,tmpH;	
	float angle = rotation/180*M_PI;
	float pHx,pHy;
    
    //Tinh goc cho dau sung va sung khi ban giat ve phia sau
    if(!this->enemyGun){
        if(rotation>0){
            pHx = 55*cosf(angle);
            pHy = 55 - 55*sinf(angle);
            headGun->setPosition(ccp(this->getPositionX()+pHx,100 - pHy));
            oldPositionHeadGun = ccp(headGun->getPositionX(),headGun->getPositionY());
            
            tmp = y/sinf(angle);
            tmp -= 4;
            n = tmp*sinf(angle);
            m = x - 4*cosf(angle);
            
            tmpH = oldPositionHeadGun.y/sinf(angle);
            tmpH -= 15;
            nH = tmpH*sinf(angle);
            mH = oldPositionHeadGun.x - 15*cosf(angle);
        }
        else if(rotation<0){
            pHx = 55*cosf(angle);
            pHy = 55 - 55*sinf(-angle);
            headGun->setPosition(ccp(this->getPositionX()-pHx,100 - pHy));
            oldPositionHeadGun = ccp(headGun->getPositionX(),headGun->getPositionY());
            
            tmp = y/sinf(-angle);
            tmp -= 4;
            n = tmp*sinf(-angle);
            m = x + 4*cosf(angle);
            
            tmpH = oldPositionHeadGun.y/sinf(-angle);
            tmpH -= 15;
            nH = tmpH*sinf(-angle);
            mH = oldPositionHeadGun.x + 15*cosf(angle);
        }
    }
    else{
        if(rotation < 180){
            pHx = 55*cosf(angle);
            pHy = 55 - 55*sinf(angle);
            headGun->setPosition(ccp(this->getPositionX() - pHx,380 + pHy));
            oldPositionHeadGun = ccp(headGun->getPositionX(),headGun->getPositionY());
            
            tmp = y/sinf(angle);
            tmp += 4;
            n = tmp*sinf(angle);
            m = x - 4*cosf(angle);
            
            tmpH = oldPositionHeadGun.y/sinf(angle);
            tmpH += 15;
            nH = tmpH*sinf(angle);
            mH = oldPositionHeadGun.x + 15*cosf(angle);
        }
        else if(rotation > 180){
            pHx = 55*cosf(angle);
            pHy = 55 - 55*sinf(-angle);
            headGun->setPosition(ccp(this->getPositionX() + pHx,380 + pHy));
            oldPositionHeadGun = ccp(headGun->getPositionX(),headGun->getPositionY());
            
            tmp = y/sinf(-angle);
            tmp += 4;
            n = tmp*sinf(-angle);
            m = x - 4*cosf(angle);
            
            tmpH = oldPositionHeadGun.y/sinf(-angle);
            tmpH += 15;
            nH = tmpH*sinf(-angle);
            mH = oldPositionHeadGun.x - 15*cosf(angle);
        }
    }

	CCMoveTo *move1 = CCMoveTo::create(.07f,ccp(m,n));
	CCMoveTo *move2 = CCMoveTo::create(.07f,ccp(x,y));
	CCMoveTo *moveH1 = CCMoveTo::create(.1f,ccp(mH,nH));
	CCMoveTo *moveH2 = CCMoveTo::create(.1f,oldPositionHeadGun); 

	CCSequence *sq = CCSequence::create(move1, move2, CCCallFunc::create(this,callfunc_selector(Gun::setFinishShot)),NULL);
	CCSequence *sqH = CCSequence::create(moveH1, moveH2,NULL);
    
    //Neu sung 9 tro ve thi chay hieu ung giat con khong thi cho shotting bang false luon
    if(this->type <= 9){
        this->runAction(sq);
        headGun->runAction(sqH);
    }
    else
        this->shotting = false;
}

//Set sung tro lai trang thai chua ban
void Gun::setFinishShot(){
	this->shotting = false;
}

void Gun::reloadGun(int typeGun,float positionX){
    this->currentGun = this->type;
    this->type = typeGun;
    this->changingGun = true;
    
    //Load do manh cua dan va toc do ban cua sung
    CCString *str1  = CCString::createWithFormat("lvGun%d",typeGun);
    this->levelBullet = CCUserDefault::sharedUserDefault()->getIntegerForKey(str1->getCString());
    CCString *str2  = CCString::createWithFormat("veloGun%d",typeGun);
    this->leveVelocity = CCUserDefault::sharedUserDefault()->getIntegerForKey(str2->getCString());
    CCLog("Gun: %d - Level Bullel: %d - Level Velocity: %d",this->type,this->levelBullet,this->leveVelocity);

    //choose info gun
    switch (typeGun) {
        case 1:
            this->dame = 100;
            break;
        case 2:
            this->dame = 220;
            break;
        case 3:
            this->dame = 270;
            break;
        case 4:
            this->dame = 360;
            break;
        case 5:
            this->dame = 500;
            break;
        case 6:
            this->dame = 560;
            break;
        case 7:
            this->dame = 700;
            break;
        case 8:
            this->dame = 880;
			break;
        case 9:
            this->dame = 990;
			break;
		case 10:
			break;
            
        default:
            break;
    }
    if(this->levelBullet >= 2)
        this->dame += (this->dame*this->levelBullet)/10;
    if(this->leveVelocity >= 2)
        this->velocity += (this->velocity*this->leveVelocity)/10;
    CCLog("DAME: %d",this->dame);

    
    CCMoveTo *hiddenGun = CCMoveTo::create(0.5f, ccp(positionX, -100));
    CCMoveTo *appearGun = CCMoveTo::create(0.5f, ccp(positionX, 45));
	CCMoveTo *hiddenHGun = CCMoveTo::create(0.5f,ccp(headGun->getPositionX(),headGun->getPositionY()-145));
	CCMoveTo *appearHGun = CCMoveTo::create(0.5f,oldPositionHeadGun);
    
    CCSequence *sq = CCSequence::create(hiddenGun, appearGun, CCCallFunc::create(this,callfunc_selector(Gun::setFinishChangeGun)),NULL);
	CCSequence *sqH = CCSequence::create(hiddenHGun,appearHGun,NULL);
	
	this->runAction(CCSequence::create(CCDelayTime::create(0.55f),CCCallFunc::create(this,callfunc_selector(Gun::reloadDisplayGun)),NULL));
	this->runAction(sq);

	if(this->type<= 9){
		this->headGun->setVisible(true);
		this->headGun->runAction(sqH);
	}
	else 
		this->headGun->setVisible(false);
}

//Reload thong so cu sung sau khi nang cap
void Gun::reloadInfoGun(){
    //Load do manh cua dan va toc do ban cua sung
    CCString *str1  = CCString::createWithFormat("lvGun%d",this->type);
    this->levelBullet = CCUserDefault::sharedUserDefault()->getIntegerForKey(str1->getCString());
    CCString *str2  = CCString::createWithFormat("veloGun%d",this->type);
    this->leveVelocity = CCUserDefault::sharedUserDefault()->getIntegerForKey(str2->getCString());
    CCLog("Gun: %d - Level Bullel: %d - Level Velocity: %d",this->type,this->levelBullet,this->leveVelocity);
    
    //choose info gun
    switch (this->type) {
        case 1:
            this->dame = 100;
            break;
        case 2:
            this->dame = 220;
            break;
        case 3:
            this->dame = 270;
            break;
        case 4:
            this->dame = 360;
            break;
        case 5:
            this->dame = 500;
            break;
        case 6:
            this->dame = 560;
            break;
        case 7:
            this->dame = 700;
            break;
        case 8:
            this->dame = 880;
			break;
        case 9:
            this->dame = 990;
			break;
		case 10:
			break;
            
        default:
            break;
    }
    if(this->levelBullet >= 2)
        this->dame += (this->dame*this->levelBullet)/10;
    if(this->leveVelocity >= 2)
        this->velocity += (this->velocity*this->leveVelocity)/10;
    CCLog("DAME: %d",this->dame);
}

//Set trang thai dang doi sung
void Gun::setFinishChangeGun(){
    this->changingGun = false;
}

//Load sung tro lai binh thuong sau khi ban dan dac biet
void Gun::reloadNormalGun(CCSprite *spBg){
    CCSequence* sq = CCSequence::create(CCDelayTime::create(4.0f), CCCallFuncND::create(this, callfuncND_selector(Gun::callReloadNormalGun),(void*)spBg),NULL);
    
    this->runAction(sq);
}

void Gun::callReloadNormalGun(CCNode* sender, void *spBg){
    CCSprite *bg = (CCSprite*)spBg;
    this->shottingLaze = false;
    this->reloadGun(this->currentGun, bg->getContentSize().width/2);
}

void Gun::reloadDisplayGun(){
    CCString *tmp = CCString::createWithFormat("gun%d.png",this->type);
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(tmp->getCString());
    CCSize textureSize = texture->getContentSize();
    CCRect textureRect = CCRectMake(0, 0, textureSize.width, textureSize.height);
    CCSpriteFrame *spriteFrame = CCSpriteFrame::createWithTexture(texture,textureRect);
    this->setDisplayFrame(spriteFrame);    

	CCString *tmpH;
	CCTexture2D *textureH;
	CCSize textureSizeH;
	CCRect textureRectH;
	CCSpriteFrame *spriteFrameH;
	if(this->type <= 9){
		tmpH = CCString::createWithFormat("hGun%d.png",this->type);    
		textureH = CCTextureCache::sharedTextureCache()->addImage(tmpH->getCString());
		textureSizeH = textureH->getContentSize();
		textureRectH = CCRectMake(0, 0, textureSizeH.width, textureSizeH.height);
		spriteFrameH = CCSpriteFrame::createWithTexture(textureH,textureRectH);
		headGun->setDisplayFrame(spriteFrameH); 
	}
		
}

Gun::Gun(void){
    
}

Gun::~Gun(void){
    
}
