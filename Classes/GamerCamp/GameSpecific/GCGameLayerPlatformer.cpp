///////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
///////////////////////////////////////////////////////////////////////////////

#include "GCGameLayerPlatformer.h"
#include <algorithm>
#include <stdlib.h> 

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "MenuScene.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h" 
#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"
#include "GamerCamp/GameSpecific/Items/GCObjItem.h" 
#include "GamerCamp/GameSpecific/Items/GCObjGroupItem.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"
#include "GamerCamp/GameSpecific/Timer/GCObjTimer.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjKeys.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemies.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjTravelatorPlatform.h"
#include "GamerCamp/GameSpecific/ExitDoor/GCObjExitDoor.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCWinScene.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCLossScene.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjTimePickUp.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjMovingPlatform.h"

#include "AppDelegate.h"


USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
// this just demos how simple it is to turn on/off logging on a define....
#define ENABLE_COLLISION_TEST_LOGGING

#if defined (ENABLE_COLLISION_TEST_LOGGING)

	#define COLLISIONTESTLOG( str )		CCLOG( str )

#else

	#define COLLISIONTESTLOG( str )		/*nothing*/

#endif


///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
CGCGameLayerPlatformer::CGCGameLayerPlatformer()
: IGCGameLayer					( GetGCTypeIDOf( CGCGameLayerPlatformer ) ) 
, m_pcGCGroupItem							( nullptr )
, m_pcGCGroupInvader						( nullptr )
, m_pcGCGroupProjectilePlayer				( nullptr )
, m_pcGCSprBackGround						( nullptr )
, m_pcGCOPlayer								( nullptr )
, m_pcGCTimer								( nullptr )
, m_pcGCOKeys								( nullptr )
, m_pcGCOKeys1								( nullptr )
, m_pcGCOKeys2								( nullptr )
, m_pcGCOTimePickUp							( nullptr )
, m_pcGCOExitDoor							( nullptr )
, m_pcGCBasicEnemies						( nullptr )
, m_pcGCMovingEnemies						( nullptr )
, m_pcGCTravelatorPlatform1					( nullptr )
, m_pcGCScalingBasicPlatformManager			( nullptr )
, m_pcGCScalingFallingPlatformManager		( nullptr )
, m_pcGCScalingBasicPlatformManager1		( nullptr )
, m_pcGCScalingBasicPlatformManager2		( nullptr )
, m_pcGCScalingBasicPlatformManagerMiddle	( nullptr )
, m_pcGCScalingBasicPlatformManagerTop		( nullptr )
, m_bResetWasRequested						( false   )

{
	m_iTotalKeys		= 3; // Mia: Sets the total amount of Keys the Player needs to obtain to be able to unlock the Exit Door and move on

	m_iKeysCollected	= 0; // Mia: Sets Default Keys to 0, so we can add 1 more on as Player collects them

	m_iTimerPickedUp	= 0; // Mia: Sets Default Timer Pick Up to 0

	m_bPlayerHitHostile = false; // sets the default value for if the player has hit a hostile to false

	m_bPlayerKeysGathered = false;
}



//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
CGCGameLayerPlatformer::~CGCGameLayerPlatformer()
{
}

void CGCGameLayerPlatformer::keyCollected() // Mia: This function adds one more Key onto how many the Player obtains
{
	m_iKeysCollected++; // Mia: Adds a Key
	CCLOG ( "Key Collected." ); // Mia: Checks to make sure Player has picked up Key only once
}

void CGCGameLayerPlatformer::addOnTime() // Mia: This function adds on Air Time
{
	// Mia: Replaces Current Air Time when Player picks up Timer PickUp by Getting Current Air Time and
	// Calling the Increase Value (of 20) that I created in Dan's 'GCObjTimer.cpp'
	m_pcGCTimer->setCurrentTime(m_pcGCTimer->getCurrentTime() + m_pcGCTimer->getTimerIncreaseValue());
	CCLOG ( "Time PickUp Collected." ); // Mia: Check to make sure Player has picked up Timer Pick Up only once
}

void CGCGameLayerPlatformer::replaceSceneWin()
{
	//If all the keys required are gathered this will become true and the scene will be replaced with the win screen/
	//in the future this will transition to the next level
	if(m_bPlayerKeysGathered == true)
	{
		m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio when Win Scene is used
		ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCWinScene >::CreateScene()));
	}
	
	
}

void CGCGameLayerPlatformer::replaceSceneLose()
{
	//When the player collides with a hostile this bool becomes true and will transition the the win screen
	if (m_bPlayerHitHostile == true)
	{
		m_pcGCBackgroundAudio->stopBackgroundMusic (); // Mia: Stops all Background Audio when Lose Scene is used
		ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCLossScene >::CreateScene()));
	}
	
}

