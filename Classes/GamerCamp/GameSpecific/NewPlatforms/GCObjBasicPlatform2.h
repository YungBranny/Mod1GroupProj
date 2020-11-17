#ifndef _CGCOBJBASICPLATFORM2_
#define _CGCOBJBASICPLATFORM2__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform2
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform2);

	GCObjBasicPlatform2 ();				//constructor
	virtual ~GCObjBasicPlatform2 () {};	//deconstuctor



};

#endif
