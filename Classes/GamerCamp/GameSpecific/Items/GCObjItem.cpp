////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
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

