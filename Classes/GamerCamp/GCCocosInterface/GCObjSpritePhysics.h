////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJSPRITEPHYSICS_H_
#define _GCOBJSPRITEPHYSICS_H_

#ifndef _GCOBJSPRITE_H_
	#include "GCObjSprite.h"
#endif

#ifndef BOX2D_H
	#include "Box2D/Box2D.h"
#endif

#ifndef _SGCFACTORYCREATIONPARAMS_H_
	#include "SGCFactoryCreationParams.h"
#endif

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
	//////////////////////////////////////////////////////////////////////////
	// parameters passed to this object from the factory when it was created
	// this pointer is set during CGCObjSpritePhysics::VHandleFactoryParams()
	const CGCFactoryCreationParams* m_psCreateParams;	
	
	// box 2d body
	b2Body*			m_pb2Body;
	b2BodyDef		m_b2BodyDef;
	std::string		m_strShapeName;

protected:
	CGCObjSpritePhysics( GCTypeID idDerivedType );

	inline b2Body* GetPhysicsBody( void );

	inline const CGCFactoryCreationParams* GetFactoryCreationParams( void )	const;

public:
					CGCObjSpritePhysics	( void );
	virtual			~CGCObjSpritePhysics( void );

	void			InitBox2DParams( const b2BodyDef& rBodyDef, const char* pszShapeName );

	// N.B. this function is called by the macro 
	// GCFACTORY_IMPLEMENT_CREATEABLECLASS() after the class instance has 
	// been created
	virtual void VHandleFactoryParams( const CGCFactoryCreationParams& rCreationParams, b2Vec2 v2InitialPosition ); 

	virtual void	VUpdateSpriteFromBody( const b2Body* pcb2Body );

	inline b2Vec2	GetVelocity() const;
	inline void		SetVelocity( b2Vec2 v2NewVelocity );

	inline b2Transform	GetPhysicsTransform() const;
	inline void			SetPhysicsTransform( const b2Vec2& rv2Pos, float fAngle );


	//////////////////////////////////////////////////////////////////////////
	// CGCObject Interface - see CGCObject for explanation of the purpose
	// and responsibilities of these functions
		virtual void VOnResourceAcquire ( void ) override; 
		virtual void VOnReset			( void ) override;
		virtual void VOnKilled			( void ) override;
		virtual void VOnResurrected		( void ) override;
		virtual void VOnResourceRelease	( void ) override;
	// CGCObject Interface
	//////////////////////////////////////////////////////////////////////////
};


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// protected
inline b2Body* CGCObjSpritePhysics::GetPhysicsBody( void )
{
	return m_pb2Body;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// protected
inline const CGCFactoryCreationParams* CGCObjSpritePhysics::GetFactoryCreationParams( void ) const
{
	return m_psCreateParams;
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