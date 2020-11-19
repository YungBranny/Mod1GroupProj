
#ifndef _CGCOBJBASEPLATFORM_
#define _CGCOBJBASEPLATFORM__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasePlatform
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasePlatform);

	GCObjBasePlatform ();				//constructor
	virtual ~GCObjBasePlatform () {};	//deconstuctor



};

#endif
