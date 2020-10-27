#ifndef	_GCOBJKEYS_H_
#define	_GCOBJKEYS_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjKeys' Header File and Class File was created and is managed by Mehak Hussain.
// The purpose of this Class is to create the Key Collectables for the Player to collect one by one.
// In this Class, I set the physics and creation of the Keys.
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjKeys
	: public CGCObjSpritePhysics
{
private:
	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

public:
	CGCObjKeys ( void );
	virtual ~CGCObjKeys ();

	unsigned short int getCollisionBuffer	()	const	{	return m_iCollisionBuffer;	}
	void  setCollisionBuffer	(	unsigned short int i	)	{	m_iCollisionBuffer = i;	 }

	bool  getJustCollided	()	const	 {	return m_bJustCollided;	 }
	void  setJustCollided	(	bool i	)	{	m_bJustCollided = i;	 }

	virtual void VOnResourceAcquire ( void );
	virtual void VOnUpdate ( f32 fTimestep );
};

#endif