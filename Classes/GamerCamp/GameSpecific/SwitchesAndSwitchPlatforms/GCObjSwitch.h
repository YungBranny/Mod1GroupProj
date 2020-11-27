#ifndef _CGCOBJSWITCH_
#define _CGCOBJSWITCH__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"



class CGCObjSwitch
	: public CGCObjSpritePhysics
{
public:

	GCFACTORY_DECLARE_CREATABLECLASS (CGCObjSwitch);

	CGCObjSwitch ();				//constructor
	virtual ~CGCObjSwitch () {};	//deconstuctor

	virtual void VOnResourceAcquire (void);
};

#endif
