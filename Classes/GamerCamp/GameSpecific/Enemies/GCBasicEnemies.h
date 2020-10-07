#ifndef _GCBASICENEMIES_
#define _GCBASICENEMIES_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

class CGCBasicEnemies
:	public CGCObjSpritePhysics
{
private:


public:
	CGCBasicEnemies ();
											  
	virtual ~CGCBasicEnemies () {};
								
	virtual void VOnResourceAcquire (void)	;
	virtual void VOnResurrected		(void)	;
	virtual void VOnResourceRelease (void)	;
	virtual void VOnReset			(void)	;
							  
	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();




	
};




#endif
