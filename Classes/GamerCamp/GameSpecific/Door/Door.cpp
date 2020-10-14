
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "Door.h"



CGCObjDoor::CGCObjDoor ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjLongPlatformTest))
	, m_v2StartPos (400, 400)
{
	SetResetPosition (GetStartPos ());
}




IN_CPP_CREATION_PARAMS_DECLARE (CGCObjDoor, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_staticBody, true);
void CGCObjDoor::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjDoor);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);


}



void CGCObjDoor::VOnReset ()
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
void CGCObjDoor::VOnUpdate (f32 fTimestep)
{
}

void CGCObjDoor::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCObjDoor::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();

}





