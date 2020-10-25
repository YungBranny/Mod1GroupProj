#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCObjMovingPlatform.h"

CGCMovingPlatform::CGCMovingPlatform()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCMovingPlatform))
{

}

CGCMovingPlatform::~CGCMovingPlatform()
{

}

IN_CPP_CREATION_PARAMS_DECLARE(CGCMovingPlatform, "TexturePacker/Sprites/Platform/platform.plist", "platform", b2_dynamicBody, true);
void CGCMovingPlatform::VOnResourceAcquire()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCMovingPlatform);

	CGCObjSpritePhysics::VOnResourceAcquire();

	// animate!
	cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	//RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}