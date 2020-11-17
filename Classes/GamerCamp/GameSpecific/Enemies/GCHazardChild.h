#ifndef _GCHazardChild_
#define _GCHazardChild_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCHazardChild
	: public CGCObjSpritePhysics
{
public:
	GCHazardChild ();
	virtual ~GCHazardChild () {};

	GCFACTORY_DECLARE_CREATABLECLASS (GCHazardChild);

};

#endif