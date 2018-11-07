////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef	_GCOBJECTGROUPINVADER_H_
#define	_GCOBJECTGROUPINVADER_H_


#ifndef BOX2D_H
	#include "Box2D/Box2D.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
	#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjSprite;
class CGCObjInvader;


//////////////////////////////////////////////////////////////////////////
// responsible for newing, managing, & deleting the invaders
//
// This shows how an object group can be used as an allocation pool.
//
//////////////////////////////////////////////////////////////////////////
class CGCObjGroupInvader
: public CGCObjectGroup
{
private:
	b2Vec2 m_v2FormationOrigin; // origin of the formation

public:
	// number of invaders
	static const u32 k_uNumInvaders = 16;

	CGCObjGroupInvader();		
	virtual ~CGCObjGroupInvader() override;

	void SetFormationOrigin( b2Vec2 m_v2FormationOrigin );

//////////////////////////////////////////////////////////////////////////
// overrides for CGCObjectGroup public interface

	// handles GCObjInvader
	virtual bool		VHandlesThisTypeId					( GCTypeID idQueryType ) override;

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId							( void ) override;

	virtual void		VOnGroupResourceAcquire_PostObject	( void ) override; // invaders are created from level file

	virtual void		VOnGroupResourceRelease				( void ) override;

// CGCObjectGroup public interface
//////////////////////////////////////////////////////////////////////////
};

#endif
