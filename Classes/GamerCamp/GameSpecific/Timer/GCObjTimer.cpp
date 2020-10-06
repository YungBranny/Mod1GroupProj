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
	,m_fCurrentTime                       ( m_fCurrentTime )
    ,m_fTimerDecreaseValue                ( 1.0f  )
    //,pTimerText(nullptr)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

    //pTimerText = Label::createWithTTF(" ", "fonts/arial.ttf", 24);

	pTimerText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));

	pTimerText->setColor(Color3B:: MAGENTA);

	pTimerText->setString(std::to_string(m_fCurrentTime));

	
	
}



CGCObjTimer::~CGCObjTimer()
{}
