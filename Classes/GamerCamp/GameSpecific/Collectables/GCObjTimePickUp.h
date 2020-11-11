#ifndef	_GCOBJTIMEPICKUP_H_
#define	_GCOBJTIMEPICKUP_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjTimePickUp' Header File and Class File was created and is managed by Mehak Hussain.
// The purpose of this Class is to create the Timer PickUp for the Player to collect.
// In this Class, I set the physics and creation of the Timer PickUp.
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjTimePickUp
	: public CGCObjSpritePhysics
{
private:
	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

public:
	CGCObjTimePickUp ( void );
	virtual ~CGCObjTimePickUp ();

	GCFACTORY_DECLARE_CREATABLECLASS(CGCObjTimePickUp);

	unsigned short int getCollisionBuffer ()		const		{ return m_iCollisionBuffer; }
	void  setCollisionBuffer ( unsigned short int i )		{ m_iCollisionBuffer = i;    }

	bool  getJustCollided ()					const		{ return m_bJustCollided;    }
	void  setJustCollided ( bool i )						{ m_bJustCollided = i;		 }


	virtual void VOnResourceAcquire ( void );
	virtual void VOnUpdate ( f32 fTimestep );
};

#endif