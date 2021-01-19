#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjTCRCrumblingPlatform.h"

#include "../../GCCocosInterface/GB2ShapeCache-x.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjTCRCrumblingPlatform);


CGCObjTCRCrumblingPlatform::CGCObjTCRCrumblingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingFallingPlatform))
	, m_v2FallingVelocity (0.0f, -1.0f)									  //Initalises the variable with a default value
	, m_v2DefaultVelocity (0.0f, 0.0f)									  //Initalises the variable with a default value
	, m_bContactWithPlayer (false)										  //Initalises the variable with a default value
	, m_fMaxDestroyPlatformTick (60.0f)
	, m_fCurrentDestroyPlatformTick (m_fMaxDestroyPlatformTick)
	, m_bCanDelete (false)		//Initalises the variable with a default value

{
}

void CGCObjTCRCrumblingPlatform::VOnResourceAcquire ()
{
	CGCObjSpritePhysics::VOnResourceAcquire ();
	CGCObjSpritePhysics::VOnResourceAcquire ();
	const char* pszAnim_Idle = "TCRIdle";

	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_Idle)));
}
void CGCObjTCRCrumblingPlatform::VOnReset ()
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
void CGCObjTCRCrumblingPlatform::MoveDownOnContact ()
{
	//if this boolean gets set to true it starts decreasing the platform tick 
	//and changes the velocity of the platform so it moves down
	if (GetContactWithPlayer () == true)
	{
		if (m_fCurrentDestroyPlatformTick >= 0)
		{
			m_fCurrentDestroyPlatformTick--;
			SetSpritePosition (cocos2d::Vec2 (GetSpritePosition ().x, GetSpritePosition ().y - 3.0f));
		}

		if (m_fCurrentDestroyPlatformTick <= 0)
		{
			m_bCanDelete = true;
		}
	}
	else  // changes the velocity to 0 so it stops moving
	{
	}
}

void CGCObjTCRCrumblingPlatform::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if (nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData)
	{
		const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute ("PlistFile");    //customplist    //PlistFile

		const tinyxml2::XMLAttribute* pCustomShape = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute ("shape");

		if (( nullptr != pCustomPlistPath ) && ( 0 != strlen (pCustomPlistPath->Value ()) )) 
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
void CGCObjTCRCrumblingPlatform::VOnUpdate (f32 fTimestep)
{
	MoveDownOnContact ();
}

