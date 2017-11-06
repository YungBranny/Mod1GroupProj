////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJITEMS_H_
#define _GCOBJITEMS_H_

#include "../../GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjItem
: public CGCObjSpritePhysics
{
public:

	CGCObjItem(	void )
	: CGCObjSpritePhysics( GetGCTypeIDOf( CGCObjItem ) )
	{}

	virtual void VOnResourceAcquire( void ) override;
};


#endif
