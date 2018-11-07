////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>

#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"

#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"

#include "GCObjPlayer.h"

USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
CGCObjPlayer::CGCObjPlayer()
: CGCObjSpritePhysics			( GetGCTypeIDOf( CGCObjPlayer ) )
, m_pProjectileManager			( NULL )
, m_fMaximumMoveForce_Horizontal( 20.0f )
, m_fDragCoefficient_Linear		( 0.25f )
, m_fDragCoefficient_Square		( 0.2f )
, m_fNoInput_ExtraDrag_Square	( 0.2f )
, m_fNoInput_VelocityThreshold	( 0.25f )
{
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE( CGCObjPlayer, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true );
//virtual 
void CGCObjPlayer::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CGCObjPlayer );

	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszAnim_marioJog = "Jog";

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist( GetFactoryCreationParams()->strPlistFile );
	RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( dicPList, pszAnim_marioJog ) ) );

	// find the player projectile group 
	// N.B. we know this cast is safe because we're checking the typeID
	m_pProjectileManager = static_cast< CGCObjGroupProjectilePlayer* >
		( CGCObjectManager::FindObjectGroupByID( GetGCTypeIDOf( CGCObjGroupProjectilePlayer ) ));
}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlayer::VOnReset( void )
{
	CGCObjSpritePhysics::VOnReset();

	// reset velocity and flip state
	SetFlippedX( false );
	SetFlippedY( false );

	// reset
	if( GetPhysicsBody() )
	{
		GetPhysicsBody()->SetLinearVelocity( b2Vec2( 0.0f, 0.0f ) );
		GetPhysicsBody()->SetTransform( IGCGameLayer::B2dPixelsToWorld( GetSpritePosition() ), 0.0f );
		GetPhysicsBody()->SetFixedRotation( true );
	}
}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlayer::VOnUpdate( f32 fTimeStep )
{
	// handle movement
	UpdateMovement( fTimeStep );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual
void CGCObjPlayer::VOnResourceRelease( void )
{
    CGCObjSpritePhysics::VOnResourceRelease();
}


//////////////////////////////////////////////////////////////////////////
// updates the movement of the CCSprite owned by this instance
//
// N.B. globals that we can edit in the debugger used to override the 
// values of the members for debugging control code
f32 g_CGCObjPlayer_fMass						= 1.0f;		// kg
f32	g_CGCObjPlayer_fMaximumMoveForce_Horizontal	= 20.0f;	// newton
f32	g_CGCObjPlayer_fMaximumMoveForce_Vertical	= 40.0f;	// newton
f32	g_CGCObjPlayer_fDragCoefficient_Linear		= 0.25f;	// unitless
f32	g_CGCObjPlayer_fDragCoefficient_Square		= 0.2f;		// unitless
f32 g_CGCObjPlayer_m_fNoInput_ExtraDrag_Square	= 0.2f;		// unitless
f32 g_CGCObjPlayer_fNoInput_VelocityThreshold	= 0.25f;	// m/s

f32 g_GCGameLayer_fPixelsPerMetre				= 20.0f;	// pixels / metre
f32 g_GCGameLayer_fDamping						= 0.999f;	// unitless
//
//////////////////////////////////////////////////////////////////////////
void CGCObjPlayer::UpdateMovement( f32 fTimeStep )
{
	m_fMaximumMoveForce_Horizontal	= g_CGCObjPlayer_fMaximumMoveForce_Horizontal;
	m_fMaximumMoveForce_Vertical	= g_CGCObjPlayer_fMaximumMoveForce_Vertical;
	m_fDragCoefficient_Linear		= g_CGCObjPlayer_fDragCoefficient_Linear;
	m_fDragCoefficient_Square		= g_CGCObjPlayer_fDragCoefficient_Square;
	m_fNoInput_ExtraDrag_Square		= g_CGCObjPlayer_m_fNoInput_ExtraDrag_Square;
	m_fNoInput_VelocityThreshold	= g_CGCObjPlayer_fNoInput_VelocityThreshold;

	// we accumulate total force over the frame and apply it at the end
	b2Vec2 v2TotalForce( 0.0f, 0.0f);


	// * calculate the control force direction
	b2Vec2 v2ControlForceDirection( 0.0f, 0.0f );

	// these 2 floats are used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	f32 fIsInputInactive	= 1.0f;

	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Up ) )
	{
		v2ControlForceDirection.y	= 1.0f;
		fIsInputInactive			= 0.0f;
	}
	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Down ) )
	{
		v2ControlForceDirection.y	= -1.0f;
		fIsInputInactive			= 0.0f;
	}

	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Left ) )
	{
		v2ControlForceDirection.x	= -1.0f;
		fIsInputInactive			= 0.0f;
	}	
	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Right ) )
	{
		v2ControlForceDirection.x	= 1.0f;
		fIsInputInactive			= 0.0f;
	}
	
	// normalise the control vector and multiply by movement force
	v2ControlForceDirection.Normalize();
	v2ControlForceDirection.x *= m_fMaximumMoveForce_Horizontal;
	v2ControlForceDirection.y *= m_fMaximumMoveForce_Vertical;

	// accumulate the force
	v2TotalForce += v2ControlForceDirection;


	// * calculate drag force
	b2Vec2 v2Velocity_Unit = GetPhysicsBody()->GetLinearVelocity();
	f32 fVelocity = v2Velocity_Unit.Normalize();
	
	// This is not the real equation for drag.
	// This is a simple mathematical function that approximates the behaviour 
	// of drag in a very tunable way - it misses out loads of the real factors
	// involved in real aerodynamic drag. I have a feeling I got it from a 
	// game physics textbook, but I can't remember for sure.
	//
	// For the 'proper' drag equation see this: 
	// http://en.wikipedia.org/wiki/Drag_(physics)#Drag_at_high_velocity

	// N.B. the last term evaluates to 0.0f if there is controller input

	f32 fDragForce = (		( m_fDragCoefficient_Linear * fVelocity ) 
						+	( m_fDragCoefficient_Square * ( fVelocity * fVelocity ) ) 
						+	( m_fNoInput_ExtraDrag_Square * ( fVelocity * fVelocity ) * fIsInputInactive ) );

	// drag is applied in the opposite direction to the current velocity of the object
	// so scale out unit version of the object's velocity by -fDragForce
	// N.B. operator* is only defined for (float, b2Vec2) and not for (b2Vec2, float) !?!
	v2TotalForce += ( -fDragForce * v2Velocity_Unit );


	// physics calcs handled by box 2d based on force applied
	GetPhysicsBody()->ApplyForceToCenter( v2TotalForce, true );


	// * set sprite flip based on velocity
	// N.B. the else-if looks redundant, but we want the sprite's flip 
	// state to stay the same if its velocity is set to (0.0f, 0.0f)
	if( GetPhysicsBody()->GetLinearVelocity().y >= 0.0f )
	{
		SetFlippedY( false );
	}
	else if( GetPhysicsBody()->GetLinearVelocity().y < 0.0f )
	{
		SetFlippedY( true );
	}

	if( GetPhysicsBody()->GetLinearVelocity().x >= 0.0f )
	{
		SetFlippedX( true );
	}
	else if( GetPhysicsBody()->GetLinearVelocity().x < 0.0f )
	{
		SetFlippedX( false );
	}

	// fire!
	if( pKeyManager->ActionHasJustBeenPressed( CGCGameLayerPlatformer::EPA_Fire ) )
	{
		// supply initial position, velocity, lifetime
		m_pProjectileManager->SpawnProjectile(	GetSpritePosition() + b2Vec2( 0.0f, 20.0f ),
												b2Vec2( 0.0f, 10.0f ),
												3.0f );	
	}
}

//////////////////////////////////////////////////////////////////////////
// this function exists purely to better illustrate the EXAMPLE collision 
// detection functionality in CGCGameLayerPlatformer
//////////////////////////////////////////////////////////////////////////
void CGCObjPlayer::NotifyOfCollisionWithInvader()
{
    CCLOG( "CGCObjPlayer::NotifyOfCollisionWithInvader - Aiee! I have collided with an invader!" );
}
