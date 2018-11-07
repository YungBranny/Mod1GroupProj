////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjGroupPlatform::CGCObjGroupPlatform()
{
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupPlatform::~CGCObjGroupPlatform()
{}



//////////////////////////////////////////////////////////////////////////
// only handle platforms
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupPlatform::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf( CGCObjPlatform ) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupPlatform::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupPlatform );
}



//////////////////////////////////////////////////////////////////////////
// invaders are created from level file, we just need to init their anims
// this has to be done after the invaders have acquired their resources
// hence the name of this function..
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupPlatform::VOnGroupResourceAcquire_PostObject( void )
{
	if( GetCountRegistered() > 0 )
	{
		const CGCObjPlatform* pcPlatform = static_cast<const CGCObjPlatform*>( GetRegisteredObjectAtIndex( 0 ) );
		CCAssert( ( GetGCTypeIDOf( CGCObjPlatform ) == pcPlatform->GetGCTypeID() ),
				  "CGCObject derived type mismatch!" );

		// set up animations for all items - get the creation params from the first one in the group
		const CGCFactoryCreationParams* psObjCreateParams = pcPlatform->GetFactoryCreationParams();

		CCAssert( psObjCreateParams, "0th object in group has no creation params" );

		// make an animation
		ValueMap	cDicPList = GCCocosHelpers::CreateDictionaryFromPlist( psObjCreateParams->strPlistFile );
		Animation*	pAnimation = GCCocosHelpers::CreateAnimation( cDicPList, "Hover" );

		// apply it to all the objects
		ForEachObject
		(
			[&] ( CGCObject* pcItemAsObject )
			{
				CGCObjSprite* pItemSprite = (CGCObjSprite*)pcItemAsObject;
				pItemSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
				return true;
			}
		);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupPlatform::VOnGroupResourceRelease( void )
{
	// n.b. this must happen first, as will fail if objects destroyed before 
	CGCObjectGroup::VOnGroupResourceRelease(); 
}


