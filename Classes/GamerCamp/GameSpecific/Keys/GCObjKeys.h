#ifndef	_GCOBJKEYS_H_
#define	_GCOBJKEYS_H_

//Header File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

#include "GamerCamp/GameSpecific/Items/GCObjItem.h" // We use header files to pull in declarations from another file.
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
//#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

class CGCObjKeys
	: public CGCObjSpritePhysics // chnange to item and in platformer if we have more than just keys
{
private:
	float m_keysGravity;

public:
	CGCObjKeys(void);
	virtual ~CGCObjKeys();

	//CGCObjItem* m_pcGCOKeys;

	float getGravity() { return m_keysGravity; } // use const and put in cpp
	void  setGravity(float i) { m_keysGravity = i; }


	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnResourceRelease(void);
	virtual void VOnReset(void);

	virtual void VOnUpdate(f32 fTimestep);
};

#endif