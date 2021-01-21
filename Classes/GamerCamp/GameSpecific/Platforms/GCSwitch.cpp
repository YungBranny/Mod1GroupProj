

#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCSwitch.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCSwitch);

GCSwitch::GCSwitch () //constructor
	: CGCObjSpritePhysics (GetGCTypeIDOf (GCSwitch))
	,m_bSwitchHit(false)
{
}

void GCSwitch::VOnResurrected () //resurrected
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0);
}

void GCSwitch::VOnReset () //reset
{
	CGCObjSpritePhysics::VOnReset ();
	m_bSwitchHit = false;
}






