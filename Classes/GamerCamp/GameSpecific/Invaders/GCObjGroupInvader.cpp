////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerSpaceInvaders.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjGroupInvader::CGCObjGroupInvader()
{
	m_v2FormationOrigin = b2Vec2_zero;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupInvader::~CGCObjGroupInvader()
{}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::SetFormationOrigin( b2Vec2 v2FormationOrigin )
{
	m_v2FormationOrigin = v2FormationOrigin;
}

//////////////////////////////////////////////////////////////////////////
// only handle invaders
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupInvader::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf( CGCObjInvader ) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupInvader::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupInvader );
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceAcquire( void )
{
	CreateInvaders();
	CGCObjectGroup::VOnGroupResourceAcquire();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceAcquire_PostObject( void )
{
	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();

	// set up animations for all items
	const char* pszPlist	= "TexturePacker/Sprites/KoopaTrooper/KoopaTrooper.plist";
	const char* pszAnim_Fly = "Fly";

	// make an animation
	ValueMap&	rdictPList = GCCocosHelpers::CreateDictionaryFromPlist( pszPlist );
	Animation*	pAnimation = GCCocosHelpers::CreateAnimation( rdictPList, pszAnim_Fly );

	// N.B. this is a workaround for the fact that Marmalade's version of GCC for ARM doesn't support lambdas. Blergh.
	SGCObjectGatherer sMyGatherer;
	ForEachObject( sMyGatherer );

	// create an animation action and set it for each invader
	for( u32 uIndex = 0; uIndex < sMyGatherer.uCount; ++uIndex )
	{
		CGCObject* pcItemAsObject = sMyGatherer.apObjects[ uIndex ];
		CCAssert( ( GetGCTypeIDOf( CGCObjInvader ) == pcItemAsObject->GetGCTypeID() ),
			"CGCObject derived type mismatch!" );

		CGCObjSprite* pItemSprite = (CGCObjSprite*)pcItemAsObject;
		pItemSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceRelease( void )
{
	// N.B. need to do this first as it clears internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyInvaders();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::CreateInvaders( void )
{
	const char* pszPlist_KooperTrooper		= "TexturePacker/Sprites/KoopaTrooper/KoopaTrooper.plist";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pszPlist_KooperTrooper );

	i32	iOffsetX = 40;
	i32	iOffsetY = 100;
	for( u32 uLoop = 0; uLoop < k_uNumProjectiles; ++uLoop )
	{	
		// n.b. these register themselves with this class on creation
		CGCObjInvader* pInvader = new CGCObjInvader(); 
		pInvader->SetResetPosition( b2Vec2( m_v2FormationOrigin.x + ( iOffsetX * uLoop ), ( m_v2FormationOrigin.y + iOffsetY ) ) );
		pInvader->SetName( "Derek" );
	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::DestroyInvaders( void )
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder( [&]( CGCObject* pObject )
	{
		GCASSERT( GetGCTypeIDOf( CGCObjInvader ) == pObject->GetGCTypeID(), "wrong type!" );
		CGCObjSprite* pProjectileAsSprite = static_cast< CGCObjSprite* >( pObject );
		pProjectileAsSprite->DestroySprite();
	});
}
