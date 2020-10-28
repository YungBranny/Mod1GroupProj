#ifndef _CGCOBJDOOR_
#define _CGCOBJDOOR__

/////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjDoor' Header File and Class File was created and is managed by Mehak Hussain.        //
// The purpose of this Class is to create the Exit Door that the Player is able to use after they  //
// collect the amount of Keys needed to progress. The Exit Door is locked until the Player obtains //
// the Keys needed to unlock it. In this Class, I set the physics and creation of the Exit Door.   //     
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjDoor
	: public CGCObjSpritePhysics
{
private:

public:
	CGCObjDoor ( void );
	virtual ~CGCObjDoor () {};

	virtual void VOnResourceAcquire ( void );
};

#endif
