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
	if( m_bMoveUpAndDown == true ) // If default bool is set to 'true', then the platform may go Right and in the opposite direction, which is Left. This may be used for future levels
	{
		m_eMoveDirection = EMoveDirection::Right;
	}
	else if( m_bMoveUpAndDown == false ) // The default 'm_bMoveUpAndDown' bool is set to 'false', therefore platform can only go up and in the opposite direction, which is down
	{
		m_eMoveDirection = EMoveDirection::Up;
	};
}

// Create the Platform Sprite, give it a Kinematic Physics Body which means it only moves when code tells it too and then set fixed rotation to 'True'
IN_CPP_CREATION_PARAMS_DECLARE( CGCObjMovingPlatform, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_kinematicBody, true );
void CGCObjMovingPlatform::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE ( CGCObjMovingPlatform );

	CGCObjSpritePhysics::VOnResourceAcquire();
}

// If 'm_bMoveUpAndDown' is set to 'True', Platform will move from Right, reach the greater or equal than point that the Start Position has been set at
// then move in the opposite direction which is Left and then move back towards the Start Position once Platform reaches End Position
void CGCObjMovingPlatform::OppositeDirection()
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

	// It is the same for if 'm_bMoveUpAndDown' was set as 'False' - which it is, but now the movement switch is Up and Down
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
	// Here is Velocity set for each Direction
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

void CGCObjMovingPlatform::VOnUpdate(f32 fTimeStep)
{
	OppositeDirection();
	SettingVelocity();
	CollisionChecker();
}
