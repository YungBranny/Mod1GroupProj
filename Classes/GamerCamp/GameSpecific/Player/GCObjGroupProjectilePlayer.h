////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef	_GCOBJGROUPPROJECTILEPLAYER_H_
#define	_GCOBJGROUPPROJECTILEPLAYER_H_


#ifndef BOX2D_H
	#include "Box2d/Box2D.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
	#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjProjectilePlayer;


//////////////////////////////////////////////////////////////////////////
// responsible for newing, managing, & deleting the player's projectiles
//
// This shows how an object group can be used as an allocation pool.
//
//////////////////////////////////////////////////////////////////////////
class CGCObjGroupProjectilePlayer
: public CGCObjectGroup
{
public:
	// number of invaders
	static const u32 k_uNumProjectiles = 16;

	CGCObjGroupProjectilePlayer			( void );		
	virtual ~CGCObjGroupProjectilePlayer( void )  override;

	// called from CGCGameLayerPlatformer::VOnCreate
	void				CreateProjectiles	( void );
	void				DestroyProjectiles	( void );

	void				SpawnProjectile		( b2Vec2 v2Position, b2Vec2 v2Velocity, f32 fMaxLifeTime );

//////////////////////////////////////////////////////////////////////////
// overrides for CGCObjectGroup public interface

	// handles GCObjInvader
	virtual bool		VHandlesThisTypeId	( GCTypeID idQueryType ) override;

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId				( void ) override;

	virtual void		VOnGroupResourceAcquire	( void ) override;	
	virtual void		VOnGroupResourceRelease	( void ) override;	

// CGCObjectGroup public interface
//////////////////////////////////////////////////////////////////////////
};

#endif
