#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTravelatorPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_staticBody, true); //file path and physics body for the travelator

//void CGCObjTravelatorPlatform::VOnResourceAcquire()
//{
//
//	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTravelatorPlatform);
//
//	CGCObjSpritePhysics::VOnResourceAcquire();
//	
//	//SetResetPosition(GetStartPos()); //Start position
//	
//	//cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
//
//}


//
//void CGCObjTravelatorPlatform::VOnReset()
//{
//	CGCObjSpritePhysics::VOnReset();//Reset
//	
//	//SetResetPosition(GetStartPos()); //start position
//	
//	if (GetPhysicsBody())
//	{
//		cocos2d::Vec2 v2SpritePos = GetSpritePosition(); //gets sprite current position
//		
//		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f); //set position of the sprite
//		
//		GetPhysicsBody()->SetFixedRotation(true);
//	}
//
//}
void CGCObjTravelatorPlatform::VOnUpdate(f32 fTimestep)
{
}
//
//void CGCObjTravelatorPlatform::VOnResourceRelease()
//{
//	CGCObjSpritePhysics::VOnResourceRelease();
//
//}
//void CGCObjTravelatorPlatform::VOnResurrected()
//{
//	CGCObjSpritePhysics::VOnResurrected();
//
//}





