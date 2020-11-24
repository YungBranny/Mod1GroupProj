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
	,m_fTotalTimerDuration		 (		100.0f		)   // Max value for the timer
    ,m_fTimerDecreaseValue		 (		0.0015f		)	// The Amount decremented each time
	,m_iTimerIncreaseValue       (       20         )	// The Amount the Timer increases when the Timer pickup is picked up
    ,m_fMaxTimeBuffer			 (		100.0f		)	// Max value timer resets too
	,m_fCurrentTimeBuffer        ( m_fMaxTimeBuffer )	// higher the value  slower the timer is
	,m_fScaleX					 (     2.0f			)	// Scale X for Timer bar
	,m_fScaleY					 (		0.1f		)	// Scale Y for Timer bar
	,m_fCurrentXScale			 (    m_fScaleX		)	// Current scale
	,m_fScaleDecreaseX			 (		40.0f		)	// Scale Decrease X
	,m_fScaleDecreaseY			 (		0.1f		)	// Scale Decrease Y
	//,m_iTimerTextOutlineSize	 (		1	     	)	// Text outline width
	//,m_fTimerTextFontSize		 (		50.0f		)	// Text font size
	,m_fTimerBarStartPosX		 (		1000		)	// Timer bar start pos X
	,m_fTimerBarStartPosY		 (		1000		)	// Timer bar start pos Y
	,m_iTimerBarHeightX			 (		425			)	// Timer bar Height on Screen
	,m_iTimerBarHeightY			 (		1000		)	// Timer bar Height on Screen
	,m_iTimerBufferDecrease		 (		1			)	// Timer buffer decrease value
	,m_fTimerBarSpeedDecrease	 (		1.0f		)
	,m_fTimerBarMidPoint		 (		0.5f		)
    
{	/////////////////////////////////////////////////////////////////////////////////////////////////
 	
 	//Set Current time to the max Time
	setCurrentTime(getTotalTimerDuration());

	////////////////////////////////////////////////////////////////////////////////////////////////////
 	
 	//Get Screen size & Width
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Timer Text Label
	//setTimerText(Label::createWithTTF(" ", "fonts/SaltyOcean.ttf", m_fTimerTextFontSize));

	//getTimerText()->setColor(Color3B::WHITE);

	//getTimerText()->enableGlow(Color4B::RED); // Enable outline overrides Glow
 	
	//getTimerText()->enableOutline(Color4B::BLACK, m_iTimerTextOutlineSize);
	//
	//getTimerText()->setPosition(Vec2(  m_iTimerBarHeightX ,   m_iTimerBarHeightY));

	//getTimerText()->setString("Power " + std::to_string( getCurrentTime()) + "%"  );

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	//Getting texture file path for timer bar sprite
	const char* pszTimerBarSprite = "Loose/UI_TimerBar.plist";
	{
		CreateSprite(pszTimerBarSprite);
		/*SetResetPosition(Vec2(m_fTimerBarStartPosX, m_fTimerBarStartPosY));
		SetParent(IGCGameLayer::ActiveInstance());
		SetScale(m_fScaleX, m_fScaleY);*/
		
	}

 	//"TexturePacker/Sprites/TimerBar/UI_TimerBar.plist";
 	//m_TimerBar = ProgressTimer::create(m_TimerBarSprite);
 	//m_TimerBar->setType(ProgressTimer::Type::BAR);

	m_UI_TimerBorder = Sprite::create("Loose/UI_Bar.png");

	getTimerBarUI()->setPosition(Vec2(m_fTimerBarStartPosX, m_fTimerBarStartPosY + 17.5));

 	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
 	
	m_TimerBarSprite = Sprite::create("Loose/UI_TimerBar.png"); // Sprite used for the Timer Bar

	setTimerBar(ProgressTimer::create(m_TimerBarSprite));// Makes the sprite into a cocos2d::ProgressTimer

 	getTimerBar()->setPosition(Vec2(m_fTimerBarStartPosX, m_fTimerBarStartPosY)); //Position for the Timer bar
 	
 	getTimerBar()->setType(ProgressTimer::Type::BAR); // Makes the Timer bar a bar, other option is radial
 	
	getTimerBar()->setBarChangeRate(Vec2(m_fTimerBarSpeedDecrease, 0.0f)); //the amount the timer bar decreases 
 	
	getTimerBar()->setPercentage(100.0f); // original percentage of the timer bar
 	
	getTimerBar()->setMidpoint(Vec2(0.0f, m_fTimerBarMidPoint)); // choose which side the bar counts down from
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
}

 //test
 //IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTimer, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);

 void CGCObjTimer::DecreaseTimer(f32 fTimeStep)
 {


	 if (getCurrentTime() >= 0)
	 {


		 setCurrentTime(getCurrentTime() - getTimerDecreaseValue()); //Starting at 100% this counts down in 1's to 0

		 //SetScale(getCurrentTime() / m_fScaleDecreaseX, m_fScaleDecreaseY);// Scale for the timer bar being decremented

		 //getTimerText()->setString("Power "+ std::to_string(getCurrentTime()) + "%" ); //Setting Current time to text to be shown on the screen
	 }
	 else
	 {
		 setCurrentTime(0.0f); //sets time to 0 when at 0 to prevent going into negative values
	 }


 	

 //	if(getCurrentTimeBuffer()> 0)
 //	{
	//	setCurrentTimeBuffer(getCurrentTimeBuffer()-m_iTimerBufferDecrease);
 //		//Decreases the timer buffer by 1 each update
 //	}
 //   else if (getCurrentTimeBuffer() <= 0)
	//{

	//	if (getCurrentTime() >= 0)
	//	{

	//		
	//		setCurrentTime(getCurrentTime() - getTimerDecreaseValue()); //Starting at 100% this counts down in 1's to 0

	//		//SetScale(getCurrentTime() / m_fScaleDecreaseX, m_fScaleDecreaseY);// Scale for the timer bar being decremented

	//		//getTimerText()->setString("Power "+ std::to_string(getCurrentTime()) + "%" ); //Setting Current time to text to be shown on the screen
	//	}
	//	else
	//	{
	//		setCurrentTime(0.0f); //sets time to 0 when at 0 to prevent going into negative values
	//	}
	//	
	//	setCurrentTimeBuffer(m_fMaxTimeBuffer);// sets timer buffer back to 100
	//}
 }

void CGCObjTimer::ClampTimer()
{
	if(getCurrentTime()> getMaxTimeBuffer())
	{
		setCurrentTime(getMaxTimeBuffer());
		//Timer can't go over 100
	}
}

//void CGCObjTimer::VOnResourceAcquire(void)
//{
// 	CGCObjSprite::VOnResourceAcquire();
//	
//	
//}

void CGCObjTimer::VOnReset()
 {
	setCurrentTime(getTotalTimerDuration());
 }


void CGCObjTimer::ResetTimer()
{
	setCurrentTime(getTotalTimerDuration());
 	//on reset set timer back to max
}

 void CGCObjTimer::Update( f32 fTimeStep)
{
	 
 	
	 m_fCurrentTime -= fTimeStep;
 	
 	 DecreaseTimer(fTimeStep);
 	
	 getTimerBar()->setPercentage(100 * getCurrentTime() / getTotalTimerDuration());
 	
	 ClampTimer();

}

 
CGCObjTimer::~CGCObjTimer()
 {
	 
 }
