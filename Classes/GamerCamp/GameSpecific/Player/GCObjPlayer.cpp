
#include <memory.h>
#include <fstream>

#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameController/GCController.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

#include "GCObjPlayer.h"

USING_NS_CC;


// action map arrays must match in length - in the templated controller class we use they map from the user define enum to cocos2d::Controller::Key 
static EPlayerActions			s_aePlayerActions[]	= { EPA_AxisMove_X,								EPA_ButtonJump };
static cocos2d::Controller::Key	s_aeKeys[]			= { cocos2d::Controller::Key::JOYSTICK_LEFT_X,	cocos2d::Controller::Key::BUTTON_A };

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CGCObjPlayer );

CGCObjPlayer::CGCObjPlayer ()
	: CGCObjSpritePhysics (GetGCTypeIDOf (CGCObjPlayer))
	, m_fMaximumMoveForce_Horizontal (20.0f)
	, m_fDragCoefficient_Linear (0.25f)
	, m_fDragCoefficient_Square (0.2f)
	, m_fNoInput_ExtraDrag_Square (0.2f)
	, m_fNoInput_VelocityThreshold (0.25f)
	, m_pcControllerActionToKeyMap (nullptr)
	, m_fLivesFontSize (20.0f)
	, m_iLivesTextOutlineSize (1)
	, m_iLivesBarHeightX (695)
	, m_iLivesBarHeightY (500)
	, m_bCanJump (true)
	, m_bOnTravelator (false)
	, m_iNumberOfLives (3)
	, m_v2MovingRightVelocity (15.0f, 0)
	, m_v2MovingLeftVelocity (-m_v2MovingRightVelocity)
	, m_v2MovingUpVelocity (3.0f, 0)
	, m_v2MovingDownVelocity (-m_v2MovingUpVelocity)
	, m_v2StopMovingVelocity (0, 0)
	, m_fStartPositionY (0)
	, m_fEndPositionY (0)
	, m_fDropDistance (0)
	, m_fMaximumDropDistance (20.0f)
	, m_fJumpHeight (12.0f)
	, m_bPlayerDiedFromFalling (false)
	, m_fLivesStartPositionX (1600)
	, m_fLivesStartPositionY (1015)
	, m_fLivesSpacingX (10.0f)
	, m_bIsPlayerOnPlatform (true)
	, m_fTravelatorVelocity (-20.0f)
	//, m_bv2CurrentPos(0,0)
	, m_bChangeAnimation (true)
	, m_iSwitchesHit (0)
	, m_bPlayerLivesCheck(false)
	, m_bLostLife(false)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Pixeled.ttf", m_fLivesFontSize);
	CC_ASSERT(pLabel != nullptr);

	setLivesText(pLabel);

	getLivesText()->setColor(Color3B::WHITE);

	getLivesText()->enableOutline(Color4B::BLACK, m_iLivesTextOutlineSize);

	getLivesText()->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));

	getLivesText()->setString("Lives: " + std::to_string(GetNumberOfLives()));

	//Create all the player lives sprites
	
	m_sprPlayerLoseLives1 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives2 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives3 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	

	m_sprPlayerLives1	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");
	m_sprPlayerLives2	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");
	m_sprPlayerLives3	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");

	//set initial position of the lives ui
	
	getPlayerLivesUI1()->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));
	getPlayerLivesUI2()->setPosition(Vec2(m_fLivesStartPositionX + 75, m_fLivesStartPositionY));
	getPlayerLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 150, m_fLivesStartPositionY));

	m_eChangeAnimation = EChangeAnimation::Idle;

}

void CGCObjPlayer::VOnResourceAcquire()
{
	CGCObjSpritePhysics::VOnResourceAcquire();
	ChangeAnimation ();
}

void CGCObjPlayer::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();

	// reset velocity and flip state
	SetFlippedX( false );
	SetFlippedY( false );
	m_bOnTravelator = false;
	m_bIsPlayerOnPlatform = true;
	m_iSwitchesHit = 0;
	m_bLostLife = false;
	m_bPlayerDiedFromFalling = false;
	// reset
	if( GetPhysicsBody() )
	{
		Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity( b2Vec2( 0.0f, 0.0f ) );
		GetPhysicsBody()->SetTransform( IGCGameLayer::B2dPixelsToWorld( b2Vec2( v2SpritePos.x, v2SpritePos.y ) ), 0.0f );
		GetPhysicsBody()->SetFixedRotation( true );
		m_bv2CurrentPos = GetPhysicsBody ()->GetPosition ();
	}
}

