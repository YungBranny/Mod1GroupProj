#ifndef	_GCOBJKEYS_H_
#define	_GCOBJKEYS_H_

//Header File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjKeys
	: public CGCObjSpritePhysics // change to item and in platformer if we have more than just keys
{
private:
	float					m_fKeysGravity;

	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

public:
	CGCObjKeys(void);
	virtual ~CGCObjKeys();

	//CGCObjItem* m_pcGCOKeys;

	float getGravity	()	{	return m_fKeysGravity;	} // use const and put in cpp
	void  setGravity	(	float i	)	{	m_fKeysGravity = i;	}

	unsigned short int getCollisionBuffer	()	const	{	return m_iCollisionBuffer;	}
	void  setCollisionBuffer	(	unsigned short int i	)	{	m_iCollisionBuffer = i;	 }

	bool  getJustCollided	()	const	 {	return m_bJustCollided;	 }
	void  setJustCollided	(	bool i	)	{	m_bJustCollided = i;	 }


	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnResourceRelease(void);
	virtual void VOnReset(void);

	virtual void VOnUpdate(f32 fTimestep);
};

#endif