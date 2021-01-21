#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingBasicPlatform.h"


#include "GCObjBasicPlatform6.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjBasicPlatform6);

GCObjBasicPlatform6::GCObjBasicPlatform6 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingBasicPlatform))
{

}