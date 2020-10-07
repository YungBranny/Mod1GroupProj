#ifndef _GCBASICENEMIES_
#define _GCBASICENEMIES_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

class CGCBasicEnemies
	:CGCObjSpritePhysics
{
private:


public:
	CGCBasicEnemies ();

	virtual ~CGCBasicEnemies() {}

	virtual void VOnResourceAcquire (void)				override;
	virtual void VOnResurrected		(void)				override;
	virtual void VOnUpdate			(f32 fTimestep)		override;




	
};




#endif
