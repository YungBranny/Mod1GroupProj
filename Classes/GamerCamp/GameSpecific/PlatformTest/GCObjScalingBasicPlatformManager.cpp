#include "GCObjScalingBasicPlatformManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>


#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/PlatformTest/GCObjScalingBasicPlatform.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h" 





CGCObjScalingBasicPlatformManager::CGCObjScalingBasicPlatformManager ()
	: m_fStartX (100)
	, m_fStartY (500)
	, m_fSpacingX(60)
	, m_iMaxPlatforms(10)
{	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjScalingBasicPlatformManager::~CGCObjScalingBasicPlatformManager ()
{}



//////////////////////////////////////////////////////////////////////////
// only handle invaders
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjScalingBasicPlatformManager::VHandlesThisTypeId (GCTypeID idQueryType)
{
	return( GetGCTypeIDOf (CGCObjScalingBasicPlatform) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjScalingBasicPlatformManager::VGetTypeId ()
{
	return GetGCTypeIDOf (CGCObjScalingBasicPlatformManager);
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingBasicPlatformManager::VOnGroupResourceAcquire ()
{
	CreatePlatforms ();
	CGCObjectGroup::VOnGroupResourceAcquire ();
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingBasicPlatformManager::VOnGroupResourceAcquire_PostObject ()
{
	// we do this here because the alternative is to do it for each invader as they're created and it's

	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject ();

}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingBasicPlatformManager::VOnGroupReset ()
{
	CGCObjectGroup::VOnGroupReset ();

}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingBasicPlatformManager::VOnObjectReset ()
{
	CGCObjectGroup::VOnObjectReset ();

}



//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjScalingBasicPlatformManager::VOnGroupUpdate (f32 fTimeStep)
{
	CGCObjectGroup::VOnGroupUpdate (fTimeStep);
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScalingBasicPlatformManager::VOnGroupResourceRelease ()
{
	// N.B. need to do this first as it clears internal lists
	CGCObjectGroup::VOnGroupResourceRelease ();
	DestroyPlatforms ();
}




//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjScalingBasicPlatformManager::CreatePlatforms ()
{
	for (i32 iLoop = 0; iLoop < m_iMaxPlatforms; ++iLoop)
	{
		m_v2PlatformStartPos = cocos2d::Vec2(m_fStartX, m_fStartY);
		// n.b. these register themselves with this class on creation
		CGCObjScalingBasicPlatform* pPlatform = new CGCObjScalingBasicPlatform ();
		pPlatform->SetResetPosition (m_v2PlatformStartPos);
		m_fStartX += m_fSpacingX;
	
	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjScalingBasicPlatformManager::DestroyPlatforms ()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder ([&](CGCObject* pObject)
		{
			// do nothing - DestroyObjectsReverseOrder calls delete!
			GCASSERT (GetGCTypeIDOf (CGCObjScalingBasicPlatform) == pObject->GetGCTypeID (), "wrong type!");
		});
}