void CGCObjPlayer::VOnUpdate( f32 fTimeStep )
{
	// handle movement
	UpdateMovement(fTimeStep);

	//Dan:When player lives are 0, used externaly 
	if(getPlayerLives() <= 0)
	{
		setPlayerCheckLives(true);
	}

}

void CGCObjPlayer::VOnResourceRelease()
{
    CGCObjSpritePhysics::VOnResourceRelease();
	delete m_pcControllerActionToKeyMap;
	m_pcControllerActionToKeyMap = nullptr;
}

void CGCObjPlayer::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody ()->SetGravityScale (8.0f);
	m_bv2jumpVel = b2Vec2(GetPhysicsBody()->GetLinearVelocity().x, m_fJumpHeight);
}

void CGCObjPlayer::UpdateMovement(f32 fTimeStep)
{
	if (GetVelocity ().y > 3 || GetVelocity ().y < -3)
	{
		m_bCanJump = false;
	}

	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	
	TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, ( *m_pcControllerActionToKeyMap ));

	if (m_bOnTravelator != true)
	{
		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Left))
		{
			if (m_bCanJump == true)
			{
				SetVelocity(cocos2d::Vec2(m_v2MovingLeftVelocity.x, GetVelocity().y));
				SetFlippedX(false);
				m_eChangeAnimation = EChangeAnimation::Run;
				ChangeAnimation ();
			}
		}
		else if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Right))
		{
			if (m_bCanJump == true)
			{

				SetVelocity(cocos2d::Vec2(m_v2MovingRightVelocity.x, GetVelocity().y));
				SetFlippedX(true);
				m_eChangeAnimation = EChangeAnimation::Run;
				ChangeAnimation ();
			}
		}

		else
		{
			if (m_bCanJump == true)
			{
				SetVelocity(cocos2d::Vec2(0, GetVelocity().y));
				m_eChangeAnimation = EChangeAnimation::Idle;
				ChangeAnimation ();
			}
		}
		  
	}
	else if (m_bOnTravelator == true) 
	{
	}
	
	// Jump
	bool bFireWasPressed = false;

	if (cController.IsActive())
	{
		if (cController.ButtonHasJustBeenPressed(EPA_ButtonJump))
		{
			bFireWasPressed = true;
		}
	}
	else
	{
		if (pKeyManager->ActionHasJustBeenPressed(CGCGameLayerPlatformer::EPA_Fire))
		{
			bFireWasPressed = true;
		}
	}

	if (bFireWasPressed && m_bCanJump)
	{
		//GetPhysicsBody()->ApplyForce(m_bv2jumpVel, GetPhysicsBody()->GetWorldCenter(), true);
		m_bCanJump = false;

		m_eChangeAnimation = EChangeAnimation::Jump;
		ChangeAnimation ();
		playJumpAudio();
		if (GetVelocity ().x > 0)
		{
			SetVelocity (cocos2d::Vec2 (GetVelocity ().x, m_v2MovingDownVelocity.x));
			float impulse = GetPhysicsBody ()->GetMass () * 35;
			GetPhysicsBody ()->ApplyLinearImpulse (b2Vec2 (0, impulse * 1.07f), GetPhysicsBody ()->GetWorldCenter (), true);
		};
		if (GetVelocity ().x < 0)
		{
			SetVelocity (cocos2d::Vec2 (GetVelocity ().x, m_v2MovingDownVelocity.x));
			float impulse = GetPhysicsBody ()->GetMass () * 35;
			GetPhysicsBody ()->ApplyLinearImpulse (b2Vec2 (0, impulse* 1.07f), GetPhysicsBody ()->GetWorldCenter (), true);
		};
		if( GetVelocity().x == 0 )
		{
			float impulse = GetPhysicsBody()->GetMass() * 36.5;
			GetPhysicsBody()->ApplyLinearImpulse(b2Vec2(0, impulse), GetPhysicsBody()->GetWorldCenter(), true);
		};
	}
}

//Function to be called when losing a life
void CGCObjPlayer::DecrementLives()
{
	if (m_bLostLife == false)
	{
		m_bLostLife = true;
		m_iNumberOfLives--;
		//getLivesText()->setString("Lives: " + std::to_string(GetNumberOfLives()));
		LivesUI ();
	}
}

//Function to reset lives
void CGCObjPlayer::ResetLives()
{
	//m_iNumberOfLives = 3;
}

