#include "GCObjScalingFallingPlatformManager.h"

#include <string.h>


#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingFallingPlatform.h"

#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h" 





CGCObjScalingFallingPlatformManager::CGCObjScalingFallingPlatformManager ()
	: m_fStartX (100)			//Default values for the variables
	, m_fStartY (500)			//Default values for the variables
	, m_fSpacingX (60)			//Default values for the variables
	, m_iMaxPlatforms (10)		//Default values for the variables
{

}

CGCObjScalingFallingPlatformManager::~CGCObjScalingFallingPlatformManager ()
{}


bool CGCObjScalingFallingPlatformManager::VHandlesThisTypeId (GCTypeID idQueryType) //Handles the typeid for the scaling platform
{
	return( GetGCTypeIDOf (CGCObjScalingFallingPlatformManager) == idQueryType );
}


GCTypeID CGCObjScalingFallingPlatformManager::VGetTypeId ()  
{
	return GetGCTypeIDOf (CGCObjScalingFallingPlatformManager);
}


void CGCObjScalingFallingPlatformManager::VOnGroupResourceAcquire ()
{
	CreatePlatforms (); //calls create platform on resourceacquire
	CGCObjectGroup::VOnGroupResourceAcquire ();
}


void CGCObjScalingFallingPlatformManager::VOnGroupResourceAcquire_PostObject ()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject ();
}


void CGCObjScalingFallingPlatformManager::VOnGroupReset ()
{
	CGCObjectGroup::VOnGroupReset ();
}

void CGCObjScalingFallingPlatformManager::VOnObjectReset ()
{
	CGCObjectGroup::VOnObjectReset ();
}

void CGCObjScalingFallingPlatformManager::VOnGroupUpdate (f32 fTimeStep)
{
	CGCObjectGroup::VOnGroupUpdate (fTimeStep);
	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop) //loops for the amount of platforms made and calls the update function for each one
	{
		m_pcGCScalingFallingPlatform[ iLoop ].VOnUpdate (fTimeStep);
	}
}

void CGCObjScalingFallingPlatformManager::VOnGroupResourceRelease ()
{
	CGCObjectGroup::VOnGroupResourceRelease ();
	DestroyPlatforms ();
}

//creates a forloop which loops for the amount of platforms being made and draws each platform changing the position of each one on the x axis by the varible spacingX
void CGCObjScalingFallingPlatformManager::CreatePlatforms () 
{
	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop) 
	{
		m_v2PlatformStartPos = cocos2d::Vec2 (m_fStartX, m_fStartY);
		m_pcGCScalingFallingPlatform = new CGCObjScalingFallingPlatform[ m_iMaxPlatforms ];
		m_pcGCScalingFallingPlatform[iLoop].SetResetPosition (m_v2PlatformStartPos);
		m_fStartX += m_fSpacingX;
	}
}

void CGCObjScalingFallingPlatformManager::DestroyPlatforms ()
{
	DestroyObjectsReverseOrder ([&](CGCObject* pObject)
		{
			GCASSERT (GetGCTypeIDOf (CGCObjScalingFallingPlatform) == pObject->GetGCTypeID (), "wrong type!");
		});
}
