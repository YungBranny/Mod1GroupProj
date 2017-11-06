////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GCOBJITEMS_H_
	#include "GCObjItem.h"
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
void CGCObjItem::VOnResourceAcquire( void )
{
	const char* pszPlist		= "TexturePacker/Sprites/Coin/Coin.plist";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pszPlist );
	AcquireResources( pszPlist, "coin", b2_dynamicBody, true );
	SetParent( IGCGameLayer::ActiveInstance() );
}

