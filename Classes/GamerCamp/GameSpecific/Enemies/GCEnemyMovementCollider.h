#ifndef _GCENEMYMOVEMENTCOLLIDER_
#define _GCENEMYMOVEMENTCOLLIDER__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjEnemyMovementCollider
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjEnemyMovementCollider);

	GCObjEnemyMovementCollider ();				//constructor
	virtual ~GCObjEnemyMovementCollider () {};	//deconstuctor





};

#endif
