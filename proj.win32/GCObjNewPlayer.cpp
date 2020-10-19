#include <memory.h>

#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameController/GCController.h"

#include "GCObjNewPlayer.h"

USING_NS_CC;

static EPlayerActions			s_aePlayerActions[] = { EPA_AxisMove_X,								EPA_AxisMove_Y,								EPA_ButtonFire };
static cocos2d::Controller::Key	s_aeKeys[] = { cocos2d::Controller::Key::JOYSTICK_LEFT_X,	cocos2d::Controller::Key::JOYSTICK_LEFT_Y,	cocos2d::Controller::Key::BUTTON_A };

CGCObjNewPlayer::CGCObjNewPlayer()
	: m_fMovementSpeedx(0.2f)
	, m_fJumpPower(0.2f)
	, m_bCanJump(true)
	, m_pcControllerActionToKeyMap(nullptr)
	, m_v2MovementSpeed(m_fMovementSpeedx, 0)
{
}

IN_CPP_CREATION_PARAMS_DECLARE(CGCObjNewPlayer, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);
//virtual 
void CGCObjNewPlayer::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjNewPlayer);

	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszAnim_marioJog = "Jog";

	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_marioJog)));

	m_pcControllerActionToKeyMap = TCreateActionToKeyMap(s_aePlayerActions, s_aeKeys);

}

void CGCObjNewPlayer::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();

	// reset velocity and flip state
	SetFlippedX(false);
	SetFlippedY(false);

	// reset
	if (GetPhysicsBody())
	{
		Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody()->SetFixedRotation(true);
	}
}

void CGCObjNewPlayer::VOnUpdate(f32 fTimeStep)
{
	// handle movement
	UpdateMovement(fTimeStep);
}

void CGCObjNewPlayer::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();
	delete m_pcControllerActionToKeyMap;
	m_pcControllerActionToKeyMap = nullptr;
}

f32 m_fSpeed = 10.0f;
f32 m_fJumpPower = 20.0f;
bool m_bCanJump = true;

void CGCObjNewPlayer::UpdateMovement(f32 fTimeStep)
{


	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerActionToKeyMap));

	if (cController.IsActive())
	{
		Vec2 v2LeftStickRaw = cController.GetCurrentStickValueRaw(EPA_AxisMove_X, EPA_AxisMove_Y);

	}
	else
	{
		//	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Up ) )
		//	{
		//		v2ControlForceDirection.y   = 1.0f;
		//		fIsInputInactive            = 0.0f;
		//	}
		//	if( pKeyManager->ActionIsPressed( CGCGameLayerPlatformer::EPA_Down ) )
		//	{
		//		v2ControlForceDirection.y	= -1.0f;
		//		fIsInputInactive            = 0.0f;
		//	}

		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Left))
		{
			SetVelocity(-m_v2MovementSpeed);
		}
		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Right))
		{
			SetVelocity(m_v2MovementSpeed);
		}
	}
}