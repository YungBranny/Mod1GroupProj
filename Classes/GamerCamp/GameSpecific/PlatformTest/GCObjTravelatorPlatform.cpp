#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjTravelatorPlatform.h"



CGCObjTravelatorPlatform::CGCObjTravelatorPlatform()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjTravelatorPlatform))
	, m_v2StartPos(600, 600)
{
	SetResetPosition(GetStartPos());
}




IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTravelatorPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_staticBody, true);
void CGCObjTravelatorPlatform::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTravelatorPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire();
	SetResetPosition(GetStartPos());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);


}



void CGCObjTravelatorPlatform::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
	// reset
	SetFlippedX(false);
	SetFlippedY(false);

	SetResetPosition(GetStartPos());
	if (GetPhysicsBody())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody()->SetFixedRotation(true);
	}

}
void CGCObjTravelatorPlatform::VOnUpdate(f32 fTimestep)
{
}

void CGCObjTravelatorPlatform::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}
void CGCObjTravelatorPlatform::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();

}





