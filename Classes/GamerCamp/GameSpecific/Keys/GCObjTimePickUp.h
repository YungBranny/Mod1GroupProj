#ifndef	_GCOBJTIMEPICKUP_H_
#define	_GCOBJTIMEPICKUP_H_

//Header File for 'CGCObjTimePickUp' created by Mehak Hussain on 19/10/2020.

#include "GamerCamp/GameSpecific/Items/GCObjItem.h" // We use header files to pull in declarations from another file.
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
//#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

class CGCObjTimePickUp
	: public CGCObjSpritePhysics // change to item and in platformer if we have more than just keys
{
private:
	float m_timeGravity;

	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

public:
	CGCObjTimePickUp(void);
	virtual ~CGCObjTimePickUp();

	//CGCObjItem* m_pcGCOKeys;

	float getGravity() { return m_timeGravity; } // use const and put in cpp
	void  setGravity(float i) { m_timeGravity = i; }

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