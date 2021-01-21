#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"

#include "GCObjCCCrumblingPlatform.h"

#include "../../GCCocosInterface/GB2ShapeCache-x.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCObjCCCrumblingPlatform);


CGCObjCCCrumblingPlatform::CGCObjCCCrumblingPlatform () //constructor 
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
void CGCObjCCCrumblingPlatform::VOnResourceAcquire () //acquires the resources 
{
	CGCObjSpritePhysics::VOnResourceAcquire ();

		CGCObjSpritePhysics::VOnResourceAcquire (); 
		const char* pszAnim_Idle = "CCIdle"; // gets the folder name the animation is stored in 

		cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile); //creates a valuemap from the plist given in ogmo
		RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_Idle))); //runs the animation
}
void CGCObjCCCrumblingPlatform::VOnReset () //reset function
{
	CGCObjSpritePhysics::VOnReset ();
	m_bContactWithPlayer = false;									  //Resets to the default state 
	m_bCanDelete = false;											  //Resets to the default state 
	m_fCurrentDestroyPlatformTick = m_fMaxDestroyPlatformTick;		  //Resets to the default state 

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
void CGCObjCCCrumblingPlatform::MoveDownOnContact ()
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
	else  // Else statement which is emtpy so that the platform should do nothing when its not being touched byt the player
	{
		
	}
}

//function that allowes the custom 
void CGCObjCCCrumblingPlatform::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
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
void CGCObjCCCrumblingPlatform::VOnUpdate (f32 fTimestep)
{
	MoveDownOnContact ();
}

