#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjTimerBar.h"



CGCObjTimerBar::CGCObjTimerBar()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjTimerBar))
	,m_v2TimerBarStartPos(400, 500)
{
	SetResetPosition(m_v2TimerBarStartPos);
	/*
	SetScale(10.0f, 10.0f);*/
}

IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTimerBar, "TexturePacker/Sprites/TimerBar/WhiteSquare.plist", "platform", b2_staticBody, true);
void CGCObjTimerBar::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTimerBar);

	CGCObjSpritePhysics::VOnResourceAcquire();
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);


}



void CGCObjTimerBar::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
	// reset
	SetFlippedX(false);
	SetFlippedY(false);

	SetResetPosition(m_v2TimerBarStartPos);
	if (GetPhysicsBody())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody()->SetFixedRotation(true);
	}

}
void CGCObjTimerBar::VOnUpdate(f32 fTimestep)
{
}

void CGCObjTimerBar::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}
void CGCObjTimerBar::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();

}




