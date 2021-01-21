#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "../../GCCocosInterface/GB2ShapeCache-x.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjScalingBasicPlatform.h"


#include "GCEnemyMovementCollider.h"


GCFACTORY_IMPLEMENT_CREATEABLECLASS (GCObjEnemyMovementCollider);

GCObjEnemyMovementCollider::GCObjEnemyMovementCollider ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (GCObjEnemyMovementCollider))
{

}