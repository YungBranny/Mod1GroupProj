#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCOFallingPlane12.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS	( CGCObjFallingPlane12 );

CGCObjFallingPlane12::CGCObjFallingPlane12()
	: CGCObjSpritePhysics ( GetGCTypeIDOf ( CGCObjFallingPlane ) )
	, m_bJustCollided		  ( false ) // Default Key collision set to False
	, m_v2MoveUpVelocity	  ( cocos2d::Vec2 ( 0.0f, 7.0f ) ) // Sets up movement velocity
	, m_v2MoveDownVelocity	  ( -m_v2MoveUpVelocity ) // Sets down movement by calling up velocity and switching direction
	, m_iCollisionBuffer	  ( 60 ) // Sets default collision buffer to 60
	, m_pCustomCreationParams ( nullptr )
{
	InitialiseMovementDirection();
}

void CGCObjFallingPlane12::InitialiseMovementDirection()
{
		m_eMoveDirection = EMoveDirection::Down; // Initialises movement
}

void CGCObjFallingPlane12::VOnResourceAcquire()
{
	CGCObjSpritePhysics::VOnResourceAcquire();

	if( nullptr != m_pCustomCreationParams.get() )
	{
		m_pCustomCreationParams.reset(nullptr);
	}
}

void CGCObjFallingPlane12::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();
	m_v2StartPosition = GetPhysicsBody()->GetPosition(); // Setting start position
	GetPhysicsBody()->SetGravityScale(0.0f); // Sets Gravity
}

void CGCObjFallingPlane12::SettingVelocity()
{
	switch( m_eMoveDirection )
	{
	case EMoveDirection::Down:
	{
		this->SetVelocity(m_v2MoveDownVelocity); // Applying velocity
	}
	break;
	}
}

void CGCObjFallingPlane12::ResetPosition() // Resets Planes position back to start position when this function is collided on collision
{
	GetPhysicsBody()->SetTransform(getStartPosition(), 0);
}

void CGCObjFallingPlane12::CollisionChecker()
{
	// Default Collision is False until collided with, this stops collision being called multiple times. First check to see if collision buffer 
    // is set to True and if so, buffer will countdown to 0 then will be set back to the default False until collided with again
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

// This enables the parameters to be handled in Ogmo level editor
void CGCObjFallingPlane12::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if( nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData )
	{
		const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("PlistFile");

		const tinyxml2::XMLAttribute* pCustomShape = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("shape");

		if( ( nullptr != pCustomPlistPath ) && ( 0 != strlen(pCustomPlistPath->Value()) ) )
		{
			    m_pCustomCreationParams = std::make_unique< CGCFactoryCreationParams >(rCreationParams.strClassName.c_str(),
				pCustomPlistPath->Value(),
				pCustomShape->Value(),
				rCreationParams.eB2dBody_BodyType,
				rCreationParams.bB2dBody_FixedRotation);

			pParamsToPassToBaseClass = m_pCustomCreationParams.get();
		}
	}
	CGCObjSpritePhysics::VHandleFactoryParams(( *pParamsToPassToBaseClass ), v2InitialPosition);
}

void CGCObjFallingPlane12::VOnUpdate(f32 fTimeStep)
{
	SettingVelocity(); // Updates SettingVelocity
	CollisionChecker(); // Updates CollisionChecker
}