#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"



#include "GCOFallingPlane2.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjFallingPlane2);

CGCObjFallingPlane2::CGCObjFallingPlane2()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjFallingPlane))
	, m_bMoveUpAndDown(false)
	, m_bJustCollided(false)
	, m_v2EndPosition(500, 110)
	, m_v2MoveUpVelocity(cocos2d::Vec2(0.0f, 3.0f))
	, m_v2MoveDownVelocity(-m_v2MoveUpVelocity)
	, m_iCollisionBuffer(60)
	, m_pCustomCreationParams(nullptr)
{
	InitialiseMovementDirection();
}

void CGCObjFallingPlane2::InitialiseMovementDirection()
{
	m_eMoveDirection = EMoveDirection::Down;
}

void CGCObjFallingPlane2::VOnResourceAcquire()
{

	CGCObjSpritePhysics::VOnResourceAcquire();


	if( nullptr != m_pCustomCreationParams.get() )
	{
		m_pCustomCreationParams.reset(nullptr);
	}
}

void CGCObjFallingPlane2::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();
	m_v2StartPosition = GetPhysicsBody()->GetPosition();
	GetPhysicsBody()->SetGravityScale(0.0f);
}


void CGCObjFallingPlane2::SettingVelocity()
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

void CGCObjFallingPlane2::ResetPosition()
{
	GetPhysicsBody()->SetTransform(getStartPosition(), 0);
}

void CGCObjFallingPlane2::CollisionChecker()
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

void CGCObjFallingPlane2::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if( nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData )
	{


		const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("PlistFile");    //customplist    //PlistFile

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

void CGCObjFallingPlane2::VOnUpdate(f32 fTimeStep)
{
	SettingVelocity();
	CollisionChecker();
}