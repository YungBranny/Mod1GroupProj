#ifndef _GCBASICENEMIES_
#define _GCBASICENEMIES_


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCBasicEnemies
:	public CGCObjSpritePhysics
{
private:
	float m_fGravity;

public:
	
	CGCBasicEnemies ();
	virtual ~CGCBasicEnemies () {};

	float getGravity ()			{ return m_fGravity;	}
	void  setGravity (float i)  { m_fGravity = i;		}

											  

								
	virtual void VOnResourceAcquire (void)	;
	virtual void VOnResurrected		(void)	;
	virtual void VOnResourceRelease (void)	;
	virtual void VOnReset			(void)	;
							  
	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();




	
};




#endif
