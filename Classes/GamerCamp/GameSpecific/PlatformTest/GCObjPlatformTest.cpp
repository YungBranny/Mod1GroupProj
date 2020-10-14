#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjPlatformTest.h"



CGCObjPlatformTest::CGCObjPlatformTest ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjPlatformTest))
{
	SetResetPosition (cocos2d::Vec2(400, 400));
}

IN_CPP_CREATION_PARAMS_DECLARE (CGCObjPlatformTest, "TexturePacker/Sprites/Platform/Platform.plist", "platform", b2_staticBody, true);
void CGCObjPlatformTest::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjPlatformTest);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	

}



void CGCObjPlatformTest::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (cocos2d::Vec2 (300, 500));
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}
void CGCObjPlatformTest::VOnUpdate (f32 fTimestep)
{
}

void CGCObjPlatformTest::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCObjPlatformTest::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();

}





