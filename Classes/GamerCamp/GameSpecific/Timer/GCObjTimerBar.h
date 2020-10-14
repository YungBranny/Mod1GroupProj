#ifndef _CGCOBJTIMERBAR_
#define _CGCOBJTIMERBAR__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjTimerBar
	: public CGCObjSpritePhysics
{
private:

	cocos2d::Vec2 m_v2TimerBarStartPos;

	
public:

	CGCObjTimerBar();
	virtual ~CGCObjTimerBar() {};


	//make varible for pos 

	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnResourceRelease(void);
	virtual void VOnReset(void);

	virtual void VOnUpdate(f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
