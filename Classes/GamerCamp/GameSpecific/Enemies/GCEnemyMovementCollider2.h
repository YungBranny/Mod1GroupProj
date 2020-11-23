#ifndef _GCENEMYMOVEMENTCOLLIDER2_
#define _GCENEMYMOVEMENTCOLLIDER2__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjEnemyMovementCollider2
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjEnemyMovementCollider2);

	GCObjEnemyMovementCollider2 ();				//constructor
	virtual ~GCObjEnemyMovementCollider2 () {};	//deconstuctor





};

#endif
