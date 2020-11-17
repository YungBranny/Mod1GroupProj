#pragma once
#ifndef _CGCOBJBASICPLATFORM7_
#define _CGCOBJBASICPLATFORM7__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"


class GCObjBasicPlatform7
	: public CGCObjSpritePhysics
{
private:

public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCObjBasicPlatform7);

	GCObjBasicPlatform7 ();				//constructor
	virtual ~GCObjBasicPlatform7 () {};	//deconstuctor




};

#endif