void CGCGameLayerPlatformer::replaceSceneMenu()
{
	//Not in use yet will be used to go back to the main menu when required
	//m_pcGCBackgroundAudio->stopAll ();
	//ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCMainMenu >::CreateScene()));
	
}

// Mia: I had to change from using AudioEngine.h to SimpleAudioEngine.h for sounds as when we tried the Release Build, Audio would not work.
// Switching to SimpleAudioEngine.h fixed this issue, but wouldn't let me set the Volume, which I soon found out that setVolume isn't
// Supported in Windows. I ended up just changing Sound Volume through Audacity and reuploading.

void CGCGameLayerPlatformer::backgroundMusic() // Mia: Function that is called when we want the Background Music to play
{
	m_pcGCBackgroundAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCBackgroundAudio->playBackgroundMusic("Sounds/Background/BackgroundMusic.wav", true); // Mia: Play Audio by locating File, set to 'True' to loop
}

void CGCGameLayerPlatformer::playKeyAudio() // Mia: Function that is called when we want the Collected Key Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/Collectables/Key/CollectKey.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

void CGCGameLayerPlatformer::playTimerPickUpAudio() // Mia: Function that is called when we want the Timer PickUp Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/TimerPickUp.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

void CGCGameLayerPlatformer::playDoorOpeningAudio() // Mia: Function that is called when we want the Door Opened Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/OpeningDoor.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

//////////////////////////////////////////////////////////////////////////
// in order to guarantee the actions this layer expects we need to 
// initialise the keyboard action map every time onEnter is called - this
// fixes the case where an IGCGameLayer with a different mapping was
// pushed over this one on Director's scene stack
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::onEnter()
{
	IGCGameLayer::onEnter();

	//////////////////////////////////////////////////////////////////////////
	// init the actions
	// N.B. these 
	cocos2d::EventKeyboard::KeyCode aeKeyCodesForActions[] =
	{
		EventKeyboard::KeyCode::KEY_UP_ARROW,		// EPA_Up,
		EventKeyboard::KeyCode::KEY_DOWN_ARROW,		// EPA_Down,
		EventKeyboard::KeyCode::KEY_LEFT_ARROW,		// EPA_Left,		
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW,	// EPA_Right,
		EventKeyboard::KeyCode::KEY_SPACE,			// EPA_Fire	
	};

	u32 uSizeOfActionArray = ( sizeof(aeKeyCodesForActions) / sizeof(cocos2d::EventKeyboard::KeyCode) );

	// call base class function	to init the keyboard manager
	AppDelegate::InitialiseKeyboardManager( uSizeOfActionArray, aeKeyCodesForActions );
}

//////////////////////////////////////////////////////////////////////////
void CB_TestCollisionHandler( CGCObjPlayer& rcPlayer, CGCObjItem& rcItem, const b2Contact& rcContact )
{
	COLLISIONTESTLOG( "( standard function!) the player hit an item!" );
}

