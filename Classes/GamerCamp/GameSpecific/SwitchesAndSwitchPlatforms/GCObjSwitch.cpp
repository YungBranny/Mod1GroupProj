
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjSwitch.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjSwitch);


CGCObjSwitch::CGCObjSwitch ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjSwitch))
{

}

//CHooses what sprite is drawn
//IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingBasicPlatform, "TexturePacker/Sprites/BasicScalingPlatform/BasicScalingPlatform.plist", "BasicScalingPlatform", b2_staticBody, true);

void CGCObjSwitch::VOnResourceAcquire ()
{
	CGCObjSwitch::VOnResourceAcquire ();
}






