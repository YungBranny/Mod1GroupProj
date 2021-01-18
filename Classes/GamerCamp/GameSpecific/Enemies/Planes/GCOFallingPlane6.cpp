#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCOFallingPlane6.h"

GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjFallingPlane6);

CGCObjFallingPlane6::CGCObjFallingPlane6()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjFallingPlane))
	, m_bMoveUpAndDown(false)
	, m_bJustCollided(false)
	, m_v2EndPosition(500, 110)
	, m_v2MoveUpVelocity(cocos2d::Vec2(0.0f, 7.0f))
	, m_v2MoveDownVelocity(-m_v2MoveUpVelocity)
	, m_iCollisionBuffer(60)
	, m_pCustomCreationParams(nullptr)
{
	InitialiseMovementDirection();
}

void CGCObjFallingPlane6::InitialiseMovementDirection()
{
	//if( m_bMoveUpAndDown == true ) // If default bool is set to 'true', then the platform may go Right and in the opposite direction, which is Left. This may be used for future levels
	//{
	m_eMoveDirection = EMoveDirection::Down;
	//}
	//else if( m_bMoveUpAndDown == false ) // The default 'm_bMoveUpAndDown' bool is set to 'false', therefore platform can only go up and in the opposite direction, which is down
	//{
	//	m_eMoveDirection = EMoveDirection::Up;
	//};
}

// Create the Platform Sprite, give it a Kinematic Physics Body which means it only moves when code tells it too and then set fixed rotation to 'True'
//IN_CPP_CREATION_PARAMS_DECLARE( CGCObjMovingPlatform, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_kinematicBody, true );
void CGCObjFallingPlane6::VOnResourceAcquire()
{
	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE ( CGCObjMovingPlatform );

	CGCObjSpritePhysics::VOnResourceAcquire();

	//m_v2StartPosition = GetPhysicsBody()->GetPosition();

	if( nullptr != m_pCustomCreationParams.get() )
	{
		m_pCustomCreationParams.reset(nullptr);
	}
}

void CGCObjFallingPlane6::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();
	m_v2StartPosition = GetPhysicsBody()->GetPosition();
	GetPhysicsBody()->SetGravityScale(0.0f);
}

void CGCObjFallingPlane6::SettingVelocity()
{
	// Here is Velocity set for each Direction
	switch( m_eMoveDirection )
	{
	case EMoveDirection::Down:
	{
		this->SetVelocity(m_v2MoveDownVelocity);
	}
	break;
	}
}

void CGCObjFallingPlane6::ResetPosition()
{
	GetPhysicsBody()->SetTransform(getStartPosition(), 0);
}

void CGCObjFallingPlane6::CollisionChecker()
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

void CGCObjFallingPlane6::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if( nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData )
	{
		//const tinyxml2::XMLAttribute* pName = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute( "name" );

		//CCLOG( (nullptr == pName) ? "BOB NOT FOUND!" : pName->Value() );

		const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("PlistFile");    //customplist    //PlistFile

		const tinyxml2::XMLAttribute* pCustomShape = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("shape");

		if( ( nullptr != pCustomPlistPath ) && ( 0 != strlen(pCustomPlistPath->Value()) ) )    // && ( (nullptr != pCustomShape) && ( 0 != strlen( pCustomShape->Value() ) ) ) )
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

void CGCObjFallingPlane6::VOnUpdate(f32 fTimeStep)
{
	SettingVelocity();
	CollisionChecker();
}