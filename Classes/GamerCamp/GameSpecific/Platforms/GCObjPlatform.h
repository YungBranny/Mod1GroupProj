////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJPLATFORMS_H_
#define _GCOBJPLATFORMS_H_

#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjPlatform
	: public CGCObjSpritePhysics
{
public:
	GCFACTORY_DECLARE_CREATABLECLASS( CGCObjPlatform );

	CGCObjPlatform(	void )
		: CGCObjSpritePhysics( GetGCTypeIDOf( CGCObjPlatform ) )
	{}
};


#endif