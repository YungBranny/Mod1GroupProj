#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCBasicEnemies.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCBasicEnemies);

CGCBasicEnemies::CGCBasicEnemies()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
{
	
}

//sets the sprite
//IN_CPP_CREATION_PARAMS_DECLARE( CGCBasicEnemies, "TexturePacker/Sprites/Spike/Spike.plist", "Spike", b2_staticBody, true);
void CGCBasicEnemies::VOnResourceAcquire()
{
	///IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCBasicEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire();

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
}

void CGCBasicEnemies::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
}
void CGCBasicEnemies::VOnUpdate(f32 fTimestep)
{
}

void CGCBasicEnemies::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();
}
void CGCBasicEnemies::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected ();
}





