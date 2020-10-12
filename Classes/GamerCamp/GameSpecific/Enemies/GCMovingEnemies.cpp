#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"



#include "GCMovingEnemies.h"

//using namespace cocos2d;

CGCMovingEnemies::CGCMovingEnemies ()
//not letting me inherit from basic enemies
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCMovingEnemies))
	//, m_eMoveDirection (EMoveDirection::Right)
	, m_bMovingLeftAndRight			(false)
	, m_vEndDestination1			(400,400)
	, m_vEndDesitnation2			(100,100)
	, m_vMovingRightVelocity		(cocos2d::Vec2 (30, 0.0f))
	, m_vMovingLeftVelocity			(-m_vMovingRightVelocity)
	, m_vMovingUpVelocity			(cocos2d::Vec2 (0.0f, 10.0f))
	, m_vMovingDownVelocity			(-m_vMovingUpVelocity)
{
	InitialiseMovementDirection ();
}


IN_CPP_CREATION_PARAMS_DECLARE (CGCMovingEnemies, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);
void CGCMovingEnemies::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCMovingEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();

	//const char* pszAnim_marioJog = "Jog";

	// animate!
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	//RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}

void CGCMovingEnemies::InitialiseMovementDirection ()
{
	if (m_bMovingLeftAndRight == true)
	{
		m_eMoveDirection = Right;
	}
	else if (m_bMovingLeftAndRight == false)
	{
		m_eMoveDirection = Up;
	};
}

void CGCMovingEnemies::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (cocos2d::Vec2 (100, 100));
	//if (GetPhysicsBody ())
	//{
	//	cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
	//	GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (0, 0.0f));
	//	GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
	//	GetPhysicsBody ()->SetFixedRotation (true);
	//}

}


void CGCMovingEnemies::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();
}

void CGCMovingEnemies::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (getGravity ());
}


void CGCMovingEnemies::ChangeDirection ()
{
	if (m_bMovingLeftAndRight == true)
	{
		switch (m_eMoveDirection)
		{
		case EMoveDirection::Right:
		{
			if (GetSpritePosition ().x >= m_vEndDestination1.x)
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
		}
		break;

		case EMoveDirection::Left:
		{
			if (GetSpritePosition ().x <= m_vEndDesitnation2.x)
			{
				m_eMoveDirection = EMoveDirection::Right;
			}
		}
		break;
		}
	}

	if (m_bMovingLeftAndRight == false)
	{
		switch (m_eMoveDirection)
		{
		case EMoveDirection::Up:
		{
			if (GetSpritePosition ().y >= m_vEndDestination1.y)
			{
				m_eMoveDirection = EMoveDirection::Down;
			}
		}
		break;

		case EMoveDirection::Down:
		{
			if (GetSpritePosition ().y <= m_vEndDesitnation2.y)
			{
				m_eMoveDirection = EMoveDirection::Up;
			}
		}
		break;
		}
	}
}

void CGCMovingEnemies::Movement ()
{
	switch (m_eMoveDirection)
	{
	case EMoveDirection::Right:
	{
		this->SetVelocity (m_vMovingRightVelocity);
	}
	break;

	case EMoveDirection::Left:
	{
		this->SetVelocity (m_vMovingLeftVelocity);
	}
	break;

	case EMoveDirection::Up:
	{
		this->SetVelocity (m_vMovingUpVelocity);
	}
	break;

	case EMoveDirection::Down:
	{
		this->SetVelocity (m_vMovingDownVelocity);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (100, 0));
	}
	break;
	}
}

void CGCMovingEnemies::VOnUpdate (f32 fTimeStep)
{
	ChangeDirection ();
	Movement ();
}
