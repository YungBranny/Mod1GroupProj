#ifndef	_GCOBJTIMEPICKUP_H_
#define	_GCOBJTIMEPICKUP_H_

//Header File for 'CGCObjTimePickUp' created by Mehak Hussain on 19/10/2020.

#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjTimePickUp
	: public CGCObjSpritePhysics
{
private:
	float					m_fTimeGravity;

	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

public:
	CGCObjTimePickUp(void);
	virtual ~CGCObjTimePickUp();

	//CGCObjItem* m_pcGCOKeys;

	float getGravity() { return m_fTimeGravity; } // use const and put in cpp
	void  setGravity(float i) { m_fTimeGravity = i; }

	unsigned short int getCollisionBuffer() const { return m_iCollisionBuffer; }
	void  setCollisionBuffer(unsigned short int i) { m_iCollisionBuffer = i; }

	bool  getJustCollided() const { return m_bJustCollided; }
	void  setJustCollided(bool i) { m_bJustCollided = i; }


	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnResourceRelease(void);
	virtual void VOnReset(void);
	virtual void VOnUpdate(f32 fTimestep);
};

#endif