#include "AppDelegate.h"
#include <vector>
#include <string>

#include "AppMacros.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCObject/GCObjGroupDefault.h"
#include "MenuScene.h"


USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    // initialize director
    auto pDirector = Director::getInstance();
    auto glview = pDirector->getOpenGLView();
    
	if(!glview) 
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("GCTemplate", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("GCTemplate");
#endif
		pDirector->setOpenGLView(glview);
    }

    // Set the design resolution
	glview->setDesignResolutionSize( designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER );

	Size frameSize = glview->getFrameSize();
    	
    // turn on display FPS
	pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0f / 60.0f);

	//////////////////////////////////////////////////////////////////////////
	// GamerCamp Edit


		// create the initial GameScene
		Scene* pScene = CMenuLayer::scene();

	// GamerCamp Edit
	//////////////////////////////////////////////////////////////////////////

	// run
    pDirector->runWithScene( pScene );

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
