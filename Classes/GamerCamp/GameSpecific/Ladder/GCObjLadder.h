#ifndef _CGCOBJLADDER_
#define _CGCOBJLADDER_

///////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjLadder' Header File and Class File was created and was managed by Mehak Hussain.       //
// The purpose of this Class is to create the Ladders used in Level 13 and 15.                       //
// In this Class, I set the creation for the Ladders to be used in Ogmo.                             //
///////////////////////////////////////////////////////////////////////////////////////////////////////

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