#include <string.h>

#include "GamerCamp/GameSpecific/Timer/GCObjTimer.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// using

using namespace cocos2d;

///////////////////////////////////////////////////////////////////////////////////////////////////////
 CGCObjTimer::CGCObjTimer()
	:m_fTotalTimerDuration                ( 100 )		//Max value for the timer
    ,m_fTimerDecreaseValue                (  1  )		// The Amount decremented each time
    ,m_fTimeBuffer                        ( 100.0f )	// higher the value  slower the timer is 
    
{
 	//Set Current time to the max Time
	setCurrentTime(getTotalTimerDuration());

 	//Get Screen size & Width
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/// /////////////////////////////////////////////////////////////////////////////////////////////////
	/// Timer Text Label
	setTimerText(Label::createWithTTF(" ", "fonts/arial.ttf", 35.0f));

	getTimerText()->setColor(Color3B::WHITE);

	//getTimerText()->enableGlow(Color4B::RED);
 	
	getTimerText()->enableOutline(Color4B::BLACK, 1);
	
	getTimerText()->setPosition(Vec2(visibleSize.width / 2 - 450 , visibleSize.height +  10));

	getTimerText()->setString(std::to_string(getCurrentTime()) + "%"  );

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	//const char* timerBarSprite = "TexturePacker/Sprites/Coin/Coin.plist";
	//{
	//	m_pcGCOTimerBar = new CGCObjSprite();

	//	if(nullptr != m_pcGCOTimerBar)
	//	{
	//		m_pcGCOTimerBar->CreateSprite(timerBarSprite);
	//		//m_pcGCOTimerBar->SetSpritePosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//		m_pcGCOTimerBar->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//		m_pcGCOTimerBar->SetParent(IGCGameLayer::ActiveInstance());
	//	}
	//}
}

 void CGCObjTimer::DecreaseTimer()
 {

 	if(getTimeBuffer()> 0)
 	{
		setTimeBuffer(getTimeBuffer()-1);
 	}
    else if (getTimeBuffer() <= 0)
	{

		if (getCurrentTime() >= 0)
		{
			setCurrentTime(getCurrentTime() - getTimerDecreaseValue());

			getTimerText()->setString(std::to_string(getCurrentTime()) + "%" );
		}
		else
		{
			setCurrentTime(0.0f);
		}
		
		setTimeBuffer(60);
	}
 }


void CGCObjTimer::ResetTimer()
{
	setCurrentTime(getTotalTimerDuration());
}

 void CGCObjTimer::Update()
{
	 DecreaseTimer();
}

 
CGCObjTimer::~CGCObjTimer()
 {
	 
 }
