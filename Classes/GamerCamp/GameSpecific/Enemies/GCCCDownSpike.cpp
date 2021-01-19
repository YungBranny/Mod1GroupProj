#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/Core/GCTypes.h"
#include "AppDelegate.h"



#include "GCCCDownSpike.h"

#ifndef TINYXML2_INCLUDED
#include "external\tinyxml2\tinyxml2.h"
#endif

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif


USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCCCDownSpike);

CGCCCDownSpike::CGCCCDownSpike () //contstructor 
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
{
}

void CGCCCDownSpike::VOnResourceAcquire ()
{
	CGCObjSpritePhysics::VOnResourceAcquire ();
	const char* pszAnim_Idle = "CCDownSpike";

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_Idle)));

}

void CGCCCDownSpike::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
}
void CGCCCDownSpike::VOnUpdate (f32 fTimestep)
{
	CGCObjSpritePhysics::VOnUpdate (fTimestep);
}

void CGCCCDownSpike::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();
	if (nullptr != m_pCustomCreationParams.get ())
	{
		m_pCustomCreationParams.reset (nullptr);
	}
}
void CGCCCDownSpike::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
}

void CGCCCDownSpike::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
	const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

	if (nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData)
	{
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




