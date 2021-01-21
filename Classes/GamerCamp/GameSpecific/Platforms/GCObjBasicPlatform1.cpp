#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingBasicPlatform.h"


#include "GCObjBasicPlatform1.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjBasicPlatform1);

GCObjBasicPlatform1::GCObjBasicPlatform1 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingBasicPlatform))
{

}