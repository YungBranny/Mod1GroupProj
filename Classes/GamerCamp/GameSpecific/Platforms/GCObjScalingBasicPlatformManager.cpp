#include "GCObjScalingBasicPlatformManager.h"

#include <string.h>


#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingBasicPlatform.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h" 





CGCObjScalingBasicPlatformManager::CGCObjScalingBasicPlatformManager ()
	: m_fStartX (100)			   //Default values for the variables
	, m_fStartY (500)			   //Default values for the variables
	, m_fSpacingX (60)			   //Default values for the variables
	, m_iMaxPlatforms (10)		   //Default values for the variables
{	

}

CGCObjScalingBasicPlatformManager::~CGCObjScalingBasicPlatformManager ()
{}



bool CGCObjScalingBasicPlatformManager::VHandlesThisTypeId (GCTypeID idQueryType)
{
	return( GetGCTypeIDOf (CGCObjScalingBasicPlatform) == idQueryType );
}



GCTypeID CGCObjScalingBasicPlatformManager::VGetTypeId ()
{
	return GetGCTypeIDOf (CGCObjScalingBasicPlatformManager);
}



void CGCObjScalingBasicPlatformManager::VOnGroupResourceAcquire ()
{
	CreatePlatforms ();
	CGCObjectGroup::VOnGroupResourceAcquire ();
}



void CGCObjScalingBasicPlatformManager::VOnGroupResourceAcquire_PostObject ()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject ();
}


void CGCObjScalingBasicPlatformManager::VOnGroupReset ()
{
	CGCObjectGroup::VOnGroupReset ();
}

void CGCObjScalingBasicPlatformManager::VOnObjectReset ()
{
	CGCObjectGroup::VOnObjectReset ();
}




void CGCObjScalingBasicPlatformManager::VOnGroupUpdate (f32 fTimeStep)
{
	CGCObjectGroup::VOnGroupUpdate (fTimeStep);
}



void CGCObjScalingBasicPlatformManager::VOnGroupResourceRelease ()
{
	CGCObjectGroup::VOnGroupResourceRelease ();
	DestroyPlatforms ();
}

//creates a forloop which loops for the amount of platforms being made and
//draws each platform changing the position of each one on the x axis by the varible spacingX
void CGCObjScalingBasicPlatformManager::CreatePlatforms ()
{
	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop)
	{
		m_v2PlatformStartPos = cocos2d::Vec2(m_fStartX, m_fStartY);
		CGCObjScalingBasicPlatform* pPlatform = new CGCObjScalingBasicPlatform ();
		pPlatform->SetResetPosition (m_v2PlatformStartPos);
		m_fStartX += m_fSpacingX;
	}
}

void CGCObjScalingBasicPlatformManager::DestroyPlatforms ()
{
	DestroyObjectsReverseOrder ([&](CGCObject* pObject)
		{
			GCASSERT (GetGCTypeIDOf (CGCObjScalingBasicPlatform) == pObject->GetGCTypeID (), "wrong type!");
		});
}
