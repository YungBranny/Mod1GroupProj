

#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjShortPlatformTest.h"



CGCObjShortPlatformTest::CGCObjShortPlatformTest ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjLongPlatformTest))
	, m_v2StartPos (400, 400)
{
	SetResetPosition (GetStartPos ());
}




IN_CPP_CREATION_PARAMS_DECLARE (CGCObjShortPlatformTest, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_staticBody, true);
void CGCObjShortPlatformTest::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjShortPlatformTest);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);


}



void CGCObjShortPlatformTest::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (GetStartPos());
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}
void CGCObjShortPlatformTest::VOnUpdate (f32 fTimestep)
{
}

void CGCObjShortPlatformTest::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCObjShortPlatformTest::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();

}





