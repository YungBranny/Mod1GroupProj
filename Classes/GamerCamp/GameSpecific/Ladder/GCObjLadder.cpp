#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjLadder.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS ( CGCObjLadder );

CGCObjLadder::CGCObjLadder ( void )
	: CGCObjSpritePhysics (GetGCTypeIDOf ( CGCObjLadder ) )
{

}

void CGCObjLadder::VOnResourceAcquire()
{
	CGCObjSpritePhysics::VOnResourceAcquire();

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
}