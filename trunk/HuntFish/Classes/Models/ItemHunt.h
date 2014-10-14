#pragma once

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class ItemHunt: public cocos2d::CCSprite
{
public:
	bool itemPressed;
	int typeItem;
    bool itemAdded;
	CCSprite *effectChoose;

	virtual bool init();
	static ItemHunt* createItem(CCString *stringFrameName);
	void addEffectChoose();
	void loadEffectItem();
	void loadEffectThunder();
	void hiddenSelf();
	void removeSelf();

	CREATE_FUNC(ItemHunt);
	ItemHunt(void);
	~ItemHunt(void);
};

