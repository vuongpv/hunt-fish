#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Effect: public cocos2d::CCSprite
{
    
public:
    static Effect* createEffect(CCString *frameName);
    CREATE_FUNC(Effect);
    Effect(void);
    ~Effect(void);
    void loadEffectLevelUpAnimation(CCSprite *bg);
    void loadEffectFullPower(CCSprite *bg);
    void removeSelf();
};