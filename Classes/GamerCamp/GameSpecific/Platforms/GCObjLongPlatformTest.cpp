#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"

#include "GCObjLongPlatformTest.h"



CGCObjLongPlatformTest::CGCObjLongPlatformTest ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjLongPlatformTest))
	, m_v2StartPos (400, 400)				//default start position
{
	SetResetPosition (GetStartPos ());		//sets the start position to the v2start pos
}	

	//sets the sprite and gets the physics body
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjLongPlatformTest, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_staticBody, true);
void CGCObjLongPlatformTest::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjLongPlatformTest);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ()); //sets the reset position
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	

}

void CGCObjLongPlatformTest::VOnReset () //Defaults for spritephysicsobj 
{
	CGCObjSpritePhysics::VOnReset ();
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





