#include "AppDelegate.h"
#include "ViewMenu.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
//    // initialize director
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
//    // Set the design resolution
////    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
//    pDirector->setOpenGLView(pEGLView);
//    pDirector->getOpenGLView()->setDesignResolutionSize(480, 320, kResolutionExactFit);
//
//    // turn on display FPS
//    pDirector->setDisplayStats(false);
//
//    // set FPS. the default value is 1.0/60 if you don't call this
//    pDirector->setAnimationInterval(1.0 / 60);
//
//    // create a scene. it's an autorelease object
//    CCScene *pScene = ViewMenu::scene();
//
////    CCScene *pScene = HelloWorld::scene();
//    
//    // run
//    pDirector->runWithScene(pScene);
//
//    return true;
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = ViewMenu::scene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
