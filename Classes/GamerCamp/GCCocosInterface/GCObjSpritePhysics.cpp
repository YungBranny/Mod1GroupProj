////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GCObjSpritePhysics.h"

#ifndef _GCCOCOSHELPERS_H_
	#include "../GCCocosInterface/GCCocosHelpers.h"
#endif

#ifndef _IGCGAMELAYER_H_
	#include "IGCGameLayer.h"
#endif

#ifndef __COCOS2D_H__
	#include "cocos2d.h"
#endif

#include "GB2ShapeCache-x.h"


//////////////////////////////////////////////////////////////////////////
// save ourselves some typing later
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
// protected version to pass through id to GCObject
//////////////////////////////////////////////////////////////////////////
CGCObjSpritePhysics::CGCObjSpritePhysics( GCTypeID idDerivedType )
: CGCObjSprite		( idDerivedType )
, m_pb2Body			( NULL )
{
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjSpritePhysics::CGCObjSpritePhysics( void )
: CGCObjSprite		( GetGCTypeIDOf( CGCObjSpritePhysics ) )
, m_pb2Body			( NULL )
{
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
CGCObjSpritePhysics::~CGCObjSpritePhysics( void )
{
	// this object is owned by the box2d world
	m_pb2Body = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjSpritePhysics::InitBox2DParams( const b2BodyDef& rBodyDef, const char* pszShapeName )
{
	m_b2BodyDef		= rBodyDef;
	m_strShapeName	= pszShapeName; 
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VUpdateSpriteFromBody( const b2Body* pcb2Body )
{
	CCAssert( pcb2Body == m_pb2Body, "called back for a body that we did not expect to be!" );
	SetSpritePosition( IGCGameLayer::B2dWorldToPixels( pcb2Body->GetPosition() ) );
}


//////////////////////////////////////////////////////////////////////////
// Acquires the resources needed for the obje sprite asked for in VHandleFactoryParams
// 
// N.B. default is to parent self to the layer (needed to render within cocos)
//
//////////////////////////////////////////////////////////////////////////
void CGCObjSpritePhysics::AcquireResources(		const char* pszPlistFile,
												const char*	pszPhysicsShape,
												b2BodyType	eb2BodyType,
												bool		bRotationIsFixed)
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pszPlistFile );
	CreateSprite( pszPlistFile );

	// N.B. default is to parent self to the layer (needed to render within cocos)
	SetParent( IGCGameLayer::ActiveInstance() );

	b2BodyDef bodyDef;
	bodyDef.type			= eb2BodyType;
	bodyDef.fixedRotation	= bRotationIsFixed;

	InitBox2DParams( bodyDef, pszPhysicsShape );
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnReset( void )
{
	CGCObjSprite::VOnReset();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnKilled( void )
{
	CGCObjSprite::VOnKilled();
	IGCGameLayer::ActiveInstance()->B2dGetWorld()->DestroyBody( m_pb2Body );
	m_pb2Body = nullptr;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual  
void CGCObjSpritePhysics::VOnResurrected( void )
{
	CGCObjSprite::VOnResurrected();

	// create the physics body
	m_pb2Body = IGCGameLayer::ActiveInstance()->B2dGetWorld()->CreateBody( &m_b2BodyDef );
	cocos2d::GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody( m_pb2Body, m_strShapeName );
	m_pb2Body->SetUserData( this );
	m_pb2Body->SetTransform( IGCGameLayer::B2dPixelsToWorld( GetSpritePosition() ), 0.0f );
}


//////////////////////////////////////////////////////////////////////////
// ALEX: I do not like this, but this ensures that all objects created via 
// the CGCObjSpritePhysics::VHandleFactoryParams() factory interface will 
// still get cleaned up properly...
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnResourceRelease( void )
{
	if( nullptr != m_pb2Body )
	{
		IGCGameLayer::ActiveInstance()->B2dGetWorld()->DestroyBody( m_pb2Body );
		m_pb2Body = NULL;
	}
	CGCObjSprite::DestroySprite();
}

