#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjTravelatorPlatform.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjTravelatorPlatform);

CGCObjTravelatorPlatform::CGCObjTravelatorPlatform()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjTravelatorPlatform))
	//, m_v2StartPos	(600, 600)  // Start position
	, m_fVelocity	(-25.0f ) //Speed and direction the player is sent in
	, m_pCustomCreationParams(nullptr)
{
	//SetResetPosition(GetStartPos()); //reset position
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//What this call does in the main game layer (i.e its functionality)

//GetCollisionManager().AddCollisionHandler
//(
//	[]
//(CGCObjPlayer& rcPlayer, CGCObjTravelatorPlatform& rcTravelatorPlatform, const b2Contact& rcContact) -> void
//	{
//		if (rcContact.IsTouching())
//		{
//			rcPlayer.setOnTravelator(true);
//
//			rcPlayer.SetCanJump(true);
//
//			rcPlayer.SetVelocity(rcTravelatorPlatform.getVelocity());
//		}
//		else if (rcContact.IsTouching() == false)
//		{
//			rcPlayer.setOnTravelator(false);
//
//			rcPlayer.SetCanJump(false);
//		}
//	}
//);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///This below is the code used to create multiple instances of and object with the same class/ provided by alex darby
void CGCObjTravelatorPlatform::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition)
{
    const CGCFactoryCreationParams* pParamsToPassToBaseClass = &rCreationParams;

    if (nullptr != CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData)
    {
       
        const tinyxml2::XMLAttribute* pCustomPlistPath = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("PlistFile");    //customplist    //PlistFile

        const tinyxml2::XMLAttribute* pCustomShape = CGCLevelLoader_Ogmo::sm_pCurrentObjectXmlData->FindAttribute("shape");

        if ((nullptr != pCustomPlistPath) && (0 != strlen(pCustomPlistPath->Value())))    // && ( (nullptr != pCustomShape) && ( 0 != strlen( pCustomShape->Value() ) ) ) )
        {
            m_pCustomCreationParams = std::make_unique< CGCFactoryCreationParams >(rCreationParams.strClassName.c_str(),
                pCustomPlistPath->Value(),
                pCustomShape->Value(),
                rCreationParams.eB2dBody_BodyType,
                rCreationParams.bB2dBody_FixedRotation);

            pParamsToPassToBaseClass = m_pCustomCreationParams.get();
        }
    }

    CGCObjSpritePhysics::VHandleFactoryParams((*pParamsToPassToBaseClass), v2InitialPosition);
}


void CGCObjTravelatorPlatform::VOnUpdate(f32 fTimestep)
{
}






