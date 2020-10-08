#include <memory.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "GCMovingEnemies.h"

using namespace cocos2d;

CGCMovingEnemies::CGCMovingEnemies ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCBasicEnemies))
	, m_eMoveDirection (EMoveDirection::Right)
	, m_bMovingLeftAndRight (Left)
	, m_fEndDestination1	(100,0)
	, m_fEndDesitnation2	(400,0)
{
	
}

cocos2d::Vec2	MovingEnemyRight = cocos2d::Vec2 (3000, 0.0f);
cocos2d::Vec2	MovingEnemyLeft	= ( -MovingEnemyRight );

cocos2d::Vec2	MovingEnemyUp = cocos2d::Vec2 (0.0f, -6.0f);
cocos2d::Vec2	MovingEnemyDown = ( -MovingEnemyDown );




IN_CPP_CREATION_PARAMS_DECLARE (CGCMovingEnemies, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);
void CGCMovingEnemies::VOnResourceAcquire ()
{

	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE (CGCMovingEnemies);

	CGCObjSpritePhysics::VOnResourceAcquire ();

	//const char* pszAnim_marioJog = "Jog";

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist (GetFactoryCreationParams ()->strPlistFile);
	//RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_marioJog)));

}


void CGCMovingEnemies::VOnReset ()
{
	CGCObjSpritePhysics::VOnReset ();
	// reset
	SetFlippedX (false);
	SetFlippedY (false);

	SetResetPosition (cocos2d::Vec2 (100, 100));
	if (GetPhysicsBody ())
	{
		cocos2d::Vec2 v2SpritePos = GetSpritePosition ();
		GetPhysicsBody ()->SetLinearVelocity (b2Vec2 (10.0f, 0.0f));
		GetPhysicsBody ()->SetTransform (IGCGameLayer::B2dPixelsToWorld (b2Vec2 (v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody ()->SetFixedRotation (true);
	}

}


void CGCMovingEnemies::VOnResourceRelease ()
{
	CGCObjSpritePhysics::VOnResourceRelease ();

}
void CGCMovingEnemies::VOnResurrected ()
{
	CGCObjSpritePhysics::VOnResurrected ();
	GetPhysicsBody ()->SetGravityScale (getGravity ());
}


void CGCMovingEnemies::VOnUpdate (f32 fTimeStep)
{
	if (m_bMovingLeftAndRight == true) 
	{
		switch (m_eMoveDirection)
		
	
		{
		case EMoveDirection::Right:
			if(GetSpritePosition().x == m_fEndDestination1.x)
			{
				m_eMoveDirection = EMoveDirection::Left;
			}
			break;
		
		
		case EMoveDirection::Left:
				
			if (GetSpritePosition ().x == m_fEndDesitnation2.x)
			{
				m_eMoveDirection = EMoveDirection::Right;
			}
			break;
	
		}

		if (m_bMovingLeftAndRight == false)
		{
			switch (m_eMoveDirection)
			{
			case EMoveDirection::Up:
				if (GetSpritePosition ().y == m_fEndDestination1.y)
				{
					m_eMoveDirection = EMoveDirection::Down;
				}
				break;


			case EMoveDirection::Down:

				if (GetSpritePosition ().y == m_fEndDesitnation2.y)
				{
					m_eMoveDirection = EMoveDirection::Up;
				}
				break;
			}
		}
	
	}
};