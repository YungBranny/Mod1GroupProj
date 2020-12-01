#ifndef _GCLEVELBACKGROUND_
#define _GCLEVELBACKGROUND_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCLevelBackground
	: public CGCObjSpritePhysics
{
public:
	CGCLevelBackground();
	virtual ~CGCLevelBackground() {};

	GCFACTORY_DECLARE_CREATABLECLASS(CGCLevelBackground);

};

#endif