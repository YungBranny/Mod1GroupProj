#ifndef _GCOBJBrickPlatform_
#define _GCOBJBrickPlatform_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCObjBrickPlatform
	: public CGCObjSpritePhysics
{
public:
	GCObjBrickPlatform ();
	virtual ~GCObjBrickPlatform () {};

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBrickPlatform);

};

#endif