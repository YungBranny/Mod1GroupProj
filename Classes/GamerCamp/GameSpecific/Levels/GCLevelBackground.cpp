#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GamerCamp/Core/GCTypes.h"

#include "GCLevelBackground.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCLevelBackground);

CGCLevelBackground::CGCLevelBackground()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCLevelBackground))
{

}

void CGCLevelBackground::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
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