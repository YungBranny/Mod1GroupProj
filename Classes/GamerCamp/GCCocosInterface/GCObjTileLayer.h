////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJTILELAYER_H_
#define _GCOBJTILELAYER_H_

#ifndef BOX2D_H
	#include "Box2D/Box2D.h"
#endif

#ifndef __CCTMX_TILE_MAP_H__
	#include "2d/CCTMXTiledMap.h"
#endif

#ifndef _GCOBJECT_H_
	#include "GamerCamp/GCObject/GCObject.h"
#endif

//////////////////////////////////////////////////////////////////////////
// 
// N.B. since this shares a lot of common code with CGCObjSprite the
// common interface should probably be factored into a base class they can 
// both derive from...
//////////////////////////////////////////////////////////////////////////
class CGCObjTileLayer
: public CGCObject
{
private:
	// cocos2d TMXTiledMap used to display the .tmx file
	cocos2d::TMXTiledMap* m_pTMXMap;

	// used to reposition the sprite at its original position on reset
	b2Vec2				m_v2InitialPosition;

protected:
			CGCObjTileLayer	( GCTypeID idDerivedType );

public:
			CGCObjTileLayer		( void );
	virtual ~CGCObjTileLayer	( void );

	// explicit construction / destruction for tiel layer
	void			CreateTileLayer	( const char* pszPlist );
	void			DestroyTileLayer( void );

	// position accessors
	inline void		SetPosition		( b2Vec2 v2Position );
	inline b2Vec2	GetPosition		( void ) const;
	// reset position is where the sprite will go back to when reset
	inline void		SetResetPosition( b2Vec2 v2Position );
	
	// adds the sprite as a child of the passed CCNode derived type
	void			SetParent		( cocos2d::Node* pNewParent );

	//////////////////////////////////////////////////////////////////////////
	// accessors for the TMX data
	
		// return values for GetObjectPosition
		enum EGetObjPosErr
		{
			EGetObjPosErr_OK,				// returned if ok
			EGetObjPosErr_GroupNotFound,	// returned if named object group not found
			EGetObjPosErr_ObjectNotFound	// returned if named object not found
		};
		// n.b. position is returned by reference
		EGetObjPosErr GetObjectPosition( const char* pszObjectGroupName, const char* pszObjectName, b2Vec2& rv2ReturnPos );

	// accessors for the TMX data
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// CGCObject Interface - see CGCObject for explanation of the purpose
	// and responsibilities of these functions
		virtual void VOnResourceAcquire	( void );
		virtual void VOnReset		    ( void );              // must be implemented as pure virtual in GCObject
		virtual void VOnUpdate		    ( float fTimeStep );   // must be implemented as pure virtual in GCObject
		virtual void VOnResourceRelease	( void );
	// CGCObject Interface
	//////////////////////////////////////////////////////////////////////////
};


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjTileLayer::SetResetPosition( b2Vec2 bArgPosition )
{
	m_v2InitialPosition = bArgPosition;
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline void CGCObjTileLayer::SetPosition( b2Vec2 bArgPosition )
{
	CCAssert( m_pTMXMap, "m_pTMXMap is NULL. Have you called CreateSprite?" );
	m_pTMXMap->setPosition( cocos2d::Point( bArgPosition.x, bArgPosition.y ) );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
inline b2Vec2 CGCObjTileLayer::GetPosition( void ) const
{
	CCAssert( m_pTMXMap, "m_pcSpm_pTMXMaprite is NULL. Have you called CreateSprite?" );
	cocos2d::Point cPosition = m_pTMXMap->getPosition();
	return b2Vec2( cPosition.x, cPosition.y );
}

#endif // _GCOBJTILELAYER_H_