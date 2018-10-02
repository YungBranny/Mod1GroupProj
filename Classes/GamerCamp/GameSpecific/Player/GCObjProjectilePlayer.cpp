////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"

#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjProjectilePlayer.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
// N.B. this is super important!
//
//////////////////////////////////////////////////////////////////////////
CGCObjProjectilePlayer::CGCObjProjectilePlayer()
: CGCObjSpritePhysics( GetGCTypeIDOf( CGCObjProjectilePlayer ) )
{	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CGCObject interface

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjProjectilePlayer::VOnResourceAcquire( void )
{
	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszPlist = "TexturePacker/Sprites/Egg/Egg.plist";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pszPlist );
	AcquireResources( pszPlist, "egg", b2_dynamicBody, true );
	SetParent( IGCGameLayer::ActiveInstance() );
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjProjectilePlayer::VOnReset( void )
{
	CGCObjSpritePhysics::VOnReset();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjProjectilePlayer::VOnUpdate( f32 fTimeStep )
{
	// changes to desired velocity
	b2Vec2 v2DesiredVelocityDelta = ( m_v2VelocityDesired - GetPhysicsBody()->GetLinearVelocity() );

	// 1) f = m * a -> a = f/m
	// 2) v = a * t -> a = v/t
	// so f/m = v/t -> f = (v/t) * m
	b2Vec2 v2RequiredForce = GetPhysicsBody()->GetMass() * ( ( 1.0f / fTimeStep ) * v2DesiredVelocityDelta );
	GetPhysicsBody()->ApplyForceToCenter( v2RequiredForce, true );

	// handle lifetime
	m_fRemainingLifetime -= fTimeStep;
	if( m_fRemainingLifetime < 0.0f )
	{
		CGCObjectManager::ObjectKill( this );
	}
}
