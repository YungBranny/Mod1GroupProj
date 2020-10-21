#include "GCObjScalingFallingPlatformManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>


#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/PlatformTest/GCObjScalingFallingPlatform.h"

#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h" 





CGCObjScalingFallingPlatformManager::CGCObjScalingFallingPlatformManager ()
	: m_fStartX (100)
	, m_fStartY (500)
	, m_fSpacingX (60)
	, m_iMaxPlatforms (10)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjScalingFallingPlatformManager::~CGCObjScalingFallingPlatformManager ()
{}



//////////////////////////////////////////////////////////////////////////
// only handle invaders
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjScalingFallingPlatformManager::VHandlesThisTypeId (GCTypeID idQueryType)
{
	return( GetGCTypeIDOf (CGCObjScalingFallingPlatformManager) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjScalingFallingPlatformManager::VGetTypeId ()
{
	return GetGCTypeIDOf (CGCObjScalingFallingPlatformManager);
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingFallingPlatformManager::VOnGroupResourceAcquire ()
{
	CreatePlatforms ();
	CGCObjectGroup::VOnGroupResourceAcquire ();
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingFallingPlatformManager::VOnGroupResourceAcquire_PostObject ()
{
	// we do this here because the alternative is to do it for each invader as they're created and it's

	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject ();

}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingFallingPlatformManager::VOnGroupReset ()
{
	CGCObjectGroup::VOnGroupReset ();

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingFallingPlatformManager::VOnObjectReset ()
{
	CGCObjectGroup::VOnObjectReset ();

}



//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingFallingPlatformManager::VOnGroupUpdate (f32 fTimeStep)
{
	CGCObjectGroup::VOnGroupUpdate (fTimeStep);
	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop)
	{
		m_pcGCScalingFallingPlatform[ iLoop ].VOnUpdate (fTimeStep);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingFallingPlatformManager::VOnGroupResourceRelease ()
{
	// N.B. need to do this first as it clears internal lists
	CGCObjectGroup::VOnGroupResourceRelease ();
	DestroyPlatforms ();
}




//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjScalingFallingPlatformManager::CreatePlatforms ()
{
	

	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop)
	{
		m_v2PlatformStartPos = cocos2d::Vec2 (m_fStartX, m_fStartY);
		// n.b. these register themselves with this class on creation
		m_pcGCScalingFallingPlatform = new CGCObjScalingFallingPlatform[ m_iMaxPlatforms ];
		m_pcGCScalingFallingPlatform[iLoop].SetResetPosition (m_v2PlatformStartPos);
		m_fStartX += m_fSpacingX;

	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjScalingFallingPlatformManager::DestroyPlatforms ()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder ([&](CGCObject* pObject)
		{
			// do nothing - DestroyObjectsReverseOrder calls delete!
			GCASSERT (GetGCTypeIDOf (CGCObjScalingFallingPlatform) == pObject->GetGCTypeID (), "wrong type!");
		});
}
