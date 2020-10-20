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
	:CGCObjSprite(GetGCTypeIDOf(CGCObjTimer))
	,m_iTotalTimerDuration		 (		100			)   //Max value for the timer
    ,m_iTimerDecreaseValue		 (		 1			)	// The Amount decremented each time
	,m_iTimerIncreaseValue       (       20          )
    ,m_fMaxTimeBuffer			 (		100.0f		)	// Max value timer resets too
	,m_fCurrentTimeBuffer        ( m_fMaxTimeBuffer )	// higher the value  slower the timer is
	,m_fScaleX					 (     2.0f			)
	,m_fCurrentXScale			 (    m_fScaleX		)
	,m_fScaleDecreaseX			 (		40.0f		)
	,m_fScaleDecreaseY			 (		0.1f		)
	
    
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

	//getTimerText()->enableGlow(Color4B::RED); // Enable outline overrides Glow
 	
	getTimerText()->enableOutline(Color4B::BLACK, 1);
	
	getTimerText()->setPosition(Vec2(visibleSize.width / 2 - 420 , visibleSize.height +  10));

	getTimerText()->setString("Air " + std::to_string( getCurrentTime()) + "%"  );

	/////////////////////////////////////////////////////////////////////////////////////////////////////


	const char* pszTimerBarSprite = "TexturePacker/Sprites/TimerBar/WhiteSquare.plist";
	{
		CreateSprite(pszTimerBarSprite);
		SetResetPosition(Vec2(500, 695));
		SetParent(IGCGameLayer::ActiveInstance());
		SetScale(m_fScaleX, 0.1f);

	}

}

 //IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTimer, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);

 void CGCObjTimer::DecreaseTimer()
 {

 	if(getCurrentTimeBuffer()> 0)
 	{
		setCurrentTimeBuffer(getCurrentTimeBuffer()-1);
 	}
    else if (getCurrentTimeBuffer() <= 0)
	{

		if (getCurrentTime() >= 0)
		{
			setCurrentTime(getCurrentTime() - getTimerDecreaseValue());

			
			SetScale(getCurrentTime() / m_fScaleDecreaseX, m_fScaleDecreaseY);

			getTimerText()->setString("Air "+ std::to_string(getCurrentTime()) + "%" );
		}
		else
		{
			setCurrentTime(0.0f);
		}
		
		setCurrentTimeBuffer(m_fMaxTimeBuffer);
	}
 }

//void CGCObjTimer::VOnResourceAcquire(void)
//{
// 	CGCObjSprite::VOnResourceAcquire();
//	
//	
//}


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
