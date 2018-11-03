////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJSPRITE_H_
#define _GCOBJSPRITE_H_

#include "base/CCValue.h"

#ifndef __SPITE_NODE_CCSPRITE_H__
#include "2d/CCSprite.h"
#endif

#ifndef __CCGEMETRY_H__
#include "math/CCGeometry.h"
#endif 

#ifndef BOX2D_H
#include "Box2D/Box2D.h"
#endif

#ifndef _GCOBJECT_H_
#include "GamerCamp/GCObject/GCObject.h"
#endif

//////////////////////////////////////////////////////////////////////////
// CGCObjSprite is intended for use as a base class for any CGCObject 
// derived types that need to render a sprite. 
// 
// It wraps the CCSprite class, taking responsibility for managing the 
// lifetime of the managed CCSprite.
//
// The default behaviour is to make the sprite visible when it is put into 
// the live list of the containing group, and to make it invisible when it 
// is put into the dead list of the containing group.
//////////////////////////////////////////////////////////////////////////
class CGCObjSprite
: public CGCObject
{
private:
	// cocos2d sprite used to display this object
	cocos2d::Sprite*	m_pcSprite;

	// used to reposition the sprite at its original position on reset
	b2Vec2				m_v2InitialPosition;

protected:
	CGCObjSprite( GCTypeID idDerivedType );

public:
	CGCObjSprite( void );
	virtual ~CGCObjSprite( void );

	// explicit constructor & destructor 
	void			CreateSprite( const char* pszPlist );
	void			CreateSpriteFast( cocos2d::ValueMap dicSpriteInfo );
	void			DestroySprite( void );

	// control visibility
	inline void		SetVisible( bool bIsVisible );
	inline bool		IsVisible( void );

	// control flip of sprite
	inline void		SetFlippedX( bool bIsFlipped );
	inline bool		IsFlippedX( void );
	inline void		SetFlippedY( bool bIsFlipped );
	inline bool		IsFlippedY( void );

	// position accessors
	inline void		SetSpritePosition( b2Vec2 v2Position );
	inline b2Vec2	GetSpritePosition( void ) const;

	// reset position is where the sprite will go back to when reset
	inline void		SetResetPosition( b2Vec2 v2Position );
	inline b2Vec2	GetResetPosition( void );

	// rotation accessors
	inline void		SetSpriteRotation( float fRotationRadians );
	inline float	GetSpriteRotation( void ) const;

	// accessor for the sprite's rect
	inline cocos2d::Rect GetBoundingBox( void ) const;

	// adds the sprite as a child of the passed CCNode derived type
	void			SetParent( cocos2d::Node* pNewParent );


	// run actions on the sprite (e.g. animations)
	enum EActionState
	{
		EAS_Error,
		EAS_Running,
		EAS_Finished,
	};
	EActionState	RunAction( cocos2d::Action* pAction );


	//////////////////////////////////////////////////////////////////////////
	// CGCObject Interface - see CGCObject for explanation of the purpose
	// and responsibilities of these functions
	virtual void VOnResourceAcquire	( void ) override;
	virtual void VOnReset			( void ) override;
	virtual void VOnResourceRelease	( void ) override;
	virtual void VOnKilled			( void ) override;
	virtual void VOnResurrected		( void ) override;
	// CGCObject Interface
	//////////////////////////////////////////////////////////////////////////
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions inline functions inline functions inline functions inline functions inline functions inline functions inline functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetVisible( bool bIsVisible )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	m_pcSprite->setVisible( bIsVisible );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline bool CGCObjSprite::IsVisible( void )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	return m_pcSprite->isVisible();
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetFlippedX( bool bIsFlipped )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	m_pcSprite->setFlippedX( bIsFlipped );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline bool CGCObjSprite::IsFlippedX( void )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	return m_pcSprite->isFlippedX();
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetFlippedY( bool bIsFlipped )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	m_pcSprite->setFlippedY( bIsFlipped );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline bool CGCObjSprite::IsFlippedY( void )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	return m_pcSprite->isFlippedY();
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetResetPosition( b2Vec2 bArgPosition )
{
	m_v2InitialPosition = bArgPosition;
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline b2Vec2 CGCObjSprite::GetResetPosition( void )
{
	return m_v2InitialPosition;
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetSpriteRotation( float fRotationRadians )
{
	m_pcSprite->setRotation( CC_RADIANS_TO_DEGREES( ( fRotationRadians < b2_pi ) ? fRotationRadians : ( fRotationRadians - ( 2 * b2_pi ) ) ) );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline float CGCObjSprite::GetSpriteRotation( void ) const
{
	return CC_DEGREES_TO_RADIANS( m_pcSprite->getRotation() );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjSprite::SetSpritePosition( b2Vec2 bArgPosition )
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	m_pcSprite->setPosition( cocos2d::Point( bArgPosition.x, bArgPosition.y ) );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline b2Vec2 CGCObjSprite::GetSpritePosition( void ) const
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	cocos2d::Point cPosition = m_pcSprite->getPosition();
	return b2Vec2( cPosition.x, cPosition.y );
}


//////////////////////////////////////////////////////////////////////////
// accessor for the sprite's bounding box
//////////////////////////////////////////////////////////////////////////
inline cocos2d::Rect CGCObjSprite::GetBoundingBox( void ) const
{
	CCAssert( m_pcSprite, "m_pcSprite is NULL. Have you called CreateSprite?" );
	return m_pcSprite->getBoundingBox();
}

#endif