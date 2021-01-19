#ifndef _CGCOBJLADDER_
#define _CGCOBJLADDER__

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjLadder
	: public CGCObjSpritePhysics
{
private:

public:
	CGCObjLadder ( void );
	virtual ~CGCObjLadder() {};

	GCFACTORY_DECLARE_CREATABLECLASS ( CGCObjLadder );

	virtual void VOnResourceAcquire ( void );
};

#endif