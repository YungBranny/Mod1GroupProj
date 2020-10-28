#include "GCObjExitDoor.h"

CGCObjExitDoor::CGCObjExitDoor( void )
	: CGCObjSpritePhysics ( GetGCTypeIDOf (CGCObjExitDoor) ) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Exit Door
{

}

// Create the Exit Door Sprite, give it a Static Physics Body which means it won't move and then set fixed rotation to 'True'
IN_CPP_CREATION_PARAMS_DECLARE (CGCObjExitDoor, "TexturePacker/Sprites/Door/Door.plist", "Door", b2_staticBody, true );
void CGCObjExitDoor::VOnResourceAcquire ()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjExitDoor);

	CGCObjSpritePhysics::VOnResourceAcquire ();
}