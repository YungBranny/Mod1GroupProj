#ifndef _GCOLIGHTMECHANIC_
#define _GCOLIGHTMECHANIC_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCOLightMechanic
	: public CGCObjSpritePhysics
{
public:
	GCOLightMechanic();
	virtual ~GCOLightMechanic() {};

	GCFACTORY_DECLARE_CREATABLECLASS(GCOLightMechanic);

	void GCOLightMechanic::VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);

private:

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
};

#endif