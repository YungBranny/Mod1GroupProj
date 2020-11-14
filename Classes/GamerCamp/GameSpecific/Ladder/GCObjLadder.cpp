#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjLadder.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjLadder);

CGCObjLadder::CGCObjLadder(void)
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjLadder))
{

}

//IN_CPP_CREATION_PARAMS_DECLARE (CGCObjExitDoor, "TexturePacker/Sprites/Ladder/Ladder.plist", "Ladder", b2_staticBody, true );
void CGCObjLadder::VOnResourceAcquire()
{
	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjExitDoor);

	CGCObjSpritePhysics::VOnResourceAcquire();

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
}