#ifndef _CGCOBJBASICPLATFORM6_
#define _CGCOBJBASICPLATFORM6__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform6
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform6);

	GCObjBasicPlatform6 ();				//constructor
	virtual ~GCObjBasicPlatform6 () {};	//deconstuctor


};

#endif
