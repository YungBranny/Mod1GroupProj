#ifndef _CGCOBJLADDER_
#define _CGCOBJLADDER__

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjLadder
	: public CGCObjSpritePhysics
{
private:
	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams; 
public:
	CGCObjLadder ( void );
	virtual ~CGCObjLadder() {};

	GCFACTORY_DECLARE_CREATABLECLASS ( CGCObjLadder );

	virtual void VHandleFactoryParams ( const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition );
};
#endif