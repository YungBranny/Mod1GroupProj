#ifndef _GCOBJMOVINGPLATFORM_
#define _GCOBJMOVINGPLATFORM_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCMovingPlatform
	:public CGCObjSpritePhysics

{
private:


public:

	CGCMovingPlatform();
	virtual ~CGCMovingPlatform() {};

	virtual void VOnResourceAcquire(void);

};

#endif
