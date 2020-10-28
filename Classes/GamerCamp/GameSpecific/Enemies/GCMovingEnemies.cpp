#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"



#include "GCMovingEnemies.h"

//using namespace cocos2d;

CGCMovingEnemies::CGCMovingEnemies ()
//not letting me inherit from basic enemies
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCMovingEnemies))
	, m_bMovingLeftAndRight			(true)							//Default values for the variables
	, m_vEndDestination1			(800,400)						//Default values for the variables
	, m_vEndDesitnation2			(500,100)						//Default values for the variables
	, m_vMovingRightVelocity		(cocos2d::Vec2 (9.0f, 0.0f))	//Default values for the variables
	, m_vMovingLeftVelocity			(-m_vMovingRightVelocity)		//Default values for the variables
	, m_vMovingUpVelocity			(cocos2d::Vec2 (0.0f, 10.0f))	//Default values for the variables
	, m_vMovingDownVelocity			(-m_vMovingUpVelocity)			//Default values for the variables
	, m_bJustCollided				(false)							//Default values for the variables
	, m_iCollisionBuffer			(60)							//Default values for the variables
{
	InitialiseMovementDirection (); //calls the function when this class is initalised
}

//this function checks if the bool"m_bMovingLeftAndRight  is true it 
//sets the starting direction to right, if not it is set to up
//If the default starting direction is right then 
//the only other direction it can go is left, if the default position
//is up then the only other direction it can go is down
void CGCMovingEnemies::InitialiseMovementDirection () 
{
	if (m_bMovingLeftAndRight == true)
	{
		m_eMoveDirection = EMoveDirection::Right;
	}
	else if (m_bMovingLeftAndRight == false)
	{
		m_eMoveDirection = EMoveDirection::Up;
	};
}

//Sets the sprite
IN_CPP_CREATION_PARAMS_DECLARE (CGCMovingEnemies, "TexturePacker/Sprites/MovingEnemy/MovingEnemy/Enemy.plist", "Enemy", b2_dynamicBody, true);
void CGCMovingEnemies::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCMovingEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();

	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
}



void CGCMovingEnemies::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
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

//changes the direction if the current position has reached the end desitination 
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

void CGCMovingEnemies::Movement () //changes the velocity depending on the direction it is going
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
	}
	break;
	}
}


//checks to see if the just collided bool is true, if it is then the collision buffer counts down, once it has reached 0 it sets the bool back to false
//Once its false it can be collided with again
void CGCMovingEnemies::CollisionChecker () 
{
	if (m_bJustCollided == true)
	{
		if (m_iCollisionBuffer >= 0)
		{
			m_iCollisionBuffer--;
		}

		if (m_iCollisionBuffer <= 0)
		{
			m_bJustCollided = false;
			m_iCollisionBuffer = 60;
		}
	}
}

void CGCMovingEnemies::VOnUpdate (f32 fTimeStep)
{
	ChangeDirection ();
	Movement ();
	CollisionChecker ();
}
