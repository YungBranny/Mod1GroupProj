
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjSwitchPlatform1.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjSwitchPlatform1);


CGCObjSwitchPlatform1::CGCObjSwitchPlatform1 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjSwitchPlatform1))
{
	//m_audio->playBackgroundMusic ("", true);

}


void CGCObjSwitchPlatform1::DestroyPlatform (CGCObjPlayer& rcPlayer)
{
	if ( rcPlayer.getSwitchesHit() >= 1 )
	{		
		SetResetPosition (cocos2d::Vec2 (-1000, -1000));
	}
}


void CGCObjSwitchPlatform1::VOnUpdate (f32 fTimeStep, CGCObjPlayer& rcPlayer)
{
	DestroyPlatform (rcPlayer);
}

