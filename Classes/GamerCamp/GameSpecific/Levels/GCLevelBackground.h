#ifndef _GCLEVELBACKGROUND_
#define _GCLEVELBACKGROUND_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCLevelBackground
	: public CGCObjSpritePhysics
{
private:
	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
public:
	CGCLevelBackground();
	virtual ~CGCLevelBackground() {};

	GCFACTORY_DECLARE_CREATABLECLASS(CGCLevelBackground);

	virtual void VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);

};

#endif