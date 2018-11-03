////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
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
// invaders are created from level file, we just need to init their anims
// this has to be done after the invaders have acquired their resources
// hence the name of this function..
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
	ValueMap	cDictPList = GCCocosHelpers::CreateDictionaryFromPlist( pszPlist );
	Animation*	pAnimation = GCCocosHelpers::CreateAnimation( cDictPList, pszAnim_Fly );

	// apply it to all the invaders
	auto cMyLambda = [&] ( CGCObject* pcItemAsObject )
	{
				CCAssert( ( GetGCTypeIDOf( CGCObjInvader ) == pcItemAsObject->GetGCTypeID() ),
						  "CGCObject derived type mismatch!" );

		CGCObjSprite* pItemSprite = (CGCObjSprite*)pcItemAsObject;
		pItemSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
		return true; // returning true means 'please keep iterating'
	};

	ForEachObject( cMyLambda );
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
void CGCObjGroupInvader::DestroyInvaders( void )
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	auto cMyLambda = [&]( CGCObject* pObject )
	{
		GCASSERT( GetGCTypeIDOf( CGCObjInvader ) == pObject->GetGCTypeID(), "wrong type!" );
		CGCObjSprite* pProjectileAsSprite = static_cast< CGCObjSprite* >( pObject );
		pProjectileAsSprite->DestroySprite();
	};

	DestroyObjectsReverseOrder( cMyLambda );
}
