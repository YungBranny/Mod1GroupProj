
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCBasicEnemies.h"

CGCBasicEnemies::CGCBasicEnemies ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
{
}

IN_CPP_CREATION_PARAMS_DECLARE (CGCBasicEnemies, "TexturePacker/Sprites/KoopaTrooper/KoopaTrooper.plist", "koopa", b2_dynamicBody, true);

void CGCBasicEnemies::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCBasicEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();
}

void CGCBasicEnemies::VOnResurrected( void )
{
	CGCBasicEnemies::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (1.0f);
}

void CGCBasicEnemies::VOnReset (void)
{
	//CGCBasicEnemies::VOnReset ();
	// reset
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (0.0f, 0.0f));
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}

void CGCBasicEnemies::VOnResourceRelease ()
{
	CGCBasicEnemies::VOnResourceRelease ();
}

void CGCBasicEnemies::VOnUpdate(f32 fTimestep)
{
	
}

