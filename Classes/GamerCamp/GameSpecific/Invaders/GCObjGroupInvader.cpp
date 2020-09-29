////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjGroupInvader::CGCObjGroupInvader( int iMaxNumInvaders )
: m_iMaxInvaders										( iMaxNumInvaders )
, m_iNumRows											( 1 )
, m_iNumColumns											( 1 )
, m_fSpacingRow											( 0.0f )
, m_fSpacingColumn										( 0.0f )
, m_v2FormationOrigin									( Vec2::ZERO )
, m_eMoveDirection										( EMoveDirection::Right )
, m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame( false )
{
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
void CGCObjGroupInvader::SetFormationOrigin( Vec2 v2FormationOrigin )
{
	m_v2FormationOrigin = v2FormationOrigin;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::SetRowsAndColumns( f32 iNumRows, int iNumColumns, f32 fPixelSpacingRow, f32 fPixelSpacingColumn )
{
	m_iNumRows			= iNumRows;
	m_iNumColumns		= iNumColumns;
	m_fSpacingRow		= fPixelSpacingRow;
	m_fSpacingColumn	= fPixelSpacingColumn;
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
GCTypeID CGCObjGroupInvader::VGetTypeId()
{
	return GetGCTypeIDOf( CGCObjGroupInvader );
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceAcquire()
{
	CreateInvaders();
	IGCGameLayer::ActiveInstance()->GetCollisionManager().AddCollisionHandler
	(
		[this]
		( CGCObjInvader& rcInvader, CGCObjScreenBound& rcEdgeOfScreen, const b2Contact& rcContact) -> void
		{
			CheckForGroupWallCollisionInCurrentMoveDirection( rcEdgeOfScreen );
		}
	);

	SetResetBehaviour( CGCObjectGroup::EResetBehaviour::EResetDead );

	CGCObjectGroup::VOnGroupResourceAcquire();
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceAcquire_PostObject()
{
	// we do this here because the alternative is to do it for each invader as they're created and it's

	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();

	// set up animations for all items
	const char* pszPlist	= "TexturePacker/Sprites/KoopaTrooper/KoopaTrooper.plist";
	const char* pszAnim_Fly = "Fly";

	// make an animation
	ValueMap&	rdictPList = GCCocosHelpers::CreateDictionaryFromPlist( pszPlist );
	Animation*	pAnimation = GCCocosHelpers::CreateAnimation( rdictPList, pszAnim_Fly );

	ForEachObject( [&] ( CGCObject* pObject ) -> bool
	{
		CCAssert( ( GetGCTypeIDOf( CGCObjInvader ) == pObject->GetGCTypeID() ),
			"CGCObject derived type mismatch!" );

		CGCObjSprite* pItemSprite = (CGCObjSprite*)pObject;
		pItemSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
		return true;
	} );
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjGroupInvader::VOnGroupReset()
{
	CGCObjectGroup::VOnGroupReset();

	m_eMoveDirection										= EMoveDirection::Right;
	m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame	= false;
	m_fTimeInCurrentMoveDirection							= 0.0f;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjGroupInvader::VOnObjectReset()
{
	CGCObjectGroup::VOnObjectReset();

	int iRow	= 0;
	int iColumn = 0; 

	ForEachObject
	(
		[&, this]
		( CGCObject* pInvaderAsObject ) -> bool
		{	
			CGCObjInvader* pInvader = CGCObject::SafeCastToDerived< CGCObjInvader* >( pInvaderAsObject );
			CCAssert( ( nullptr != pInvader ), "Aiiieeeee!! Houston we have a problem!" );

			VOnObjectResurrect( pInvader );
			pInvader->SetResetPosition( Vec2( ( m_v2FormationOrigin.x + ( m_fSpacingColumn * iColumn++ ) ), ( m_v2FormationOrigin.y + ( m_fSpacingRow * iRow ) ) ) );
			pInvader->VOnReset();

			if( iColumn >= m_iNumColumns )
			{
				iColumn = 0;
				iRow++;
			}

			if( iRow >= m_iNumRows )
			{
				return false;
			}

			return true;
		}
	);
}


//////////////////////////////////////////////////////////////////////////
Vec2	s_InvaderGroup_v2VelocityRight	= Vec2( 5.0f, 0.0f );
Vec2	s_InvaderGroup_v2VelocityLeft	= ( -s_InvaderGroup_v2VelocityRight );

Vec2	s_InvaderGroup_v2VelocityDown	= Vec2( 0.0f, -6.0f );
f32		s_InvaderGroup_fMoveDownTime	= 0.2f;
//////////////////////////////////////////////////////////////////////////
//virtual override
void CGCObjGroupInvader::VOnGroupUpdate( f32 fTimeStep )
{
	CGCObjectGroup::VOnGroupUpdate( fTimeStep );

	// group movement logic

	m_fTimeInCurrentMoveDirection += fTimeStep;

	EMoveDirection eMoveDirBeforeDirectionLogic = m_eMoveDirection;

	switch( m_eMoveDirection )
	{
	case EMoveDirection::Right:
		if( m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame )
		{
			m_eMoveDirection = EMoveDirection::DownBeforeLeft;
		}
		break;

	case EMoveDirection::DownBeforeLeft:
		if( m_fTimeInCurrentMoveDirection >= s_InvaderGroup_fMoveDownTime )
		{
			m_eMoveDirection = EMoveDirection::Left;
		}
		break;

	case EMoveDirection::Left:
		if( m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame )
		{
			m_eMoveDirection = EMoveDirection::DownBeforeRight;			
		}
		break;

	case EMoveDirection::DownBeforeRight:
		if( m_fTimeInCurrentMoveDirection >= s_InvaderGroup_fMoveDownTime )
		{
			m_eMoveDirection = EMoveDirection::Right;
		}
		break;
	}

	m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame = false;

	if( eMoveDirBeforeDirectionLogic != m_eMoveDirection )
	{
		m_fTimeInCurrentMoveDirection = 0.0f;
	}


	// update invaders

	Vec2 v2CurrentGroupVelocity = Vec2::ZERO;

	switch( m_eMoveDirection )
	{
	case EMoveDirection::DownBeforeLeft:
	case EMoveDirection::DownBeforeRight:
		v2CurrentGroupVelocity = s_InvaderGroup_v2VelocityDown;
		break;

	case EMoveDirection::Left:
		v2CurrentGroupVelocity = s_InvaderGroup_v2VelocityLeft;
		break;

	case EMoveDirection::Right:
		v2CurrentGroupVelocity = s_InvaderGroup_v2VelocityRight;
		break;
	}

	ForEachObjectIn_LiveList
	(	
		[&]										// capture locals by ref
		( CGCObject* pInvaderAsGcObj ) -> bool	// return true to keep iterating
		{
			CGCObjInvader* pInvader = CGCObject::SafeCastToDerived< CGCObjInvader* >( pInvaderAsGcObj );
			CCAssert( ( nullptr != pInvader ), "Aiiieeeee!! Houston we have a problem!" );
			pInvader->SetVelocity( v2CurrentGroupVelocity );
			return true;
		}
	);
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupInvader::VOnGroupResourceRelease()
{
	// N.B. need to do this first as it clears internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyInvaders();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::CheckForGroupWallCollisionInCurrentMoveDirection( const CGCObjScreenBound& pScreenBound )
{
	switch( m_eMoveDirection )
	{
	case EMoveDirection::Left:
		if( pScreenBound.GetScreenBoundType() == CGCObjScreenBound::EScreenBoundType::Left )
		{		
			m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame = true;
		}
		break;

	case EMoveDirection::Right:
		if( pScreenBound.GetScreenBoundType() == CGCObjScreenBound::EScreenBoundType::Right )
		{		
			m_bAtLeastOneInvaderTouchedTheEdgeOfTheScreenLastFrame = true;
		}
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::CreateInvaders()
{
	for( i32 iLoop = 0; iLoop < m_iMaxInvaders; ++iLoop )
	{	
		// n.b. these register themselves with this class on creation
		CGCObjInvader* pInvader = new CGCObjInvader(); 
		pInvader->SetName( "Derek" );
	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupInvader::DestroyInvaders()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder( [&]( CGCObject* pObject )
	{
		// do nothing - DestroyObjectsReverseOrder calls delete!
		GCASSERT( GetGCTypeIDOf( CGCObjInvader ) == pObject->GetGCTypeID(), "wrong type!" );
	});
}
