#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjFallingPlatform.h"





CGCObjFallingPlatform::CGCObjFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjFallingPlatform))
	, m_v2StartPos			(400, 400)									  //Initalises the variable with a default value
	, m_v2FallingVelocity	(0.0f, -10.0f)								  //Initalises the variable with a default value
	, m_v2DefaultVelocity	(0.0f, 0.0f)								  //Initalises the variable with a default value
	, m_bContactWithPlayer	(false)										  //Initalises the variable with a default value
	, m_fDestroyPlatformTick(120.0f)									  //Initalises the variable with a default value
	, m_bCanDelete			(false)										  //Initalises the variable with a default value
	, m_v2EndPos			(m_v2StartPos.x, m_v2StartPos.y - ( -1.0f ))  //Initalises the variable with a default value
{
	SetResetPosition (GetStartPos ()); // sets the reset position to be the start position
}



//sets the sprite 
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjFallingPlatform, "TexturePacker/Sprites/LongPlatformTest/LongPlatformTest.plist", "LongPlatformTest", b2_dynamicBody, true);
void CGCObjFallingPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
	SetResetPosition (GetStartPos ());
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
}


//default sprite physics 
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

//Calls the function that moves the platform down
void CGCObjFallingPlatform::MoveDownOnContact ()
{
	if (GetContactWithPlayer() == true) //if this boolean gets set to true it starts decreasing the platform tick and changes the velocity of the platform so it moves down
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
	else // changes the velocity to 0 so it stops moving
	{
		SetVelocity (m_v2DefaultVelocity);
	}
}

void CGCObjFallingPlatform::VOnUpdate (f32 fTimestep) //update function
{
   MoveDownOnContact ();
}

//standard spritephysics functions
void CGCObjFallingPlatform::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();
}

void CGCObjFallingPlatform::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (0.0f);
}





