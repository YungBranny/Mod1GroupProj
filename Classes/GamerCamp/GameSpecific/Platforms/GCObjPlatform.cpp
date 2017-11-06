////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GCOBJPLATFORMS_H_
	#include "GCObjPlatform.h"
#endif

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlatform::VOnResourceAcquire( void )
{
	const char* pszPlist = "TexturePacker/Sprites/Platform/Platform.plist";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pszPlist );
	AcquireResources( pszPlist, "platform", b2_staticBody, true );
	SetParent( IGCGameLayer::ActiveInstance() );
}
