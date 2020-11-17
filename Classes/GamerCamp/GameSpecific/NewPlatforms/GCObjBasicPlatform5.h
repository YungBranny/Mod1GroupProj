#ifndef _CGCOBJBASICPLATFORM5_
#define _CGCOBJBASICPLATFORM5__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform5
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform5);

	GCObjBasicPlatform5 ();				//constructor
	virtual ~GCObjBasicPlatform5 () {};	//deconstuctor




};

#endif
