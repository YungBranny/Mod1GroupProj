#ifndef _GCENEMYMOVEMENTCOLLIDER_
#define _GCENEMYMOVEMENTCOLLIDER__


//Brandon Middleton
//This class is an empty item which has a single use that is to be collided with by an enemy and act as a single to make the enemy move the
//other directon

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
