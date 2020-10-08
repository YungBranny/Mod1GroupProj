#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

//Class File for 'CGCObjKeys' created by Mehak Hussain on 6/10/2020.

using namespace cocos2d;

CGCObjKeys::CGCObjKeys()
{
	m_fGravity = 0.0f;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const char* keysSprite = "TexturePacker/Sprites/Coin/Coin.plist";
	{
		m_pcGCOKeys = new CGCObjItem();
		if( nullptr != m_pcGCOKeys )
		{
			m_pcGCOKeys->CreateSprite(keysSprite);
			m_pcGCOKeys->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			m_pcGCOKeys->SetParent(IGCGameLayer::ActiveInstance());
		}
	}
}

CGCObjKeys::~CGCObjKeys()
{

}

void CGCObjKeys::VOnResurrected()
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody()->SetGravityScale(getGravity());
}