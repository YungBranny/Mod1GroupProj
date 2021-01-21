#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"

#include "GCObjExitDoor.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS ( CGCObjExitDoor );

CGCObjExitDoor::CGCObjExitDoor( void )
	: CGCObjSpritePhysics ( GetGCTypeIDOf ( CGCObjExitDoor ) )
	, m_pCustomCreationParams ( nullptr )
{

}

void CGCObjExitDoor::VOnResourceAcquire ()
{
	CGCObjSpritePhysics::VOnResourceAcquire ();

	const char* pszPlist_Exit = "TexturePacker/Sprites/Exit/cc_exit.plist"; // Locating PList file animation for Exit
	const char* pszAnim_Exit = "ExitIdle"; // Calling PList animation for Exit

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_Exit)));
}