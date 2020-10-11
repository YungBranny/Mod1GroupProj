#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"



#include "GCMovingEnemies.h"

using namespace cocos2d;

CGCMovingEnemies::CGCMovingEnemies ()
//not letting me inherit from basic enemies
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCMovingEnemies))
	//, m_eMoveDirection (EMoveDirection::Right)
	, m_bMovingLeftAndRight (true)
	, m_fEndDestination1	(400,400)
	, m_fEndDesitnation2	(100,100)
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





IN_CPP_CREATION_PARAMS_DECLARE (CGCMovingEnemies, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);
void CGCMovingEnemies::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCMovingEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();

	//const char* pszAnim_marioJog = "Jog";

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	//RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}


void CGCMovingEnemies::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (cocos2d::Vec2 (100, 100));
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (0, 0.0f));
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

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

cocos2d::Vec2	MovingEnemyRight = cocos2d::Vec2 (30, 0.0f);
cocos2d::Vec2	MovingEnemyLeft = ( -MovingEnemyRight );

cocos2d::Vec2	MovingEnemyUp = cocos2d::Vec2 (0.0f, 10.0f);
cocos2d::Vec2	MovingEnemyDown = ( -MovingEnemyUp );



void CGCMovingEnemies::VOnUpdate (f32 fTimeStep)
{
	//m_fTimeInCurrentMoveDirection += fTimeStep;
	//CGCObjSpritePhysics::VOnUpdate (fTimeStep);
	//
	//GetPhysicsBody ()->ApplyForceToCenter (b2Vec2 (100, 0),true );
	if (m_bMovingLeftAndRight == true) 
	{
		//m_eMoveDirection = Right;
		switch (m_eMoveDirection)
		{
		case EMoveDirection::Right:
		{
			if (GetSpritePosition ().x >= m_fEndDestination1.x)
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
		}
			break;
		
		
		case EMoveDirection::Left:
		{
			if (GetSpritePosition ().x <= m_fEndDesitnation2.x)
			{
				m_eMoveDirection = EMoveDirection::Right;
			}
		}
			break;
	
		}
	}
	
	if (m_bMovingLeftAndRight == false)
	{
		//m_eMoveDirection = Up;
		switch (m_eMoveDirection)
		{
		case EMoveDirection::Up:
		{
			if (GetSpritePosition ().y >= m_fEndDestination1.y)
			{
				m_eMoveDirection = EMoveDirection::Down;
			}
		}
		break;


		case EMoveDirection::Down:
		{
			if (GetSpritePosition ().y <= m_fEndDesitnation2.y)
			{
				m_eMoveDirection = EMoveDirection::Up;
			}
		}
		break;
		}
	}
	
	switch (m_eMoveDirection)
	{
	case EMoveDirection::Right:
	{
		this->SetVelocity (MovingEnemyRight);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (400, 0));
	}
	break;

	case EMoveDirection::Left:
	{
		//MovingEnemyRight = cocos2d::Vec2 (-30, 0.0f);

		this->SetVelocity (MovingEnemyLeft);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (100, 0));
	}
	break;
	
	case EMoveDirection::Up:
	{
		this->SetVelocity (MovingEnemyUp);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (400, 0));
	}
	break;

	case EMoveDirection::Down:
	{
		//MovingEnemyRight = cocos2d::Vec2 (-30, 0.0f);

		this->SetVelocity (MovingEnemyDown);
		//this->GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (100, 0));
	}
	break;
	}


	

	//this->SetVelocity (MovingEnemyRight);
}
