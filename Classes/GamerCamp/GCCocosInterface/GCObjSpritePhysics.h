////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJSPRITEPHYSICS_H_
#define _GCOBJSPRITEPHYSICS_H_

#ifndef _GCOBJSPRITE_H_
	#include "GCObjSprite.h"
#endif

#include "box2d/Box2D.h"


//////////////////////////////////////////////////////////////////////////
// CGCObjSpritePhysics is intended for use as a base class for any CGCObject 
// derived types that need to render a sprite. 
// 
// It wraps the CCSprite class, taking responsibility for managing the 
// lifetime of the managed CCSprite.
//
// The default behaviour is to make the sprite visible when it is put into 
// the live list of the containing group, and to make it invisible when it 
// is put into the dead list of the containing group.
//////////////////////////////////////////////////////////////////////////
class CGCObjSpritePhysics
: public CGCObjSprite
{
private:
	// box 2d body
	b2Body*			m_pb2Body;
	b2BodyDef		m_b2BodyDef;
	std::string		m_strShapeName;

protected:
	CGCObjSpritePhysics( GCTypeID idDerivedType );

	inline b2Body* GetPhysicsBody( void );


public:
					CGCObjSpritePhysics	( void );
	virtual			~CGCObjSpritePhysics( void );

	void			AcquireResources( const char* pszPlistFile, const char* pszPhysicsShape, b2BodyType eb2BodyType, bool bRotationIsFixed );

	void			InitBox2DParams( const b2BodyDef& rBodyDef, const char* pszShapeName );

	virtual void	VUpdateSpriteFromBody( const b2Body* pcb2Body );

	inline b2Vec2	GetVelocity() const;
	inline void		SetVelocity( b2Vec2 v2NewVelocity );

	inline b2Transform	GetPhysicsTransform() const;
	inline void			SetPhysicsTransform( const b2Vec2& rv2Pos, float fAngle );


	//////////////////////////////////////////////////////////////////////////
	// CGCObject Interface - see CGCObject for explanation of the purpose
	// and responsibilities of these functions
		virtual void VOnReset			( void );
		virtual void VOnKilled			( void );
		virtual void VOnResurrected		( void );
		virtual void VOnResourceRelease	( void );
	// CGCObject Interface
	//////////////////////////////////////////////////////////////////////////
};


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
inline b2Body* CGCObjSpritePhysics::GetPhysicsBody( void )
{
	return m_pb2Body;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
inline b2Vec2 CGCObjSpritePhysics::GetVelocity() const
{
	return m_pb2Body->GetLinearVelocity();	
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
inline void	CGCObjSpritePhysics::SetVelocity( b2Vec2 v2NewVelocity )
{
	m_pb2Body->SetLinearVelocity( v2NewVelocity );
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
inline b2Transform CGCObjSpritePhysics::GetPhysicsTransform() const
{
	return m_pb2Body->GetTransform();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
inline void	CGCObjSpritePhysics::SetPhysicsTransform( const b2Vec2& rv2Pos, float fAngle )
{
	m_pb2Body->SetTransform( rv2Pos, fAngle );
}


#endif