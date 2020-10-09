//#include <string.h>
//
//#include "GamerCamp/GameSpecific/Timer/GCObjTimerBar.h"
//
//#include "GamerCamp/GCObject/GCObjectManager.h"
//#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
//#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
//#include "GamerCamp/Core/GCTypes.h"
//#include "GamerCamp/GCObject/GCObject.h"
//#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
//#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
//
//
//using namespace cocos2d;
//
//
//CGCObjTimerBar::CGCObjTimerBar()
//{
//
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Point origin = Director::getInstance()->getVisibleOrigin();
//
//
//	const char* timerBarSprite = "TexturePacker/Sprites/Coin/Coin.plist";
//	{
//		m_pcGCOTimerBar = new CGCObjSpritePhysics();
//
//		
//			m_pcGCOTimerBar->CreateSprite(timerBarSprite);
//			//m_pcGCOTimerBar->SetSpritePosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//			m_pcGCOTimerBar->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//			m_pcGCOTimerBar->SetParent(IGCGameLayer::ActiveInstance());
//		
//	}
//}
//
//
//CGCObjTimerBar::~CGCObjTimerBar()
//{
//	
//}
//
