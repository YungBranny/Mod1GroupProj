
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "CGCObjSwitchPlatform2.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjSwitchPlatform2);


CGCObjSwitchPlatform2::CGCObjSwitchPlatform2 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjSwitchPlatform2))
{
	//m_audio->playBackgroundMusic ("", true);

}

void CGCObjSwitchPlatform2::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0);
}



void CGCObjSwitchPlatform2::DestroyPlatform ()
{
	GetPhysicsBody ()->SetTransform (b2Vec2 (-1000, 1000), 0.0f);
}


void CGCObjSwitchPlatform2::VOnUpdate (f32 fTimeStep)
{
	//DestroyPlatform ();
}

