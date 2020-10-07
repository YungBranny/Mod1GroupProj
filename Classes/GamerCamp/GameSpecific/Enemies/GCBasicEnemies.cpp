
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

void CGCBasicEnemies::VOnUpdate(f32 fTimestep)
{
	
}

