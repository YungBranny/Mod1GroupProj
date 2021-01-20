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

static EPlayerActions			s_aePlayerActions[]	= { EPA_AxisMove_X,								EPA_ButtonJump };
static cocos2d::Controller::Key	s_aeKeys[]			= { cocos2d::Controller::Key::JOYSTICK_LEFT_X,	cocos2d::Controller::Key::BUTTON_A };

GCFACTORY_IMPLEMENT_CREATEABLECLASS ( CGCObjPlayer );

CGCObjPlayer::CGCObjPlayer ()
	: CGCObjSpritePhysics ( GetGCTypeIDOf ( CGCObjPlayer ) )
	, m_fMaximumMoveForce_Horizontal ( 20.0f  )
	, m_fDragCoefficient_Linear		 ( 0.25f  )
	, m_fDragCoefficient_Square		 ( 0.2f   )
	, m_fNoInput_ExtraDrag_Square	 ( 0.2f   )
	, m_fNoInput_VelocityThreshold	 ( 0.25f  )
	, m_fTravelatorVelocity			 ( -20.0f )
	, m_iNumberOfLives				 ( 3 )
	, m_iSwitchesHit				 ( 0 )
	, m_fStartPositionY				 ( 0 )      // Mia: Players start position for fall damage
	, m_fEndPositionY				 ( 0 )      // Mia: Players end position for fall damage
	, m_fDropDistance				 ( 0 )      // Mia: Default Player drop distance set to 0
	, m_fMaximumDropDistance		 ( 20.0f  ) // Mia: Players maximum drop distance for fall damage
	, m_fJumpHeight					 ( 12.0f  )
	, m_fLivesStartPositionX		 ( 1600   )
	, m_fLivesStartPositionY		 ( 1015   )
	, m_v2MovingRightVelocity		 ( 15.0f, 0 )
	, m_v2MovingUpVelocity			 ( 3.0f, 0  )
	, m_v2MovingLeftVelocity		 ( -m_v2MovingRightVelocity )
	, m_v2MovingDownVelocity		 ( -m_v2MovingUpVelocity    )
	, m_bCanJump					 ( true    )
	, m_bIsPlayerOnPlatform			 ( true    )
	, m_bOnTravelator				 ( false   )
	, m_bPlayerDiedFromFalling		 ( false   ) // Mia: Default is set to false
	, m_bLostLife					 ( false   )
	, m_pcControllerActionToKeyMap   ( nullptr )
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//Create all the player lives sprites
	//These are the sprites for when the player has lost a life
	m_sprPlayerLoseLives1 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives2 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives3 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	
	//These are the sprites when a player has a life
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

void CGCObjPlayer::VOnReset() //Brandon reset function
{
	CGCObjSpritePhysics::VOnReset();

	// reset velocity and flip state	   //Variables which need to be reset when the player dies
	SetFlippedX( false );				   //Variables which need to be reset when the player dies
	SetFlippedY( false );				   //Variables which need to be reset when the player dies
	m_bOnTravelator = false;			   //Variables which need to be reset when the player dies
	m_bIsPlayerOnPlatform = true;		   //Variables which need to be reset when the player dies
	m_iSwitchesHit = 0;					   //Variables which need to be reset when the player dies
	m_bLostLife = false;				   //Variables which need to be reset when the player dies
	m_bPlayerDiedFromFalling = false;	   //Variables which need to be reset when the player dies
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

void CGCObjPlayer::UpdateMovement(f32 fTimeStep) //Brandon Movement function 
{
	if (GetVelocity ().y > 3 || GetVelocity ().y < -3) //stops the player from jumping when he is falling/ in air
	{
		m_bCanJump = false;
	}

	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	
	TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, ( *m_pcControllerActionToKeyMap ));

	if (m_bOnTravelator != true) //if statements to determine which way the player should move and if the player can move
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
	
	// Brandon Jump enables the jump and triggers the jump animation
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

	if (bFireWasPressed && m_bCanJump) //Allows the player to jump, the jump height/distance varies on which direction the player is moving or if the player is still
	{
		m_bCanJump = false;
		m_eChangeAnimation = EChangeAnimation::Jump;
		ChangeAnimation ();
		playJumpAudio(); // Mia: Triggers jump audio for when Player jumps
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
		LivesUI ();
	}
}

// Mia: This function is for the Players fall damage. The drop distance is calculated by getting the Players position then minus what I set as 
// the maximum drop distance. If Players position exceeds the drop distance, the Player recieves fall damage
void CGCObjPlayer::FallDamage()
{
	if( m_bCanJump == false)
	{
		m_fStartPositionY = GetPhysicsBody()->GetPosition().y; // Mia: Grabs the start position of Player along Y axis
		m_fDropDistance = m_fStartPositionY - m_fMaximumDropDistance; // Mia: Grabs drop distance Player has fallen from
	}

	else if( m_bCanJump == true )
	{
		m_fEndPositionY = GetPhysicsBody()->GetPosition().y; // Mia: Grabs the end position of Player along Y axis

		if( m_fEndPositionY <= m_fDropDistance ) // Mia: If Players end position is less than or equal to the drop distance
		{
			CCLOG("Player dead."); // Mia: For testing, to show in the ouput the Player has received fall damage
			m_bPlayerDiedFromFalling = true; // Mia: Changes bool to true
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

void CGCObjPlayer::ChangeAnimation() //Brandon - chooses the animation depending on if the player is jumping, moving or still
{
	
	const char* pszPlist_Willy = "TexturePacker/Sprites/Willy/Willy.plist";	 //Charatcer plist
	const char* pszAnim_WillyRun = "Run";									 //Animation Names
	const char* pszAnim_WillyIdle = "Idle";									 //Animation Names
	const char* pszAnim_WillyJump = "Jump";									 //Animation Names
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