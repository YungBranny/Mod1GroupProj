#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"



#include "GCObjBrickPlatform.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjBrickPlatform);

GCObjBrickPlatform::GCObjBrickPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (GCObjBrickPlatform))
{

}