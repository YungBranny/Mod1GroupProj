#ifndef _GCOBJBrickPlatform_
#define _GCOBJBrickPlatform_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCObjBrickPlatform
	: public CGCObjSpritePhysics
{
private:
	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
public:
	GCObjBrickPlatform ();
	virtual ~GCObjBrickPlatform () {};

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBrickPlatform);
	virtual void VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);
};

#endif