#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjTravelatorPlatform.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGCObjTravelatorPlatform::CGCObjTravelatorPlatform()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjTravelatorPlatform))
	, m_v2StartPos	(600, 600)  // Start position
	, m_v2Velocity	(-8.0f, 0.0f ) //Speed and direction the player is sent in 
{
	SetResetPosition(GetStartPos()); //reset position
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTravelatorPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_staticBody, true); //file path and physics body for the travelator

void CGCObjTravelatorPlatform::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTravelatorPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire();
	
	SetResetPosition(GetStartPos()); //Start position
	
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);

}



void CGCObjTravelatorPlatform::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();//Reset
	
	SetResetPosition(GetStartPos()); //start position
	
	if (GetPhysicsBody())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition(); //gets sprite current position
		
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f); //set position of the sprite
		
		GetPhysicsBody()->SetFixedRotation(true);
	}

}
void CGCObjTravelatorPlatform::VOnUpdate(f32 fTimestep)
{
}

void CGCObjTravelatorPlatform::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}
void CGCObjTravelatorPlatform::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();

}





