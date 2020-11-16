#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjKeys.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjKeys);

CGCObjKeys::CGCObjKeys ( void )
	: CGCObjSpritePhysics (GetGCTypeIDOf(CGCObjKeys) ) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Keys
	, m_bJustCollided		(	false	)
	, m_iCollisionBuffer	(	 60		)
{

}

CGCObjKeys::~CGCObjKeys()
{

}

// Create the Key Sprite, give it a Static Physics Body which means it won't move and then set fixed rotation to 'True'
//IN_CPP_CREATION_PARAMS_DECLARE ( CGCObjKeys, "TexturePacker/Sprites/Key/cc_collectible_key.plist", "Key", b2_staticBody, true );
void CGCObjKeys::VOnResourceAcquire ( void )
{
	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjKeys);

	CGCObjSpritePhysics::VOnResourceAcquire();
}

void CGCObjKeys::CollisionChecker()
{
	// Default Collision is false until collided with, this stops collision being called multiple times
	if( m_bJustCollided == true )
	{
		if( m_iCollisionBuffer >= 0 )
		{
			m_iCollisionBuffer--;
		}

		if( m_iCollisionBuffer <= 0 )
		{
			m_bJustCollided = false;
			m_iCollisionBuffer = 60;
		}
	}
}

void CGCObjKeys::VOnUpdate ( f32 fTimestep )
{
	SetSpriteRotation(GetSpriteRotation() + 0.1f); // Setting the rotation for the Keys, so they spin and look appealing to the Player
	CollisionChecker(); // Updates CollisionChecker
}