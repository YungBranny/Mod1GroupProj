#ifndef _CGCOBJBASICPLATFORM1_
#define _CGCOBJBASICPLATFORM1__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform1
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform1);

	GCObjBasicPlatform1 ();				//constructor
	virtual ~GCObjBasicPlatform1 () {};	//deconstuctor



};

#endif
