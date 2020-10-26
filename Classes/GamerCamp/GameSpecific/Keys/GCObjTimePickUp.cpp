#include "GamerCamp/GameSpecific/Keys/GCObjTimePickUp.h"
#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

//Class File for 'CGCObjTimePickUp' created by Mehak Hussain on 19/10/2020.

using namespace cocos2d;

CGCObjTimePickUp::CGCObjTimePickUp(void)
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjTimePickUp))
	, m_fTimeGravity(0.0f)
	, m_bJustCollided(false)
	, m_iCollisionBuffer(60)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	const char* timeSprite = "TexturePacker/Sprites/TimerPickUp/TimerPickUp.plist";
	{
		CreateSprite(timeSprite);
		SetResetPosition(cocos2d::Vec2(860, 500));
		SetParent(IGCGameLayer::ActiveInstance());
	}
}

CGCObjTimePickUp::~CGCObjTimePickUp()
{

}

IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTimePickUp, "TexturePacker/Sprites/TimerPickUp/TimerPickUp.plist", "TimerPickUp", b2_staticBody, true);
//virtual 
void CGCObjTimePickUp::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTimePickUp);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

void CGCObjTimePickUp::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
}

void CGCObjTimePickUp::CollisionChecker()
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

void CGCObjTimePickUp::VOnUpdate(f32 fTimestep)
{
	SetSpriteRotation(GetSpriteRotation() + 0.1f);
	CollisionChecker();
}

void CGCObjTimePickUp::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}

void CGCObjTimePickUp::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody()->SetGravityScale(getGravity());
}