#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjScalingFallingPlatform.h"

#include "../../GCCocosInterface/GB2ShapeCache-x.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjScalingFallingPlatform);


CGCObjScalingFallingPlatform::CGCObjScalingFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingFallingPlatform))
	, m_v2FallingVelocity (0.0f, -1.0f)									  //Initalises the variable with a default value
	, m_v2DefaultVelocity (0.0f, 0.0f)									  //Initalises the variable with a default value
	, m_bContactWithPlayer (false)										  //Initalises the variable with a default value
	, m_fMaxDestroyPlatformTick (60.0f)
	, m_fCurrentDestroyPlatformTick (m_fMaxDestroyPlatformTick)
	, m_bCanDelete (false)		//Initalises the variable with a default value

{																		 
}																		 

//Sets the sprite
//IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingFallingPlatform, "TexturePacker/Sprites/FallingScalingPlatform/FallingScalingPlatform.plist", "FallingScalingPlatform", b2_kinematicBody, true);

void CGCObjScalingFallingPlatform::VOnResourceAcquire ()
{

	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjScalingFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();


}
void CGCObjScalingFallingPlatform::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	m_bContactWithPlayer = false;
	m_bCanDelete = false;
	m_fCurrentDestroyPlatformTick = m_fMaxDestroyPlatformTick;

	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (0.0f, 0.0f));
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
		m_v2CurrentPos = GetPhysicsBody ()->GetPosition ();
	}
}

//Calls the function that moves the platform down
void CGCObjScalingFallingPlatform::MoveDownOnContact ()
{
	//if this boolean gets set to true it starts decreasing the platform tick 
	//and changes the velocity of the platform so it moves down
	if (GetContactWithPlayer () == true)	
	{
		//SetVelocity (m_v2FallingVelocity);

		if (m_fCurrentDestroyPlatformTick >= 0)
		{
			m_fCurrentDestroyPlatformTick--;
			SetSpritePosition (cocos2d::Vec2 (GetSpritePosition ().x, GetSpritePosition ().y -3.0f));
		}

		if (m_fCurrentDestroyPlatformTick <= 0)
		{
			m_bCanDelete = true;
		}
	}
	else  // changes the velocity to 0 so it stops moving
	{
		//SetVelocity (m_v2DefaultVelocity);
	}
}

void CGCObjScalingFallingPlatform::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
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
//update function
void CGCObjScalingFallingPlatform::VOnUpdate (f32 fTimestep)
{
	MoveDownOnContact ();
}

