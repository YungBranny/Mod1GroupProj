#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjFallingPlatform.h"





CGCObjFallingPlatform::CGCObjFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjFallingPlatform))
	, m_v2StartPos			(400, 400)										
	, m_v2FallingVelocity	(0.0f, -10.0f)
	, m_v2DefaultVelocity	(0.0f, 0.0f)
	, m_bContactWithPlayer	(false)
	, m_fDestroyPlatformTick(120.0f)
	, m_bCanDelete			(false)
	, m_v2EndPos			(m_v2StartPos.x, m_v2StartPos.y - ( -1.0f ))
{
	SetResetPosition (GetStartPos ());
}




IN_CPP_CREATION_PARAMS_DECLARE (CGCObjFallingPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_dynamicBody, true);
void CGCObjFallingPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
}



void CGCObjFallingPlatform::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (GetStartPos ());
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}
void CGCObjFallingPlatform::MoveDownOnContact ()
{
	if (GetContactWithPlayer() == true)
	{
		SetVelocity (m_v2FallingVelocity);

		if (m_fDestroyPlatformTick >= 0)
		{
			m_fDestroyPlatformTick--;
		}

		if (m_fDestroyPlatformTick <= 0)
		{
			m_bCanDelete = true;
		}
	}
	else
	{
		SetVelocity (m_v2DefaultVelocity);
	}
}

void CGCObjFallingPlatform::VOnUpdate (f32 fTimestep)
{
   MoveDownOnContact ();
}

void CGCObjFallingPlatform::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();
}

void CGCObjFallingPlatform::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0.0f);
}





