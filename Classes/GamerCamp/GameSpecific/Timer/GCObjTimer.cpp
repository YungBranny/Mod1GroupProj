#include <string.h>

#include "GamerCamp/GameSpecific/Timer/GCObjTimer.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

/////////////////////////////////////////////////////////////////////////////////////
/// using

using namespace cocos2d;


/////////////////////////////////////////////////////////////////////////////////////
 CGCObjTimer::CGCObjTimer()
	:m_fTotalTimerDuration                ( 100 )
    ,m_fTimerDecreaseValue                (  1  )
    ,m_fTimeBuffer                        ( 100.0f )  // higher the slower the timer is 
    
{
 	//Set Current time to the max Time
	 setCurrentTime(getTotalTimerDuration());
 	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	setTimerText(Label::createWithTTF("Hello world ", "fonts/arial.ttf", 35.0f));

	getTimerText()->setColor(Color3B::MAGENTA);

	getTimerText()->setPosition(Vec2(visibleSize.width / 2 - 450 , visibleSize.height +  10));

	
 	
	getTimerText()->setString(std::to_string(getCurrentTime()) + "%"  );

	
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
{}
