#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingBasicPlatform.h"


#include "GCEnemyMovementCollider2.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjEnemyMovementCollider2);

GCObjEnemyMovementCollider2::GCObjEnemyMovementCollider2 ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (GCObjEnemyMovementCollider2))
{

}