#ifndef _CGCOBJBASICPLATFORM4_
#define _CGCOBJBASICPLATFORM4__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform4
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform4);

	GCObjBasicPlatform4 ();				//constructor
	virtual ~GCObjBasicPlatform4 () {};	//deconstuctor



};

#endif
