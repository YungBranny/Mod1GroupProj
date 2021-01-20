#ifndef _CGCOBJEXITDOOR_
#define _CGCOBJEXITDOOR__

/////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjDoor' Header File and Class File was created and was managed by Mehak Hussain.       //
// The purpose of this Class is to create the Exit Door that the Player is able to use after they  //
// collect the amount of Keys needed to progress. The Exit Door is locked until the Player obtains //
// the Keys needed to unlock it. In this Class, I set the physics and creation of the Exit Door.   //     
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjExitDoor
	: public CGCObjSpritePhysics
{
private:
	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
public:
	CGCObjExitDoor ( void );
	virtual ~CGCObjExitDoor () {};

	GCFACTORY_DECLARE_CREATABLECLASS ( CGCObjExitDoor );

	virtual void VOnResourceAcquire ( void );
};
#endif
