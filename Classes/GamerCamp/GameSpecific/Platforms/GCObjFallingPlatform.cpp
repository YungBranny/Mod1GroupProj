#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"

#include "GCObjFallingPlatform.h"





CGCObjFallingPlatform::CGCObjFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjFallingPlatform))
	, m_v2StartPos			(400, 400)									  //Initalises the variable with a default value
	, m_v2FallingVelocity	(0.0f, -10.0f)								  //Initalises the variable with a default value
	, m_v2DefaultVelocity	(0.0f, 0.0f)								  //Initalises the variable with a default value
	, m_bContactWithPlayer	(false)										  //Initalises the variable with a default value
	, m_fMaxDestroyPlatformTick(120.0f)
	, m_fCurrentDestroyPlatformTick(m_fMaxDestroyPlatformTick)									  //Initalises the variable with a default value
	, m_bCanDelete			(false)										  //Initalises the variable with a default value
	, m_v2EndPos			(m_v2StartPos.x, m_v2StartPos.y - ( -1.0f ))  //Initalises the variable with a default value
{
	SetResetPosition (GetStartPos ()); // sets the reset position to be the start position
}



//sets the sprite 
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjFallingPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_dynamicBody, true);
void CGCObjFallingPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
}


//default sprite physics 
void CGCObjFallingPlatform::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);
	m_bCanDelete = false;
	m_fCurrentDestroyPlatformTick = m_fMaxDestroyPlatformTick;
	
	SetResetPosition (GetStartPos ());
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}

//Calls the function that moves the platform down
void CGCObjFallingPlatform::MoveDownOnContact ()
{
	if (GetContactWithPlayer() == true) //if this boolean gets set to true it starts decreasing the platform tick and changes the velocity of the platform so it moves down
	{
		SetVelocity (m_v2FallingVelocity);

		if (m_fCurrentDestroyPlatformTick >= 0)
		{
			m_fCurrentDestroyPlatformTick--;
		}

		if (m_fCurrentDestroyPlatformTick <= 0)
		{
			if (m_bCanDelete == false)
			{
				m_bCanDelete = true;
			}
			
		}
	}
	else // changes the velocity to 0 so it stops moving
	{
		SetVelocity (m_v2DefaultVelocity);
	}
}

void CGCObjFallingPlatform::VOnUpdate (f32 fTimestep) //update function
{
   MoveDownOnContact ();
}

void CGCObjFallingPlatform::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
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
//standard spritephysics functions
void CGCObjFallingPlatform::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();
	if (nullptr != m_pCustomCreationParams.get ())
	{
		m_pCustomCreationParams.reset (nullptr);
	}
}

void CGCObjFallingPlatform::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0.0f);

}





