//
//  DiaryView.h
//  HuntFish
//
//  Created by Trinh Van Duong on 11/22/13.
//
//

#define __HuntFish__DiaryView__

#include "cocos-ext.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace extension;

class DiaryView: public cocos2d::CCSprite
{
public:
    static DiaryView* createDiary(CCString *nameFile);
    virtual bool init();
    CREATE_FUNC(DiaryView);
    DiaryView(void);
    ~DiaryView(void);
    
    void exitDiary(CCObject *pSender);
    void appearDiary(int positionY);
    void hiddenDiary(int positionY);
    void setDiaryUnenalbe();
    void nextPage(CCObject *pSender);
    void backPage(CCObject *pSender);
    void shareDiary(CCObject *pSender);
    void initLayerFish();
    void loadNumberFish();
    
    CCMenuItem *buttonExitDiary, *buttonNext, *buttonBack, *buttonShare;
    CCMenu *menuButton;
    CCLayer *layerFish1, *layerFish2;
    CCLabelBMFont *labelNumberFish[16];
    int numFish[16];
    bool isEnable;
};

