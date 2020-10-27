#ifndef _GCBASICENEMIES_
#define _GCBASICENEMIES_


//Brandon Middleton
//This class is used for a basic enemy (spike/Hazard)

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCBasicEnemies
:	public CGCObjSpritePhysics
{
private:
	float m_fGravity;										//float for gravity

public:
	
	CGCBasicEnemies ();										//constructor
	virtual ~CGCBasicEnemies () {};							//deconstructor

	float getGravity ()			{ return m_fGravity;	}	//Getter and setter for gravity
	void  setGravity (float i)  { m_fGravity = i;		}	//Getter and setter for gravity

											  

								
	virtual void VOnResourceAcquire (void)	;				//Default Functions
	virtual void VOnResurrected		(void)	;				//Default Functions
	virtual void VOnResourceRelease (void)	;				//Default Functions
	virtual void VOnReset			(void)	;				//Default Functions
							  
	virtual void VOnUpdate (f32 fTimestep);					//Update
	
};

#endif
