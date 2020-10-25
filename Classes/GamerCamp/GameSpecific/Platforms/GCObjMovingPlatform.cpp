#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjMovingPlatform.h"

CGCMovingPlatform::CGCMovingPlatform()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCMovingPlatform))
	, m_moveUpAndDown(true)
	, m_endPosition(970, 900)
	, m_endPosition1(900, 970)
	, m_vMovingRightVelocity(cocos2d::Vec2(0.0f, 10.0f))
	, m_vMovingLeftVelocity(-m_vMovingRightVelocity)
	, m_vMovingUpVelocity(cocos2d::Vec2(9.0f, 0.0f))
	, m_vMovingDownVelocity(-m_vMovingUpVelocity)
	, m_bJustCollided(false)
	, m_iCollisionBuffer(60)
{
	InitialiseMovementDirection();
}

void CGCMovingPlatform::InitialiseMovementDirection()
{
	if( m_moveUpAndDown == true )
	{
		m_eMoveDirection = EMoveDirection::Right;
	}
	else if( m_moveUpAndDown == false )
	{
		m_eMoveDirection = EMoveDirection::Up;
	};
}

//CGCMovingPlatform::~CGCMovingPlatform()
//{
//
//}

IN_CPP_CREATION_PARAMS_DECLARE(CGCMovingPlatform, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_dynamicBody, true);
void CGCMovingPlatform::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCMovingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire();

	// animate!
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	//RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}

void CGCMovingPlatform::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
	// reset
	SetFlippedX(false);
	SetFlippedY(false);

	SetResetPosition(cocos2d::Vec2(100, 100));
}


void CGCMovingPlatform::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();
}

void CGCMovingPlatform::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	//GetPhysicsBody()->SetGravityScale(getGravity());
}


void CGCMovingPlatform::ChangeDirection()
{
	if( m_moveUpAndDown == true )
	{
		switch( m_eMoveDirection )
		{
		case EMoveDirection::Right:
		{
			if( GetSpritePosition().x >= m_endPosition.x )
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
		}
		break;

		case EMoveDirection::Left:
		{
			if( GetSpritePosition().x <= m_endPosition1.x )
			{
				m_eMoveDirection = EMoveDirection::Right;
			}
		}
		break;
		}
	}

	if( m_moveUpAndDown == true )
	{
		switch( m_eMoveDirection )
		{
		case EMoveDirection::Up:
		{
			if( GetSpritePosition().y >= m_endPosition.y )
			{
				m_eMoveDirection = EMoveDirection::Down;
			}
		}
		break;

		case EMoveDirection::Down:
		{
			if( GetSpritePosition().y <= m_endPosition1.y )
			{
				m_eMoveDirection = EMoveDirection::Up;
			}
		}
		break;
		}
	}
}

void CGCMovingPlatform::Movement()
{
	switch( m_eMoveDirection )
	{
	case EMoveDirection::Right:
	{
		this->SetVelocity(m_vMovingRightVelocity);
	}
	break;

	case EMoveDirection::Left:
	{
		this->SetVelocity(m_vMovingLeftVelocity);
	}
	break;

	case EMoveDirection::Up:
	{
		this->SetVelocity(m_vMovingUpVelocity);
	}
	break;

	case EMoveDirection::Down:
	{
		this->SetVelocity(m_vMovingDownVelocity);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (100, 0));
	}
	break;
	}
}



void CGCMovingPlatform::CollisionChecker()
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

void CGCMovingPlatform::VOnUpdate(f32 fTimeStep)
{
	ChangeDirection();
	Movement();
	CollisionChecker();

}