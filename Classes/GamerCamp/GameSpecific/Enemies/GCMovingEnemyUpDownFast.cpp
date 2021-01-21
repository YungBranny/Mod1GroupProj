#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCMovingEnemyUpDownFast.h"


#ifndef TINYXML2_INCLUDED
#include "external\tinyxml2\tinyxml2.h"
#endif

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif



//using namespace cocos2d;

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCMovingEnemyUpDownFast);

CGCMovingEnemyUpDownFast::CGCMovingEnemyUpDownFast ()
//not letting me inherit from basic enemies
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCMovingEnemies))
	, m_bMovingLeftAndRight (false)							//Default values for the variables
	, m_vEndDestination1 (600, 400)						//Default values for the variables
	, m_vEndDesitnation2 (450, 100)						//Default values for the variables
	, m_vMovingRightVelocity (cocos2d::Vec2 (12.0f, 0.0f))	//Default values for the variables
	, m_vMovingLeftVelocity (-m_vMovingRightVelocity)		//Default values for the variables
	, m_vMovingUpVelocity (cocos2d::Vec2 (0.0f, 3.0f))	//Default values for the variables
	, m_vMovingDownVelocity (-m_vMovingUpVelocity)			//Default values for the variables
	, m_bJustCollided (false)							//Default values for the variables
	, m_iCollisionBuffer (60)							//Default values for the variables
	, m_iCollisionDirBuffer (20)
	, m_bDefaultDirection (true)
	, m_bJustChangedDir (false)
	, m_pCustomCreationParams (nullptr)
{
	InitialiseMovementDirection (); //calls the function when this class is initalised

}
void CGCMovingEnemyUpDownFast::VOnResurrected (void)
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0.0f);
}
//this function checks if the bool"m_bMovingLeftAndRight  is true it 
//sets the starting direction to right, if not it is set to up
//If the default starting direction is right then 
//the only other direction it can go is left, if the default position
//is up then the only other direction it can go is down
void CGCMovingEnemyUpDownFast::InitialiseMovementDirection ()
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

void CGCMovingEnemyUpDownFast::VOnResourceAcquire ()
{

	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCMovingEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();


	const char* pszAnim_Idle = "UEnemyIdle";
	if (pszAnim_Idle)
	{
		cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
		RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_Idle)));
	}
}

//
//void CGCMovingEnemies::VOnReset ()
//{
//	CGCObjSpritePhysics::VOnReset ();
//}

void CGCMovingEnemyUpDownFast::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

	if (nullptr != m_pCustomCreationParams.get ())
	{
		m_pCustomCreationParams.reset (nullptr);
	}
}

//void CGCMovingEnemies::VOnResurrected ()
//{
//	CGCObjSpritePhysics::VOnResurrected ();
//	//GetPhysicsBody ()->SetGravityScale (getGravity ());
//	GetPhysicsBody ()->SetGravityScale (0.0f);
//}

//changes the direction if the current position has reached the end desitination 
void CGCMovingEnemyUpDownFast::ChangeDirection ()
{
	if (m_bMovingLeftAndRight == true)
	{
		switch (m_eMoveDirection)
		{
		case EMoveDirection::Right:
		{
			//if (GetSpritePosition ().x >= m_vEndDestination1.x)
			if (m_bDefaultDirection == true)
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
		}
		break;

		case EMoveDirection::Left:
		{
			//if (GetSpritePosition ().x <= m_vEndDesitnation2.x)
			if (m_bDefaultDirection == false)
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
			//if (GetSpritePosition ().y >= m_vEndDestination1.y)
			if (m_bDefaultDirection == true)
			{
				m_eMoveDirection = EMoveDirection::Down;
			}
		}
		break;

		case EMoveDirection::Down:
		{
			//if (GetSpritePosition ().y <= m_vEndDesitnation2.y)
			if (m_bDefaultDirection == false)
			{
				m_eMoveDirection = EMoveDirection::Up;
			}
		}
		break;
		}
	}
}

void CGCMovingEnemyUpDownFast::Movement () //changes the velocity depending on the direction it is going
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
		SetFlippedX (true);
	}
	break;

	case EMoveDirection::Down:
	{
		this->SetVelocity (m_vMovingDownVelocity);
		SetFlippedX (false);
	}
	break;
	}
}


//checks to see if the just collided bool is true, if it is then the collision buffer counts down, once it has reached 0 it sets the bool back to false
//Once its false it can be collided with again
void CGCMovingEnemyUpDownFast::CollisionChecker ()
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

void CGCMovingEnemyUpDownFast::CollisionDirChecker ()
{
	{
		if (m_bJustChangedDir == true)
		{
			if (m_iCollisionBuffer >= 0)
			{
				m_iCollisionBuffer--;
			}

			if (m_iCollisionBuffer <= 0)
			{
				m_bJustChangedDir = false;
				m_iCollisionBuffer = 30;
			}
		}
	}
}

void CGCMovingEnemyUpDownFast::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if (nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData)
	{
		//const tinyxml2::XMLAttribute* pName = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute( "name" );

		//CCLOG( (nullptr == pName) ? "BOB NOT FOUND!" : pName->Value() );

		const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute ("PlistFile");    //customplist    //PlistFile

		const tinyxml2::XMLAttribute* pCustomShape = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute ("shape");

		if (( nullptr != pCustomPlistPath ) && ( 0 != strlen (pCustomPlistPath->Value ()) ))    // && ( (nullptr != pCustomShape) && ( 0 != strlen( pCustomShape->Value() ) ) ) )
		{
			m_pCustomCreationParams = std::make_unique< CGCFactoryCreationParams > (rCreationParams.strClassName.c_str (),
				pCustomPlistPath->Value (),
				pCustomShape->Value (),
				rCreationParams.eB2dBody_BodyType,
				rCreationParams.bB2dBody_FixedRotation);

			pParamsToPassToBaseClass = m_pCustomCreationParams.get ();
		}
	}

	CGCObjSpritePhysics::VHandleFactoryParams (( *pParamsToPassToBaseClass ), v2InitialPosition);
}


void CGCMovingEnemyUpDownFast::VOnUpdate (f32 fTimeStep)
{
	ChangeDirection ();
	Movement ();
	CollisionChecker ();
	CollisionDirChecker ();
}