//////////////////////////////////////////////////////////////////////////
// on create
//////////////////////////////////////////////////////////////////////////
//virtual
void CGCGameLayerPlatformer::VOnCreate()
{

	/*static_cast<GLViewImpl*>(cocos2d::Director::getInstance()->getOpenGLView())->setFullscreen();

	Director::getInstance()->getOpenGLView()->setFrameSize(1920, 1080);

	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1920, 1080, ResolutionPolicy::EXACT_FIT);*/
	
	///////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	///////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	Size visibleSize	= Director::getInstance()->getVisibleSize();
	Point origin		= Director::getInstance()->getVisibleOrigin();


	///////////////////////////////////////////////////////////////////////////
	// default object group
	///////////////////////////////////////////////////////////////////////////

	// create the default object group
	IGCGameLayer::VOnCreate();


	///////////////////////////////////////////////////////////////////////////
	// custom object groups
	//
	// N.B. Cannot do this in CGCObjectGroup internally on construction, 
	// because ObjectGroupRegister calls a virtual function 
	// in the CGCObjectManager interface to check the 
	// types of objects that the group handles
	///////////////////////////////////////////////////////////////////////////

	// create and register the object group for the platform objects
	m_pcGCGroupPlatform = new CGCObjGroupPlatform();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupPlatform );

	// create and register the object group for the item objects
	m_pcGCGroupItem = new CGCObjGroupItem();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupItem );
	

	// create and register the object group for the player projectile objects
	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupProjectilePlayer );

	m_pcGCScalingBasicPlatformManager = new CGCObjScalingBasicPlatformManager ();
	m_pcGCScalingBasicPlatformManager->SetMaxPlatforms (18);
	m_pcGCScalingBasicPlatformManager->SetStartX (0);
	m_pcGCScalingBasicPlatformManager->SetStartY (60);
	CGCObjectManager::ObjectGroupRegister (m_pcGCScalingBasicPlatformManager);

	// Mia: Creating a new Object for 'm_pcGCScalingBasicPlatformManagerMiddle'
	m_pcGCScalingBasicPlatformManagerMiddle = new CGCObjScalingBasicPlatformManager();
	m_pcGCScalingBasicPlatformManagerMiddle->SetMaxPlatforms(16); // Mia: Setting the Max Platforms for the Middle Row to '16'
	m_pcGCScalingBasicPlatformManagerMiddle->SetStartX(0); // Mia: The X Position is set to '0'
	m_pcGCScalingBasicPlatformManagerMiddle->SetStartY(280); // Mia: The Y Position is set to '280'
	CGCObjectManager::ObjectGroupRegister(m_pcGCScalingBasicPlatformManagerMiddle); // Mia: Register the object group for the Middle Platforms

	// Mia: Creating a new Object for 'm_pcGCScalingBasicPlatformManagerTop'
	m_pcGCScalingBasicPlatformManagerTop = new CGCObjScalingBasicPlatformManager();
	m_pcGCScalingBasicPlatformManagerTop->SetMaxPlatforms(7); // Mia: Setting the Max Platforms for the Top Row to '7'
	m_pcGCScalingBasicPlatformManagerTop->SetStartX(400); // Mia: The X Position is set to '400'
	m_pcGCScalingBasicPlatformManagerTop->SetStartY(460); // Mia: The Y Position is set to '460'
	CGCObjectManager::ObjectGroupRegister(m_pcGCScalingBasicPlatformManagerTop); // Mia: Register the object group for the Top Platforms

	m_pcGCScalingBasicPlatformManager1 = new CGCObjScalingBasicPlatformManager ();
	m_pcGCScalingBasicPlatformManager1->SetMaxPlatforms (1);
	//m_pcGCScalingBasicPlatformManager1->SetSpacingX (100);
	m_pcGCScalingBasicPlatformManager1->SetStartX (20);
	m_pcGCScalingBasicPlatformManager1->SetStartY (340);
	CGCObjectManager::ObjectGroupRegister (m_pcGCScalingBasicPlatformManager1);

	m_pcGCScalingBasicPlatformManager2 = new CGCObjScalingBasicPlatformManager();
	m_pcGCScalingBasicPlatformManager2->SetMaxPlatforms (1);
	//m_pcGCScalingBasicPlatformManager1->SetSpacingX (100);
	m_pcGCScalingBasicPlatformManager2->SetStartX(110);
	m_pcGCScalingBasicPlatformManager2->SetStartY(420);
	CGCObjectManager::ObjectGroupRegister(m_pcGCScalingBasicPlatformManager2);

	m_pcGCScalingFallingPlatformManager = new CGCObjScalingFallingPlatformManager ();
	m_pcGCScalingFallingPlatformManager->SetMaxPlatforms (3);
	m_pcGCScalingFallingPlatformManager->SetStartY (460);
	m_pcGCScalingFallingPlatformManager->SetStartX (200);
	CGCObjectManager::ObjectGroupRegister (m_pcGCScalingFallingPlatformManager);

	


    ///////////////////////////////////////////////////////////////////////////
    // add menu
	///////////////////////////////////////////////////////////////////////////

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage* pResetItem 
		= MenuItemImage::create(	"Loose/CloseNormal.png",
									"Loose/CloseSelected.png",
									CC_CALLBACK_1( CGCGameLayerPlatformer::Callback_OnResetButton, this));
    
	pResetItem->setPosition( Vec2(	( ( visibleSize.width - ( pResetItem->getContentSize().width * 0.5f ) ) + origin.x ),
									( ( ( pResetItem->getContentSize().height * 0.5f ) + origin.y ) ) ) );
 
    MenuItemImage* pQuitItem 
		= MenuItemImage::create(	"Loose/CloseNormal.png",
									"Loose/CloseSelected.png",
									CC_CALLBACK_1( CGCGameLayerPlatformer::Callback_OnQuitButton, this ));
    
	pQuitItem->setPosition( Vec2(	( ( visibleSize.width - ( pQuitItem->getContentSize().width * 0.5f ) ) + origin.x ),
									( ( visibleSize.height - ( pQuitItem->getContentSize().height * 0.5f ) ) + origin.y ) ) );

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create( pResetItem, pQuitItem, nullptr );
    pMenu->setPosition( Vec2::ZERO );
    this->addChild( pMenu, 1 );

	//////////////////////////////////////////////////////////////////////////////////////////

	//Not in use yet 
	/*switch(mState)
	{
	case ECGameStates::EState_Menu:
			{


			break;
			}
	case ECGameStates::EState_Playing:
			{
				

			break;
			}
	case ECGameStates::EState_GameLost:
			{


			break;
			}
	case ECGameStates::EState_GameWon:
			{


			break;
			}
	}*/

    ///////////////////////////////////////////////////////////////////////////
    // add label
	///////////////////////////////////////////////////////////////////////////

 	// Mia: Create and initialize the Label with instructions, then set the Font and then the Size
    Label* pLabel = Label::createWithTTF( "Collect the three Keys to open the Door before the Air Timer runs out!", "fonts/SaltyOcean.ttf", 35);

    // Mia: Position the label on the center of the screen
    pLabel->setPosition( Vec2( visibleSize.width/2, visibleSize.height - 50 ) );

    // Mia: Add the label as a child to this Game Layer
    this->addChild(pLabel, 1);

	//"TexturePacker/Backgrounds/Placeholder/background.plist"
    //
    // add "CGCGameLayerPlatformer" splash screen"

	//Old code
	/*const char* pszPlist_TimerBar = "TexturePacker/Sprites/TimerBar/WhiteSquare.plist";
	{
		m_pcGCsprTimerBar = new CGCObjSprite();
		
		m_pcGCsprTimerBar->CreateSprite(pszPlist_TimerBar);
		m_pcGCsprTimerBar->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2) );
		m_pcGCsprTimerBar->SetParent(IGCGameLayer::ActiveInstance());
		m_pcGCsprTimerBar->SetScale(0.1f, 0.1f);
	}*/
	
	// Mia: Setting up the Background Sprite
	const char* pszPlist_background = "TexturePacker/Sprites/Background/Background.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite(); // Mia: Create a new Object for Background
		m_pcGCSprBackGround->CreateSprite( pszPlist_background ); // Mia: Create the Sprite for Background by calling it
		m_pcGCSprBackGround->SetResetPosition(cocos2d::Vec2(500, 400)); // Mia: Setting the X and Y Positions
		m_pcGCSprBackGround->SetParent( IGCGameLayer::ActiveInstance() ); // Mia: Adding Sprite to this Game Layer
		backgroundMusic(); // Mia: Calling 'backgroundMusic' Function, so the Audio plays as soon as level loads
 	}

	//Timer
	m_pcGCTimer = new CGCObjTimer();

	//Lives
	m_pcGCOPlayer = new CGCObjPlayer();

	//Timer Layer
	this->addChild(m_pcGCTimer->getTimerText(), 10);

	//Lives Layer
	this->addChild(m_pcGCOPlayer->getLivesText(), 10);
	
	///////////////////////////////////////////////////////////////////////////
	// set up physics 
	///////////////////////////////////////////////////////////////////////////

	// set "self" as contact listener
	B2dGetWorld()->SetContactListener( this ); 

	// load the physics shapes from the plist created with PhysicsEditor
	B2dLoadShapesFromPlist( "PhysicsEditor/GameShapes.plist" );	


	///////////////////////////////////////////////////////////////////////////
	// add screen bounds - note these are now derived from CGCObjSpritePhysics
	// this is to allow callback based collision handling with them etc.
	///////////////////////////////////////////////////////////////////////////
	Vec2	v2ScreenCentre_Pixels( ( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ) );
	Vec2	v2ScreenCentre_B2d = B2dPixelsToWorld( v2ScreenCentre_Pixels );

	f32 fScreenWidthB2d			= B2dPixelsToWorld( visibleSize.width );
	f32 fHalfScreenWidthB2d		= ( fScreenWidthB2d / 2.0f );

	f32 fScreenHeightB2d		= B2dPixelsToWorld( visibleSize.height );
	f32 fHalfScreenHeightB2d	= ( fScreenHeightB2d / 2.0f);

	new CGCObjScreenBound( CGCObjScreenBound::EScreenBoundType::Bottom, ( v2ScreenCentre_B2d + Vec2( 0.0f, -fHalfScreenHeightB2d ) ), fScreenWidthB2d, 0.5f, 0.0f );
	new CGCObjScreenBound( CGCObjScreenBound::EScreenBoundType::Top,	( v2ScreenCentre_B2d + Vec2( 0.0f, fHalfScreenHeightB2d ) ), fScreenWidthB2d, 0.5f, 0.0f );
	new CGCObjScreenBound( CGCObjScreenBound::EScreenBoundType::Left,	( v2ScreenCentre_B2d + Vec2( -fHalfScreenWidthB2d, 0.0f ) ), 0.5f, fScreenHeightB2d, 0.0f );
	new CGCObjScreenBound( CGCObjScreenBound::EScreenBoundType::Right,	( v2ScreenCentre_B2d + Vec2( fHalfScreenWidthB2d, 0.0f ) ), 0.5f, fScreenHeightB2d, 0.0f );


	///////////////////////////////////////////////////////////////////////////
	// add player
	///////////////////////////////////////////////////////////////////////////

	// starting position
	Vec2 v2MarioStartPos = ( v2ScreenCentre_Pixels - Vec2( 0.0f, ( visibleSize.height * 0.45f ) ) );

	// create player object
	m_pcGCOPlayer = new CGCObjPlayer();
	m_pcGCOPlayer->SetResetPosition( cocos2d::Vec2(150, 100) );

	m_pcGCOKeys				= new CGCObjKeys (); // Mia: Create Keys Object
	m_pcGCOKeys->SetResetPosition			( cocos2d::Vec2 (715, 160) ); // Mia: Setting the X and Y Positions

	m_pcGCOKeys1			= new CGCObjKeys (); // Mia: Create other Keys Object
	m_pcGCOKeys1->SetResetPosition			( cocos2d::Vec2(500, 380) ); // Mia: Setting the X and Y Positions

	m_pcGCOKeys2			= new CGCObjKeys (); // Mia: Create last Keys Object
	m_pcGCOKeys2->SetResetPosition			( cocos2d::Vec2(700, 550) ); // Mia: Setting the X and Y Positions

	m_pcGCOTimePickUp		= new CGCObjTimePickUp (); // Mia: Create Time PickUp Object
	m_pcGCOTimePickUp->SetResetPosition		( cocos2d::Vec2(880, 500) ); // Mia: Setting the X and Y Positions
	
	m_pcGCOExitDoor			= new CGCObjExitDoor (); // Mia: Create Exit Door Object
	m_pcGCOExitDoor->SetResetPosition		( cocos2d::Vec2(60, 120) ); // Mia: Setting the X and Y Positions


	m_pcGCOMovingPlatform	= new CGCObjMovingPlatform (); // Mia: Create Moving Platform Object
	m_pcGCOMovingPlatform->SetResetPosition ( cocos2d::Vec2 (970, 280) );  // Mia: Setting the X and Y Positions
	m_pcGCOMovingPlatform->setGravity		( 3.0f ); // Mia: Setting the Gravity

	m_pcGCTravelatorPlatform1 = new CGCObjTravelatorPlatform();
	m_pcGCTravelatorPlatform1->SetStartPos(cocos2d::Vec2(920, 450));
	//m_pcGCPlatformTest1->SetResetPosition (v2MarioStartPos);
	
	//enemy
	Vec2 v2Enemy1StartPos = ( cocos2d::Vec2(720,100) );
	m_pcGCBasicEnemies = new CGCBasicEnemies ();
	m_pcGCBasicEnemies->SetResetPosition (v2Enemy1StartPos);
	m_pcGCBasicEnemies->setGravity(1.0);

	m_pcGCMovingEnemies = new CGCMovingEnemies ();
	m_pcGCMovingEnemies->SetResetPosition (cocos2d::Vec2(500,333));
	m_pcGCMovingEnemies->setGravity (10.0f);
	
	//
	///////////////////////////////////////////////////////////////////////////
	// N.B. invaders are created by m_pcGCGroupInvader in OnResourceAcquire
	///////////////////////////////////////////////////////////////////////////
	//m_pcGCGroupInvader->SetFormationOrigin( v2ScreenCentre_Pixels + Vec2( -( visibleSize.width * 0.3f ), ( visibleSize.height * 0.25f ) ) );
	//m_pcGCGroupInvader->SetRowsAndColumns( 6, 8, -60.0f, 40.0f );


	//////////////////////////////////////////////////////////////////////////
	//
	// you can also pass regular (static) function:
	// GetCollisionManager().AddCollisionHandler( CB_TestCollisionHandler );
	// 
	// NOTE: in general rather than executing game logic in handler we should cache data we need to respond to this and do it in the next update
	// e.g. if we wanted to award score, make the player lose a life, or similar we should set a state flag and respond in update

	// Mia: Handles the Collision between the Player and the Moving Platform
	GetCollisionManager().AddCollisionHandler
	(

		[]
	(CGCObjPlayer& rcPlayer, CGCObjMovingPlatform& rcMovingPlatform, const b2Contact& rcContact) -> void
	{
		if( rcContact.IsTouching() )
		{
			rcPlayer.SetCanJump(true); // // Mia: If is touching Platform, the Player can jump
		}

		else if( rcContact.IsTouching() == false )
		{
			rcPlayer.SetCanJump(false); // Mia: If not touching, the Player cannot jump
		}
	}
	);

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision checks if the player is touching a platform or not, if it is touching it gives the player the ability to jump
		// if it not touching then the player cannot jump
		[]
	(CGCObjPlayer& rcPlayer, CGCObjScalingBasicPlatform& rcPlatform, const b2Contact& rcContact) -> void
		{
			if (rcContact.IsTouching ()) //checks if it is touching
			{
				rcPlayer.SetCanJump (true);  //sets the bool can jump to true if it touching
			}

			else if (rcContact.IsTouching () == false)
			{
				rcPlayer.SetCanJump (false); // sets the bool to false if it is not touching
			}

		}
	);

	GetCollisionManager().AddCollisionHandler
	(
		[]
		(CGCObjPlayer& rcPlayer, CGCObjTravelatorPlatform& rcTravelatorPlatform, const b2Contact& rcContact) -> void
		{
			if (rcContact.IsTouching())
			{
				
				rcPlayer.setOnTravelator(true);

				rcPlayer.SetCanJump(true);// Setting jump to true so the player can jump when on the travelator(i.e. ground check)
				
				rcPlayer.SetVelocity(rcTravelatorPlatform.getVelocity());
				// When contact with the player is made the players velocity will be increased or decreased depending on if the value is + / -
				
			}
			else if(rcContact.IsTouching() == false )
			{
				rcPlayer.setOnTravelator(false);//Sets the players velocity back to normal when the player is no longer touching the platfrom

				rcPlayer.SetCanJump(false);// making sure that the player cant jump while in the air when they are falling off the platform
			}
		}
	);
	
	// Mia: Handles the Collision between the Player and the Exit Door
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjExitDoor& rcExitDoor, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		if( m_iKeysCollected >= m_iTotalKeys ) // Mia: If the Keys Collected by Player is more than or equal than to the Total Keys Collected
		{
			m_bPlayerKeysGathered = true;

			playDoorOpeningAudio(); // Mia: Calls the Function which plays the Door Opening Audio
		}
	}
	);

	// Mia: Handles the Collision between the Player and the Keys
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjKeys& rcKeys, CGCObjPlayer &rcPlayer, const b2Contact& rcContact) -> void
	{
		if( rcKeys.getJustCollided() == false )
		{
			rcKeys.setJustCollided ( true ); // Mia: When player has collided with a Key
			CGCObjectManager::ObjectKill ( &rcKeys ); // Mia: Destroy the Key Object Sprite
			keyCollected(); // Mia: Calls Function which adds on one Key to how many Player has obtained
			playKeyAudio(); // Mia: Then calls Function which plays Key Collected Audio
		}
	}
	);

	// Mia: Handles the Collision between the Player and the Time PickUp
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjTimePickUp& rcPickUp, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		if( rcPickUp.getJustCollided() == false )
		{
			if( m_pcGCTimer->getCurrentTime() >= 0 ) // Mia: If Current Time is greater or equal to zero
			{
				rcPickUp.setJustCollided ( true ); // Mia: When player has collided with a Timer PickUp
				CGCObjectManager::ObjectKill(&rcPickUp); // Mia: Destroy the Timer PickUp Object Sprite
				addOnTime(); // Mia: Calls the Function which adds on Timer Increase Value (20) to whatever is the current Air Time
				playTimerPickUpAudio(); // Mia: Calls the Function which plays Timer PickUp Audio
			}
		}
	}
		);

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
		//it will reset the level from the start
		[this]
	(CGCBasicEnemies& rcEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			//m_pcGCTimer->ResetTimer ();
			//CGCObjectManager::ObjectKill (&rcEnemies);
			CCLOG ("Player Died.");
			m_bPlayerHitHostile = true;
			rcPlayer.DecrementLives();
		}
	);

	

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
		//it will reset the level from the start
		[this]
	(CGCMovingEnemies& rcMEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			if (rcMEnemies.getJustCollided() == false)
			{
				rcMEnemies.setJustCollided (true);
				//RequestReset ();
				//m_pcGCTimer->ResetTimer ();
				CCLOG ("Player wacked.");
				//CGCObjectManager::ObjectKill (&rcPlayer);
				m_bPlayerHitHostile = true;
				rcPlayer.DecrementLives();
			}
		}
	);

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision checks if the player is touching the falling platforms or not
		//If the player is touching the falling platforms it will then set a bool to true
		//when this happens the platform has some code to make its self move down and then after
		//x amount of time delete itself
		//It also can decide if the player is allowed to jump or not
		[this]
	(CGCObjScalingFallingPlatform& rcFallingPlatforms, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void

		{
			if (rcContact.IsTouching ())
			{
				if (rcFallingPlatforms.GetContactWithPlayer () == false)	
				{
					rcFallingPlatforms.SetContactWithPlayer (true);	//Starts moving when the player is on the platform		
				}
			}

			else if (rcContact.IsTouching () == false)				//stops moving when the player is off it
			{
				rcFallingPlatforms.SetContactWithPlayer (false);
			}

			if (rcFallingPlatforms.GetCanDelete () == true)
			{
				CGCObjectManager::ObjectKill (&rcFallingPlatforms); //checks if the platform can be delted, if it can then it will delete itself
			}

			if (rcContact.IsTouching ())							//checks if it is touching
			{
				rcPlayer.SetCanJump (true);							//sets the bool can jump to true if it touching);
			}

			else if (rcContact.IsTouching () == false)
			{
				rcPlayer.SetCanJump (false);						//Sets it to false if it is not touching 
			}
		}
	);
}




