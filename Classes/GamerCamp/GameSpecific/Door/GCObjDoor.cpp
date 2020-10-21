
#include <memory.h>

//#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

#include "GCObjDoor.h"

using namespace cocos2d;

CGCObjDoor::CGCObjDoor ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjDoor))
	, m_keysGravity(0.0f)
	//, m_v2StartPos (400, 400)
{
	//SetResetPosition (GetStartPos ());

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const char* doorSprite = "TexturePacker/Sprites/Door/Door.plist";
	{
		//m_pcGCOKeys = new CGCObjItem();
		//if( nullptr != m_pcGCOKeys )
		//{
		//	m_pcGCOKeys->CreateSprite(keysSprite);
		//	m_pcGCOKeys->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		//	m_pcGCOKeys->SetParent(IGCGameLayer::ActiveInstance());
		//	m_pcGCOKeys->GetPhysicsBody()->SetGravityScale(0.0f);
		//}

		CreateSprite(doorSprite);
		//SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		SetResetPosition(cocos2d::Vec2(20, 120));
		SetParent(IGCGameLayer::ActiveInstance());
		//GetPhysicsBody()->SetGravityScale(0.0f);

	}
}




IN_CPP_CREATION_PARAMS_DECLARE (CGCObjDoor, "TexturePacker/Sprites/Door/Door.plist", "Door", b2_staticBody, true);
void CGCObjDoor::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCObjDoor);

	CGCObjSpritePhysics::VOnResourceAcquire ();

	//SetResetPosition(cocos2d::Vec2(100, 120));
	//SetResetPosition (GetStartPos ());
	//cocos2d::ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);


}



void CGCObjDoor::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	//SetFlippedX (false);
	//SetFlippedY (false);

	//SetResetPosition (GetStartPos ());
	//if (GetPhysicsBody ())
	//{
	//	cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
	//	GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
	//	GetPhysicsBody ()->SetFixedRotation (true);
	//}

}
void CGCObjDoor::VOnUpdate (f32 fTimestep)
{
}

void CGCObjDoor::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCObjDoor::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody()->SetGravityScale(getGravity());

}





