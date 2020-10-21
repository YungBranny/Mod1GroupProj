

#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjScalingBasicPlatform.h"



CGCObjScalingBasicPlatform::CGCObjScalingBasicPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingBasicPlatform))
{
}

IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingBasicPlatform, "TexturePacker/Sprites/BasicScalingPlatform/BasicScalingPlatform.plist", "BasicScalingPlatform", b2_staticBody, true);

void CGCObjScalingBasicPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjScalingBasicPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
}






