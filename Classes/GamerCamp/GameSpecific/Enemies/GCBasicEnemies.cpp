#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/Core/GCTypes.h"
#include "AppDelegate.h"



#include "GCBasicEnemies.h"

#ifndef TINYXML2_INCLUDED
#include "external\tinyxml2\tinyxml2.h"
#endif

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif


USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS (CGCBasicEnemies);

CGCBasicEnemies::CGCBasicEnemies() 
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
{
	
}

void CGCBasicEnemies::VOnResourceAcquire() //resource acquire function 
{
	CGCObjSpritePhysics::VOnResourceAcquire ();
	const char* pszPlist_SeaUrchin = "TexturePacker/Sprites/SeaUrchin/SeaUrchin.plist"; // gets the plist file for the sea urchin
	const char* pszAnim_Idle = "UrchinIdle"; //finds the animation frames for the sea urchin

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist( GetFactoryCreationParams()->strPlistFile ); //gets a plist from the files given in ogmo
	RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( dicPList, pszAnim_Idle ) ) ); //runs the idle animation


	

}

void CGCBasicEnemies::VOnReset()  //reset function
{
	CGCObjSpritePhysics::VOnReset();
}
void CGCBasicEnemies::VOnUpdate(f32 fTimestep) //update function which is needed to make the animation update
{
	CGCObjSpritePhysics::VOnUpdate (fTimestep);
}

void CGCBasicEnemies::VOnResourceRelease() //release function
{
	CGCObjSpritePhysics::VOnResourceRelease();
	if (nullptr != m_pCustomCreationParams.get ())
	{
		m_pCustomCreationParams.reset (nullptr);
	}
}
void CGCBasicEnemies::VOnResurrected() //resurrected function 
{
	CGCObjSpritePhysics::VOnResurrected ();
}

void CGCBasicEnemies::VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition) //this enables the parameters to be handled in ogmo level editor
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