//////////////////////////////////////////////////////////////////////////
// on update
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );
	
	// this shows how to iterate and respond to the box2d collision info
	ManuallyHandleCollisions();	
	
	m_pcGCTimer->Update();

	if( ResetWasRequested() )
	{
		VOnReset();
		m_iKeysCollected = 0; // Mia: Resets Keys Collected
		ResetRequestWasHandled();
		m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio on Reset
		backgroundMusic (); // Mia: Calls this Function, so it doesn't overlay
	}

	//This is a check for the timer, When the timer reaches 0 the timer is reset and the current level is also reset
	if(m_pcGCTimer->getCurrentTime() <= 0)
	{
		m_pcGCTimer->setCurrentTime(m_pcGCTimer->getTotalTimerDuration());
		
		RequestReset();
	}

	////////////////////////////////
	//Move to Lives function when made 
	replaceSceneWin();

	replaceSceneLose();

	//onDeath(); (This Will Replace The Replace Scene Lose Function)
	//These will be called when the scene needs to be replaced
	////////////////////////////////
}


///////////////////////////////////////////////////////////////////////////////
// on destroy
///////////////////////////////////////////////////////////////////////////////
// virtual
void CGCGameLayerPlatformer::VOnDestroy()
{
	///////////////////////////////////////////////////////////////////////////
	// clean up anything we allocated in opposite order to creation
	///////////////////////////////////////////////////////////////////////////	
	delete m_pcGCOPlayer;
	m_pcGCOPlayer = nullptr;

	delete m_pcGCBasicEnemies;
	m_pcGCBasicEnemies = nullptr;

	delete m_pcGCMovingEnemies;
	m_pcGCMovingEnemies = nullptr;

	delete m_pcGCSprBackGround;
	m_pcGCSprBackGround = nullptr;

	delete m_pcGCTimer;
	m_pcGCTimer = nullptr;
	
	delete m_pcGCOExitDoor;
	m_pcGCOExitDoor = nullptr;

	delete m_pcGCOTimePickUp;
	m_pcGCOTimePickUp = nullptr;

	delete m_pcGCOMovingPlatform;
	m_pcGCOMovingPlatform = nullptr;

	delete m_pcGCOKeys;
	m_pcGCOKeys = nullptr;

	delete m_pcGCOKeys1;
	m_pcGCOKeys1 = nullptr;

	delete m_pcGCOKeys2;
	m_pcGCOKeys2 = nullptr;

	delete m_pcGCTravelatorPlatform1;
	m_pcGCTravelatorPlatform1 = nullptr;

	///////////////////////////////////////////////////////////////////////////
	// N.B. because object groups must register manually, 
	// we also unregister them manually
	///////////////////////////////////////////////////////////////////////////
	//CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupPlatform );
	//delete m_pcGCGroupPlatform;
	//m_pcGCGroupPlatform = nullptr;

	//CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupProjectilePlayer );
	//delete m_pcGCGroupProjectilePlayer;
	//m_pcGCGroupProjectilePlayer = nullptr;

	//CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupInvader );
	//delete m_pcGCGroupInvader;
	//m_pcGCGroupInvader = nullptr;

	//CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupItem );
	//delete m_pcGCGroupItem;
	//m_pcGCGroupItem = nullptr;

	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingBasicPlatformManager);
	delete m_pcGCScalingBasicPlatformManager;
	m_pcGCScalingBasicPlatformManager = nullptr;

	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingFallingPlatformManager);
	delete m_pcGCScalingFallingPlatformManager;
	m_pcGCScalingFallingPlatformManager = nullptr;

	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingBasicPlatformManagerMiddle);
	delete m_pcGCScalingBasicPlatformManagerMiddle;
	m_pcGCScalingBasicPlatformManagerMiddle = nullptr;

	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingBasicPlatformManagerTop);
	delete m_pcGCScalingBasicPlatformManagerTop;
	m_pcGCScalingBasicPlatformManagerTop = nullptr;

	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingBasicPlatformManager1);
	delete m_pcGCScalingBasicPlatformManager1;
	m_pcGCScalingBasicPlatformManager1 = nullptr;


	CGCObjectManager::ObjectGroupUnRegister (m_pcGCScalingBasicPlatformManager2);
	delete m_pcGCScalingBasicPlatformManager2;
	m_pcGCScalingBasicPlatformManager2 = nullptr;



	IGCGameLayer::VOnDestroy();
}

