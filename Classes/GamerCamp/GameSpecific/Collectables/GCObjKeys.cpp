#include "GCObjKeys.h"

#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif

#ifndef TINYXML2_INCLUDED
#include "external\tinyxml2\tinyxml2.h"
#endif

GCFACTORY_IMPLEMENT_CREATEABLECLASS ( CGCObjKeys );

CGCObjKeys::CGCObjKeys ( void )
	: CGCObjSpritePhysics ( GetGCTypeIDOf(CGCObjKeys) )
	, m_bJustCollided			(	false	)
	, m_iCollisionBuffer		(	 60		)
	, m_pCustomCreationParams	(  nullptr  )
{

}

CGCObjKeys::~CGCObjKeys()
{

}

void CGCObjKeys::VOnResourceAcquire ( void )
{
	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszPlist_Key = "TexturePacker/Sprites/Key/cc_collectible_key.plist";
	const char* pszAnim_Key = "KeyIdle";

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_Key)));
}

void CGCObjKeys::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)  // This enables the parameters to be handled in ogmo level editor
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

void CGCObjKeys::CollisionChecker()
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

void CGCObjKeys::VOnUpdate ( f32 fTimestep )
{
	CollisionChecker(); // Updates CollisionChecker
}