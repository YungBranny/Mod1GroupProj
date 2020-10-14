#ifndef _CGCOBJLongPLATFORMTEST_
#define _CGCOBJLongPLATFORMTEST__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjLongPlatformTest
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2StartPos;

		

public:

	CGCObjLongPlatformTest ();
	virtual ~CGCObjLongPlatformTest () {};

	cocos2d::Vec2 GetStartPos () { return m_v2StartPos; }
	void SetStartPos (cocos2d::Vec2 i) { m_v2StartPos = i; }

	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);

	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
