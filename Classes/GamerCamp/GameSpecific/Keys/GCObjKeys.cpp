#include <memory.h>

#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

//Class File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

using namespace cocos2d;

CGCObjKeys::CGCObjKeys(void)
	: CGCObjSpritePhysics(GetGCTypeIDOf(CGCObjKeys))
	, m_keysGravity (0.0f)
{
	//m_keysGravity = 0.0f;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const char* keysSprite = "TexturePacker/Sprites/Coin/Coin.plist";
	{
		//m_pcGCOKeys = new CGCObjItem();
		//if( nullptr != m_pcGCOKeys )
		//{
		//	m_pcGCOKeys->CreateSprite(keysSprite);
		//	m_pcGCOKeys->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		//	m_pcGCOKeys->SetParent(IGCGameLayer::ActiveInstance());
		//	m_pcGCOKeys->GetPhysicsBody()->SetGravityScale(0.0f);
		//}

		CreateSprite(keysSprite);
		SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		SetParent(IGCGameLayer::ActiveInstance());
		//GetPhysicsBody()->SetGravityScale(0.0f);
	}
}

CGCObjKeys::~CGCObjKeys()
{

}

IN_CPP_CREATION_PARAMS_DECLARE(CGCObjKeys, "TexturePacker/Sprites/Coin/Coin.plist", "coin", b2_dynamicBody, true);
//virtual 
void CGCObjKeys::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjKeys);
	CGCObjSpritePhysics::VOnResourceAcquire();
}


void CGCObjKeys::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();


}
void CGCObjKeys::VOnUpdate(f32 fTimestep)
{
}

void CGCObjKeys::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

}
void CGCObjKeys::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody()->SetGravityScale(getGravity());
}