

#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjScalingFallingPlatform.h"



CGCObjScalingFallingPlatform::CGCObjScalingFallingPlatform ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjScalingFallingPlatform))
	, m_v2FallingVelocity (0.0f, -1.0f)
	, m_v2DefaultVelocity (0.0f, 0.0f)
	, m_bContactWithPlayer (false)
	, m_fDestroyPlatformTick (120.0f)
	, m_bCanDelete (false)
{
}

IN_CPP_CREATION_PARAMS_DECLARE (CGCObjScalingFallingPlatform, "TexturePacker/Sprites/FallingScalingPlatform/FallingScalingPlatform.plist", "FallingScalingPlatform", b2_dynamicBody, true);

void CGCObjScalingFallingPlatform::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjScalingFallingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire ();
}


void CGCObjScalingFallingPlatform::MoveDownOnContact ()
{
	if (GetContactWithPlayer () == true)
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


void CGCObjScalingFallingPlatform::VOnUpdate (f32 fTimestep)
{
	MoveDownOnContact ();
}

