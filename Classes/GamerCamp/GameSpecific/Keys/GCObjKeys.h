#ifndef	_GCOBJKEYS_H_
#define	_GCOBJKEYS_H_

//Header File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

#include "GamerCamp/GameSpecific/Items/GCObjItem.h" // We use header files to pull in declarations from another file.
#include "../../GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjKeys
	: public CGCObjItem
{
private:
	float m_fGravity;

public:
	CGCObjKeys();
	~CGCObjKeys();

	float getGravity() { return m_fGravity; }
	void  setGravity(float i) { m_fGravity = i; }

	virtual void VOnResurrected(void);

};

#endif