#include "GamerCamp/GameSpecific/Platforms/GCObjMovingPlatform.h"

CGCObjMovingPlatform::CGCObjMovingPlatform()
	: CGCObjSpritePhysics ( GetGCTypeIDOf(CGCObjMovingPlatform) ) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Platform
	, m_bMoveUpAndDown								(	  false		)
	, m_bJustCollided								(	  false		)
	, m_v2StartPosition								(	 800, 280	)
	, m_v2EndPosition								(	 500, 110	)
	, m_v2MoveUpVelocity							( cocos2d::Vec2(0.0f, 3.0f) )
	, m_v2MoveDownVelocity							(	-m_v2MoveUpVelocity	)
	, m_iCollisionBuffer							(	60	)
{
	InitialiseMovementDirection();
}

void CGCObjMovingPlatform::InitialiseMovementDirection() 
{
	if( m_bMoveUpAndDown == true ) // If default is set to 'true', then the platform may go Right and in the opposite direction, which is Left. This may be used for future levels
	{
		m_eMoveDirection = EMoveDirection::Right;
	}
	else if( m_bMoveUpAndDown == false ) // The default 'm_bMoveUpAndDown' is set to 'false', therefore platform can only go up and in the opposite direction, which is down
	{
		m_eMoveDirection = EMoveDirection::Up;
	};
}

IN_CPP_CREATION_PARAMS_DECLARE( CGCObjMovingPlatform, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_dynamicBody, true );
void CGCObjMovingPlatform::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE ( CGCObjMovingPlatform );

	CGCObjSpritePhysics::VOnResourceAcquire();
}

void CGCObjMovingPlatform::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody()->SetGravityScale ( getGravity() );
}

void CGCObjMovingPlatform::Movement()
{
	if( m_bMoveUpAndDown == true )
	{
		switch( m_eMoveDirection )
		{
		case EMoveDirection::Right:
		{
			if( GetSpritePosition().x >= m_v2StartPosition.x )
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
		}
		break;

		case EMoveDirection::Left:
		{
			if( GetSpritePosition().x <= m_v2EndPosition.x )
			{
				m_eMoveDirection = EMoveDirection::Right;
			}
		}
		break;
		}
	}

	if( m_bMoveUpAndDown == false )
	{
		switch( m_eMoveDirection )
		{
		case EMoveDirection::Up:
		{
			if( GetSpritePosition().y >= m_v2StartPosition.y )
			{
				m_eMoveDirection = EMoveDirection::Down;
			}
		}
		break;

		case EMoveDirection::Down:
		{
			if( GetSpritePosition().y <= m_v2EndPosition.y )
			{
				m_eMoveDirection = EMoveDirection::Up;
			}
		}
		break;
		}
	}
}

void CGCObjMovingPlatform::SettingVelocity()
{
	switch( m_eMoveDirection )
	{
	case EMoveDirection::Right:
	{
		this->SetVelocity(m_v2MoveRightVelocity);
	}
	break;

	case EMoveDirection::Left:
	{
		this->SetVelocity(m_v2MoveLeftVelocity);
	}
	break;

	case EMoveDirection::Up:
	{
		this->SetVelocity(m_v2MoveUpVelocity);
	}
	break;

	case EMoveDirection::Down:
	{
		this->SetVelocity(m_v2MoveDownVelocity);
	}
	break;
	}
}

void CGCObjMovingPlatform::CollisionChecker()
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

void CGCObjMovingPlatform::VOnUpdate(f32 fTimeStep)
{
	Movement();
	SettingVelocity();
	CollisionChecker();
}
