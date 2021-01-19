#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjExitDoor.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS ( CGCObjExitDoor );

CGCObjExitDoor::CGCObjExitDoor( void )
	: CGCObjSpritePhysics ( GetGCTypeIDOf ( CGCObjExitDoor ) ) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Exit Door
	, m_pCustomCreationParams ( nullptr )
{

}

void CGCObjExitDoor::VOnResourceAcquire ()
{
	CGCObjSpritePhysics::VOnResourceAcquire ();

	const char* pszPlist_Exit = "TexturePacker/Sprites/Exit/cc_exit.plist";
	const char* pszAnim_Exit = "ExitIdle";

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_Exit)));
}