///////////////////////////////////////////////////////////////////////////////
// on death (REPLACEMENT FOR LATER)
///////////////////////////////////////////////////////////////////////////////
//void CGCGameLayerPlatformer::onDeath()
//{
	//if (m_pcGCOPlayer->GetNumberOfLives() <= 0)
	//{
	//	m_pcGCBackgroundAudio->stopAll(); // Stops all Background Audio when Lose Scene is used
		//ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCLossScene >::CreateScene()));
		//m_pcGCOPlayer->ResetLives();
	//}
//}

///////////////////////////////////////////////////////////////////////////////
// on quit button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnQuitButton( Ref* pSender )
{
	m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio when Quit Button is used
	ReplaceScene (TransitionRotoZoom::create (1.0f, TGCGameLayerSceneCreator< CGCMainMenu >::CreateScene ()));
}



///////////////////////////////////////////////////////////////////////////////
// on reset button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnResetButton(Ref* pSender)
{
	ReplaceScene (TransitionRotoZoom::create (1.0f, TGCGameLayerSceneCreator< CGCLossScene >::CreateScene ()));
	m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio when Reset Button is used
	//m_pcGCTimer->ResetTimer();
	//RequestReset();
}


///////////////////////////////////////////////////////////////////////////////
// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::BeginContact( b2Contact* pB2Contact )
{
}


