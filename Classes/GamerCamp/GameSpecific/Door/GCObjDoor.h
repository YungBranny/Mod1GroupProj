
#ifndef _CGCOBJDOOR_
#define _CGCOBJDOOR__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjDoor
	: public CGCObjSpritePhysics
{
private:

	cocos2d::Vec2 m_v2StartPos;

	float m_keysGravity;

public:

	CGCObjDoor ();
	virtual ~CGCObjDoor () {};

	//cocos2d::Vec2 GetStartPos () { return m_v2StartPos; }
	//void SetStartPos (cocos2d::Vec2 i) { m_v2StartPos = i; }

	float getGravity() { return m_keysGravity; } // use const and put in cpp
	void  setGravity(float i) { m_keysGravity = i; }

	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);

	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
