#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjScalingFallingPlatform.h"



CGCObjScalingFallingPlatform::CGCObjScalingFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingFallingPlatform))
	, m_v2FallingVelocity (0.0f, -1.0f)									  //Initalises the variable with a default value
	, m_v2DefaultVelocity (0.0f, 0.0f)									  //Initalises the variable with a default value
	, m_bContactWithPlayer (false)										  //Initalises the variable with a default value
	, m_fDestroyPlatformTick (120.0f)									  //Initalises the variable with a default value
	, m_bCanDelete (false)												  //Initalises the variable with a default value
{																		 
}																		 

//Sets the sprite
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingFallingPlatform, "TexturePacker/Sprites/FallingScalingPlatform/FallingScalingPlatform.plist", "FallingScalingPlatform", b2_kinematicBody, true);

void CGCObjScalingFallingPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjScalingFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();

}

//Calls the function that moves the platform down
void CGCObjScalingFallingPlatform::MoveDownOnContact ()
{
	if (GetContactWithPlayer () == true)	//if this boolean gets set to true it starts decreasing the platform tick and changes the velocity of the platform so it moves down
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
	else  // changes the velocity to 0 so it stops moving
	{
		SetVelocity (m_v2DefaultVelocity);
	}
}
//update function
void CGCObjScalingFallingPlatform::VOnUpdate (f32 fTimestep)
{
	MoveDownOnContact ();
}

