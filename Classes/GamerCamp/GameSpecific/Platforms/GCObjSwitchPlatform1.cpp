
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjSwitchPlatform1.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjSwitchPlatform1);


CGCObjSwitchPlatform1::CGCObjSwitchPlatform1 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjSwitchPlatform1))
{
	//m_audio->playBackgroundMusic ("", true);

}

void CGCObjSwitchPlatform1::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0);
}



void CGCObjSwitchPlatform1::DestroyPlatform()
{
	
		 SetResetPosition (cocos2d::Vec2 (-1000, -1000));
		 GetPhysicsBody ()->SetTransform (b2Vec2 (-1000, 1000), 0.0f);
		 //SetScale (0, 0);
}


void CGCObjSwitchPlatform1::VOnUpdate (f32 fTimeStep)
{
	//DestroyPlatform ();
}

