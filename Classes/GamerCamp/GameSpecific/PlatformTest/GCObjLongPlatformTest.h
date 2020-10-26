#ifndef _CGCOBJLongPLATFORMTEST_
#define _CGCOBJLongPLATFORMTEST__

//Brandon Middleton

//This class spawns a longer platform than the default short one

//This class is no longer being used as I have made a scalable platform class which makes this
//class no longer needed




#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjLongPlatformTest
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2StartPos;									// This just gets a vector 2 which is set as the start and reset position for the platform

public:

	CGCObjLongPlatformTest ();									//Constructor
	virtual ~CGCObjLongPlatformTest () {};						//Deconstructor

	cocos2d::Vec2 GetStartPos () { return m_v2StartPos; }		//getter for the start position
	void SetStartPos (cocos2d::Vec2 i) { m_v2StartPos = i; }	//Setter for the start position

	virtual void VOnResourceAcquire (void);						//default functions needed for sprite physics
	virtual void VOnResurrected (void);							//default functions needed for sprite physics
	virtual void VOnResourceRelease (void);						//default functions needed for sprite physics
	virtual void VOnReset (void);								//default functions needed for sprite physics

	virtual void VOnUpdate (f32 fTimestep);						//Update function just incase I ever needed something being updated
};

#endif
