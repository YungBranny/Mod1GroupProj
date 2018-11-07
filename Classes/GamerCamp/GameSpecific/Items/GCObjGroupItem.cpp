////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Items/GCObjGroupItem.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjGroupItem::CGCObjGroupItem()
{
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupItem::~CGCObjGroupItem()
{}



//////////////////////////////////////////////////////////////////////////
// only handle items
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupItem::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf( CGCObjItem ) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupItem::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupItem );
}



//////////////////////////////////////////////////////////////////////////
// invaders are created from level file, we just need to init their anims
// this has to be done after the invaders have acquired their resources
// hence the name of this function..
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupItem::VOnGroupResourceAcquire_PostObject( void )
{
	if( GetCountRegistered() > 0 )
	{
		const CGCObjItem* pcItem = static_cast< const CGCObjItem* >( GetRegisteredObjectAtIndex( 0 ) );
		CCAssert( ( GetGCTypeIDOf( CGCObjItem ) == pcItem->GetGCTypeID() ),
				  "CGCObject derived type mismatch!" );

		// set up animations for all items - get the creation params from the first one in the group
		const CGCFactoryCreationParams* psObjCreateParams = pcItem->GetFactoryCreationParams();

		CCAssert( psObjCreateParams, "0th object in group has no creation params" );

		// make an animation
		ValueMap	cDicPList	= GCCocosHelpers::CreateDictionaryFromPlist( psObjCreateParams->strPlistFile );
		Animation*	pAnimation	= GCCocosHelpers::CreateAnimation( cDicPList, "Rotate" );

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
void CGCObjGroupItem::VOnGroupResourceRelease( void )
{
	// n.b. this must happen first, as will fail if objects destroyed before 
	CGCObjectGroup::VOnGroupResourceRelease(); 
}


