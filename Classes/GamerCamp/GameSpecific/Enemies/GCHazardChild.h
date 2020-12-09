#ifndef _GCHazardChild_
#define _GCHazardChild_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCHazardChild
	: public CGCObjSpritePhysics
{
public:
	GCHazardChild ();
	virtual ~GCHazardChild () {};

	GCFACTORY_DECLARE_CREATABLECLASS (GCHazardChild);

	void GCHazardChild::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);

private:

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
};

#endif