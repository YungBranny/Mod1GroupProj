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
	:m_fTotalTimerDuration                ( 30.0f )
    ,m_fTimerDecreaseValue                ( 0.02f )
    ,m_fTimeBuffer                        ( 30.0f )
    
{
	 setCurrentTime(getTotalTimerDuration());
 	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	setTimerText(Label::createWithTTF("Hello world ", "fonts/arial.ttf", 24.0f));

	getTimerText()->setColor(Color3B::MAGENTA);

	getTimerText()->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	
	getTimerText()->setString(std::to_string(getCurrentTime() ));

	
}

 void CGCObjTimer::DecreaseTimer()
 {

 	//if(getTimeBuffer()> 0)
 	//{
		//setTimeBuffer(getTimeBuffer()-1);
 	//}
 	
	/*else if(getTimeBuffer()<= 0)
	{*/
		
	if (getCurrentTime() >= 0)
	{


		setCurrentTime(getCurrentTime() - getTimerDecreaseValue());

		getTimerText()->setString(std::to_string(getCurrentTime()));

	}
	else
	{
		setCurrentTime(0.0f);
	}
		
		
		/*setTimeBuffer(60);*/
	/*}*/
 
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
