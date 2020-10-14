#ifndef _CGCOBJPLATFORMTEST_
#define _CGCOBJPLATFORMTEST__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjPlatformTest
	: public CGCObjSpritePhysics
{
private:

public:

	CGCObjPlatformTest ();
	virtual ~CGCObjPlatformTest () {};




	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);

	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
