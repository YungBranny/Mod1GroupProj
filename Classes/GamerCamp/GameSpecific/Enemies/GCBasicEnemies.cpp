#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCBasicEnemies.h"

USING_NS_CC;

CGCBasicEnemies::CGCBasicEnemies()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
{
	
}

IN_CPP_CREATION_PARAMS_DECLARE( CGCBasicEnemies, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true );

void CGCBasicEnemies::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCBasicEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszAnim_marioJog = "Jog";

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}



void CGCBasicEnemies::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (cocos2d::Vec2(100, 100));
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (0.0f, 0.0f));
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}
void CGCBasicEnemies::VOnUpdate(f32 fTimestep)
{
}

void CGCBasicEnemies::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}
void CGCBasicEnemies::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody ()->SetGravityScale (1.0f);
}





