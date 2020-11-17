#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatform.h"


#include "GCObjBasicPlatform5.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjBasicPlatform5);

GCObjBasicPlatform5::GCObjBasicPlatform5 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingBasicPlatform))
{

}