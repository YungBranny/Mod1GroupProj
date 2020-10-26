#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjLongPlatformTest.h"

#include "AudioEngine.h"



CGCObjLongPlatformTest::CGCObjLongPlatformTest ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjLongPlatformTest))
	, m_v2StartPos (400, 400)				//default start position
{
	SetResetPosition (GetStartPos ());		//sets the start position to the v2start pos
}	



	
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjLongPlatformTest, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_staticBody, true);
void CGCObjLongPlatformTest::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjLongPlatformTest);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	

}



void CGCObjLongPlatformTest::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (GetStartPos ());
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}
void CGCObjLongPlatformTest::VOnUpdate (f32 fTimestep)
{
}

void CGCObjLongPlatformTest::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCObjLongPlatformTest::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();

}





