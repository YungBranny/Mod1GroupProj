////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GCOBJSCREENBOUND_H_
	#include "GCObjScreenBound.h"
#endif

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
CGCObjScreenBound::CGCObjScreenBound( EScreenBoundType eBoundType, cocos2d::Vec2 v2Position, f32 fWidth, f32 fHeight, f32 fAngle )
: CGCObjSpritePhysics( GetGCTypeIDOf( CGCObjScreenBound ) )
, m_eBoundType			( eBoundType )
, m_pb2ScreenBoundBody	( nullptr )
{
	m_b2ScreenBoundShape.SetAsBox( ( fWidth / 2.0F ), ( fHeight / 2.0f ), b2Vec2( v2Position.x, v2Position.y ), fAngle);
}


//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnResourceAcquire()
{ /* do nothing! */ }

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnReset()
{ /* do nothing! */ }

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnUpdate( float fTimeStep )
{ /* do nothing! */ }

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnResourceRelease()
{ /* do nothing! */ }

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnKilled()
{
	IGCGameLayer::ActiveInstance()->B2dGetWorld()->DestroyBody( m_pb2ScreenBoundBody );
	m_pb2ScreenBoundBody = nullptr;
}

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VOnResurrected() 
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.SetZero();
	groundBodyDef.type = b2_kinematicBody;

	m_pb2ScreenBoundBody = IGCGameLayer::ActiveInstance()->B2dGetWorld()->CreateBody( &groundBodyDef );
	b2Fixture* b2Fixture = m_pb2ScreenBoundBody->CreateFixture( &m_b2ScreenBoundShape, 0 );

	// all other code gets fixtures from GB2ShapeCache-x which sets userdata on them
	m_pb2ScreenBoundBody->SetUserData( this );
}

//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjScreenBound::VUpdateSpriteFromBody( const b2Body* pcb2Body )
{ /* do nothing! */ }