void CGCObjPlayer::FallDamage()
{
	if( m_bCanJump == false)
	{
		m_fStartPositionY = GetPhysicsBody()->GetPosition().y;
		m_fDropDistance = m_fStartPositionY - m_fMaximumDropDistance;
	}

	else if( m_bCanJump == true )
	{
		m_fEndPositionY = GetPhysicsBody()->GetPosition().y;

		if( m_fEndPositionY <= m_fDropDistance )
		{
			CCLOG("Player dead.");
			m_bPlayerDiedFromFalling = true;
		}
		m_bPlayerDiedFromFalling = false;
		m_fStartPositionY = GetPhysicsBody()->GetPosition().y;
		m_fEndPositionY = GetPhysicsBody()->GetPosition().y;
		m_fDropDistance = 0;
	}
}
void CGCObjPlayer::LivesUI()
{
	if (m_iNumberOfLives == 0)
	{
		
		
		getPlayerLivesUI1()->setVisible(false);

		getPlayerLivesUI2()->setVisible(false);

		getPlayerLivesUI3()->setVisible(false);

		//Dan: The overlay for the lives which shows a life being lost are moved elsewhere on start up to prevent overdraw
		getPlayerLoseLivesUI1()->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));

		getPlayerLoseLivesUI2()->setPosition(Vec2(m_fLivesStartPositionX + 75, m_fLivesStartPositionY));

		getPlayerLoseLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 150, m_fLivesStartPositionY));
		
	}
	else if (m_iNumberOfLives == 1)
	{
		//Hides player lives ui and moves the lost lives ui into position 
		getPlayerLivesUI2()->setVisible(false);

		getPlayerLivesUI3()->setVisible(false);
	
		getPlayerLoseLivesUI2()->setPosition(Vec2(m_fLivesStartPositionX + 75, m_fLivesStartPositionY));

		getPlayerLoseLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 150, m_fLivesStartPositionY));
	}
	else if (m_iNumberOfLives == 2)
	{
		//Hides player lives ui and moves the lost lives ui into position 
		getPlayerLivesUI3()->setVisible(false);
		
		getPlayerLoseLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 150, m_fLivesStartPositionY));
	}

}

void CGCObjPlayer::ChangeAnimation()
{
	
	const char* pszPlist_Willy = "TexturePacker/Sprites/Willy/Willy.plist";
	const char* pszAnim_WillyRun = "Run";
	const char* pszAnim_WillyIdle = "Idle";
	const char* pszAnim_WillyJump = "Jump";
	static int switchAnim = 0;

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);

	switch (m_eChangeAnimation)
	{

	case EChangeAnimation::Run:
	{
		if (switchAnim != 1)
		{
			switchAnim = 1;
			StopAction ();
			RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_WillyRun)));
		}
	}
	break;
	case EChangeAnimation::Idle:

	{
		if (switchAnim != 2)
		{
			switchAnim = 2;
			StopAction ();
			RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_WillyIdle)));
		}
	}
	break;

	case EChangeAnimation::Jump:

	{
		if (switchAnim != 3)
		{
			switchAnim = 3;
			StopAction ();
			RunAction (GCCocosHelpers::CreateAnimationActionLoop (GCCocosHelpers::CreateAnimation (dicPList, pszAnim_WillyJump)));
		}
	}
	break;
	}

	m_pcControllerActionToKeyMap = TCreateActionToKeyMap( s_aePlayerActions, s_aeKeys );

}

void CGCObjPlayer::playJumpAudio()
{
	m_pcJumpSoundEffectAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcJumpSoundEffectAudio->playEffect("Sounds/Jumping/jump_up.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

//void CGCObjPlayer::playJumpDownAudio()
//{
//	m_pcJumpSoundEffectAudio = CocosDenshion::SimpleAudioEngine::getInstance();
//	m_pcJumpSoundEffectAudio->playEffect("Sounds/Jumping/jump_down.wav", false); // Mia: Play Audio by locating File, set to 'False' to not
//}

//void CGCObjPlayer::playRunAudio()
//{
//	m_pcJumpSoundEffectAudio = CocosDenshion::SimpleAudioEngine::getInstance();
//	m_pcJumpSoundEffectAudio->playEffect("Sounds/wilfred_run_1.mp3", false); // Mia: Play Audio by locating File, set to 'False' to not
//}

void CGCObjPlayer::PlayerLivesReadFile()
{
	//Dan : opens txt file  then read the value inside 
	std::ifstream readFile;
	readFile.open("Lives.txt");

	if (readFile.is_open())
	{
		readFile >> m_iNumberOfLives;
	}
	readFile.close();
};

void CGCObjPlayer::PlayerLivesWriteFile()
{
	//Dan : opens txt file  then writes the value inside 
	std::ofstream writeFile;
	writeFile.open("Lives.txt");

	if (writeFile.is_open())
	{
		writeFile << m_iNumberOfLives;
		writeFile.close();
	}


}

