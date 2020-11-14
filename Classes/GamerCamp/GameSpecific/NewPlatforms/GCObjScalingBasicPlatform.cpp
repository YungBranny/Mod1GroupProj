

#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjScalingBasicPlatform.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjScalingBasicPlatform);

CGCObjScalingBasicPlatform::CGCObjScalingBasicPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingBasicPlatform))
{
	//m_audio->playBackgroundMusic ("", true);

}

//CHooses what sprite is drawn
//IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingBasicPlatform, "TexturePacker/Sprites/BasicScalingPlatform/BasicScalingPlatform.plist", "BasicScalingPlatform", b2_staticBody, true);

void CGCObjScalingBasicPlatform::VOnResourceAcquire ()
{

	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjScalingBasicPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
}






