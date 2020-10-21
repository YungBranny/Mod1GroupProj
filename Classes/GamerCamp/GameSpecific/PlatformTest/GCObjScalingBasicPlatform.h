#ifndef _CGCOBJSCALINGBASICPLATFORM_
#define _CGCOBJSCALINGBASICPLATFORM__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjScalingBasicPlatform
	: public CGCObjSpritePhysics
{
private:


public:

	CGCObjScalingBasicPlatform ();
	virtual ~CGCObjScalingBasicPlatform () {};


	void createScalingPlatforms ();

	virtual void VOnResourceAcquire (void);


	//virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
