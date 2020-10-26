// We use header files to pull in declarations from another file.
#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

//Class File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

using namespace cocos2d;

CGCObjKeys::CGCObjKeys(void)
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjKeys))
	, m_fKeysGravity		(	0.0f	)
	, m_bJustCollided		(	false	)
	, m_iCollisionBuffer	(	60		)
{
	//m_keysGravity = 0.0f;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const char* keysSprite = "TexturePacker/Sprites/Coin/Coin.plist";
	{
		CreateSprite(keysSprite);
		SetResetPosition(cocos2d::Vec2(500, 120));
		SetParent(IGCGameLayer::ActiveInstance());
	}
}


CGCObjKeys::~CGCObjKeys()
{

}

IN_CPP_CREATION_PARAMS_DECLARE(CGCObjKeys, "TexturePacker/Sprites/Key/Key.plist", "Key", b2_staticBody, true);
void CGCObjKeys::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjKeys);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

void CGCObjKeys::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();


}

void CGCObjKeys::CollisionChecker()
{
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
	SetSpriteRotation(GetSpriteRotation() + 0.1f);
	CollisionChecker();
}

void CGCObjKeys::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}

void CGCObjKeys::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody()->SetGravityScale(getGravity());
}