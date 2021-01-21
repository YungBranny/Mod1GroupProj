#ifndef _CGCOBJBASICPLATFORM3_
#define _CGCOBJBASICPLATFORM3__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform3
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform3);

	GCObjBasicPlatform3 ();				//constructor
	virtual ~GCObjBasicPlatform3 () {};	//deconstuctor





};

#endif