///////////////////////////////////////////////////////////////////////////////
// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::EndContact( b2Contact* pB2Contact )
{
}


///////////////////////////////////////////////////////////////////////////////
// pre solve
// insert any logic that needs to be done before a contact is resolved
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::PreSolve( b2Contact* pB2Contact, const b2Manifold* pOldManifold ) 
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA();
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB();

	const b2Body* pBodyA = pFixtureA->GetBody();
	const b2Body* pBodyB = pFixtureB->GetBody();

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*) pBodyA->GetUserData();
	// if( this is not a GC object )
	if( pGcSprPhysA == nullptr )
	{
		return;
	}

	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*) pBodyB->GetUserData();
	// if( this is not a GC object )
	if( pGcSprPhysB == nullptr )
	{
		return;
	}

	// ignore contact between player projectile and item for collision resolution purposes
	if(	pGcSprPhysA->GetGCTypeID() != pGcSprPhysB->GetGCTypeID() )
	{
		if(		(	( pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf( CGCObjProjectilePlayer ) )
				 &&	( pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf( CGCObjItem ) ) )
			||	(	( pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf( CGCObjItem ) )
				 &&	( pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf( CGCObjProjectilePlayer ) ) ) )
		{
			// ignore the collision!
			pB2Contact->SetEnabled( false );
			
			//
			// insert logic relating to this collision here
			//
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// post solve
// insert any logic that needs to be done after a contact is resolved
// e.g. check the types and double the impulse
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::PostSolve( b2Contact* pB2Contact, const b2ContactImpulse* pImpulse )
{
}


///////////////////////////////////////////////////////////////////////////////
// this function can only look at the collisions that happened (and which 
// have potentially been resolved) in the previous physics step
// 
// N.B. it is totally possible to get a callback after collisions have been 
// detected, but before they're resolved so you can choose to ignore them - 
// e.g. for gamplay reasons like jumping up through a platform
// 
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::ManuallyHandleCollisions()
{
	for(	const b2Contact* pB2Contact	= IGCGameLayer::ActiveInstance()->B2dGetWorld()->GetContactList();
			nullptr						!= pB2Contact;
			pB2Contact					= pB2Contact->GetNext() )
	{
		const b2Fixture* pFixtureA = CGCObjSpritePhysics::FromB2DContactGetFixture_A( pB2Contact );
		const b2Fixture* pFixtureB = CGCObjSpritePhysics::FromB2DContactGetFixture_B( pB2Contact );

		// return if either physics body has null user data
		CGCObjSpritePhysics* pGcSprPhysA = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics( pFixtureA );
		if( !pGcSprPhysA )
		{
			return;
		}

		CGCObjSpritePhysics* pGcSprPhysB = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics( pFixtureB );
		if( !pGcSprPhysB )
		{
			return;
		}

		// check for user data - this is defined in physics editor as the 'Id' text
		// in the text box immediately below the 'Is Sensor?' checkbox
		// 
		// Mario has a fixture that is a sensor with id 'bottom_left' 
		// and this is what we're checking for - put a breakpoint on 
		const std::string*	pstrCheckMe		= cocos2d::GB2ShapeCache::getFixtureIdText( pFixtureA );
		bool				bNameMatches	= ( 0 == pstrCheckMe->compare( "bottom_left" ) );
		bool				bIsASensor		= pFixtureA->IsSensor();

		if(	pstrCheckMe && bNameMatches && bIsASensor )
		{
			// put a breakpoint on the next line to see the sensor detection
			int i = 0;
			++i;			
		}

		pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText( pFixtureB );
		if( 	pstrCheckMe 
			&&	( 0 == pstrCheckMe->compare( "bottom_left" ) ) 
			&&	pFixtureB->IsSensor() )
		{
			int i = 0;
			++i;
		}
	}
}

