#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

using namespace cocos2d;

CGCObjKeys::CGCObjKeys(void)
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjKeys)) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Keys
	, m_bJustCollided		(	false	)
	, m_iCollisionBuffer	(	60		)
{

}

CGCObjKeys::~CGCObjKeys()
{

}

// Create the Key Sprite, give it a physics body and then set fixed rotation to 'True'
IN_CPP_CREATION_PARAMS_DECLARE(CGCObjKeys, "TexturePacker/Sprites/Key/Key.plist", "Key", b2_staticBody, true);
void CGCObjKeys::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjKeys);
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

void CGCObjKeys::VOnUpdate(f32 fTimestep)
{
	SetSpriteRotation(GetSpriteRotation() + 0.1f); // Setting the rotation for the keys, so they spin and look appealing to the Player
	CollisionChecker(); // Updates CollisionChecker
}