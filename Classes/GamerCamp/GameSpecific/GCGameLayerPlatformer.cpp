///////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
///////////////////////////////////////////////////////////////////////////////

#include "GCGameLayerPlatformer.h"
#include <algorithm>
#include <stdlib.h> 
#include <fstream>
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "MenuScene.h"
#include "GamerCamp/GameSpecific/Levels/GCLevel2.h"
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
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

#include "GamerCamp/GameSpecific/Timer/GCObjTimer.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjKeys.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemy2.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDown.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDownSlow.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDownFast.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyLRSlow.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyLRFast.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjTravelatorPlatform.h"
#include "GamerCamp/GameSpecific/ExitDoor/GCObjExitDoor.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCWinScene.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCLossScene.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjTimePickUp.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjMovingPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBrickPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform1.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform2.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform3.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform4.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform5.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform6.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform7.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasePlatform.h"
#include "GamerCamp/GameSpecific/Ladder/GCObjLadder.h"
#include "GamerCamp/GameSpecific/Enemies/GCHazardChild.h"
#include "GamerCamp/GameSpecific/Enemies/GCEnemyMovementCollider.h"
#include "GamerCamp/GameSpecific/Enemies/GCEnemyMovementCollider2.h"
#include "GamerCamp/GameSpecific/Score/GCObjScore.h"
#include "GamerCamp/GameSpecific/Score/GCObjHighScore.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCSwitch.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjSwitchPlatform1.h"
#include "GamerCamp/GameSpecific/NewPlatforms/CGCObjSwitchPlatform2.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane.h"


#include "AppDelegate.h"


USING_NS_CC;


///////////////////////////////////////////////////////////////////////////
// this just demos how simple it is to turn on/off logging on a define....
//#define ENABLE_COLLISION_TEST_LOGGING
//
//#if defined (ENABLE_COLLISION_TEST_LOGGING)
//
//	#define COLLISIONTESTLOG( str )		CCLOG( str )
//
//#else
//
//	#define COLLISIONTESTLOG( str )		/*nothing*/
//
//#endif
//

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
CGCGameLayerPlatformer::CGCGameLayerPlatformer()
	: IGCGameLayer(GetGCTypeIDOf(CGCGameLayerPlatformer))
	, m_pcGCGroupItem(nullptr)
	, m_pcGCGroupInvader(nullptr)
	, m_pcGCGroupProjectilePlayer(nullptr)
	, m_pcGCTimer(nullptr)
	, m_pcGCSprBackGround(nullptr)
	, m_pcGCOPlayer(nullptr)
	, m_bResetWasRequested(false)
	, m_bSkipWasRequested(false)
, m_bQuitWasRequested			( false )
, m_pcGCOKeys					( nullptr )
, m_pcGCOKeys1					( nullptr )
, m_pcGCOKeys2					( nullptr )
, m_bCheckIfPlayerIsAbovePlatform (false)
, m_pcGCOScore (nullptr)
, m_pcGCOHighScore(nullptr)

{
	m_iTotalKeys = 5; // Mia: Sets the total amount of Keys the Player needs to obtain to be able to unlock the Exit Door and move on

	m_iKeysCollected = 0; // Mia: Sets Default Keys to 0, so we can add 1 more on as Player collects them

	//m_iTimerPickedUp = 0; // Mia: Sets Default Timer Pick Up to 0
	
	
	
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
	m_pcGCOScore->IncreaseScore();
	CCLOG("Key Collected."); // Mia: Checks to make sure Player has picked up Key only once
}

void CGCGameLayerPlatformer::addOnTime()
{
	// Mia: Replaces Current Air Time when Player picks up Timer PickUp by Getting Current Air Time and
	// Calling the Increase Value (of 20) that I created in Dan's 'GCObjTimer.cpp'
	m_pcGCTimer->setCurrentTime(m_pcGCTimer->getCurrentTime() + m_pcGCTimer->getTimerIncreaseValue());
	CCLOG("Time PickUp Collected."); // Mia: Check to make sure Player has picked up Timer Pick Up only once

}

void CGCGameLayerPlatformer::playBackgroundMusic() // Mia: Function that is called when we want the Background Music to play
{
	m_pcGCBackgroundAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCBackgroundAudio->playBackgroundMusic("Sounds/BackgroundMusic/CrystalCoralReefSvR.wav", true); // Mia: Play Audio by locating File, set to 'True' to loop
}

void CGCGameLayerPlatformer::playKeyAudio() // Mia: Function that is called when we want the Collected Key Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/Collectables/Key/item_pickup.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

//void CGCGameLayerPlatformer::playTimerPickUpAudio() // Mia: Function that is called when we want the Timer PickUp Sound Effect to play
//{
//	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
//	m_pcGCSoundEffectsAudio->playEffect("Sounds/Collectables/Timer/TimerPickUp.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
//}

void CGCGameLayerPlatformer::playDoorOpeningAudio() // Mia: Function that is called when we want the Door Opened Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/Door/OpeningDoor.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
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
	//COLLISIONTESTLOG( "( standard function!) the player hit an item!" );
}

//////////////////////////////////////////////////////////////////////////
// on create
//////////////////////////////////////////////////////////////////////////
//virtual
void CGCGameLayerPlatformer::VOnCreate ()
{
	///////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	///////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	Size visibleSize = Director::getInstance ()->getVisibleSize ();
	Point origin = Director::getInstance ()->getVisibleOrigin ();

	

	///////////////////////////////////////////////////////////////////////////
	// default object group
	///////////////////////////////////////////////////////////////////////////

	// create the default object group
	IGCGameLayer::VOnCreate ();

	
	///////////////////////////////////////////////////////////////////////////
	// custom object groups
	//
	// N.B. Cannot do this in CGCObjectGroup internally on construction, 
	// because ObjectGroupRegister calls a virtual function 
	// in the CGCObjectManager interface to check the 
	// types of objects that the group handles
	///////////////////////////////////////////////////////////////////////////

	// create and register the object group for the platform objects
	m_pcGCGroupPlatform = new CGCObjGroupPlatform ();
	CGCObjectManager::ObjectGroupRegister (m_pcGCGroupPlatform);

	// create and register the object group for the item objects
	m_pcGCGroupItem = new CGCObjGroupItem ();
	CGCObjectManager::ObjectGroupRegister (m_pcGCGroupItem);

	// create and register the object group for the invader objects
	m_pcGCGroupInvader = new CGCObjGroupInvader ();
	CGCObjectManager::ObjectGroupRegister (m_pcGCGroupInvader);

	// create and register the object group for the player projectile objects
	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer ();
	CGCObjectManager::ObjectGroupRegister (m_pcGCGroupProjectilePlayer);


	///////////////////////////////////////////////////////////////////////////
	// add menu
	///////////////////////////////////////////////////////////////////////////

	// add a "close" icon to exit the progress. it's an autorelease object
	MenuItemImage* pResetItem
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnResetButton, this));

	pResetItem->setPosition (Vec2 (( ( visibleSize.width - ( pResetItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( ( pResetItem->getContentSize ().height * 0.5f ) + origin.y ) )));

	MenuItemImage* pSkipItem
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnSkipButton, this));

	pSkipItem->setPosition (Vec2 (( ( visibleSize.width - ( pSkipItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( ( pSkipItem->getContentSize ().height * 6.0f ) + origin.y ) )));

	MenuItemImage* pQuitItem
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnQuitButton, this));

	pQuitItem->setPosition (Vec2 (( ( visibleSize.width - ( pQuitItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( visibleSize.height - ( pQuitItem->getContentSize ().height * 0.5f ) ) + origin.y )));

	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create (pResetItem, pSkipItem, pQuitItem, nullptr);
	pMenu->setPosition (Vec2::ZERO);
	this->addChild (pMenu, 1);


	///////////////////////////////////////////////////////////////////////////
	// add label
	///////////////////////////////////////////////////////////////////////////

	//// Mia: Create and initialize the Label with instructions, then set the Font and then the Size
	//Label* pLabel = Label::createWithTTF("Collect the five Keys to open the Door before the Air Timer runs out!", "fonts/SaltyOcean.ttf", 30);

	//// Mia: Position the label to the top centre of the screen
	//pLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 175));

	//// Mia: Add the label as a child to this Game Layer
	//this->addChild(pLabel, 1);

	
	m_pcGCOScore = new CGCObjScore ();

	this->addChild (m_pcGCOScore->getScoreText (), 10);

	m_pcGCOScore->ScoreClearFile(m_pcGCOScore);
	
	m_pcGCOHighScore = new CGCObjHighScore(m_pcGCOScore);

	m_pcGCOHighScore->HighScoreReadFile(m_pcGCOScore);
	
	this->addChild(m_pcGCOHighScore->getHighScoreText(), 10);


	
	//HighScore();
	//Mia: Added Background
	//const char* pszPlist_background = "TexturePacker/Sprites/Background/cc_background.plist";
	//{
	//	m_pcGCSprBackGround = new CGCObjSprite ();
	//	m_pcGCSprBackGround->CreateSprite (pszPlist_background);
	//	m_pcGCSprBackGround->SetScale (1, 1);
	//	m_pcGCSprBackGround->SetResetPosition (Vec2 (visibleSize.width / 2, visibleSize.height / 2));
	//	m_pcGCSprBackGround->SetParent (IGCGameLayer::ActiveInstance ());
		playBackgroundMusic (); // Mia: Calling 'playBackgroundMusic' Function, so the Audio plays as soon as level loads
	//}

	m_pcGCTimer = new CGCObjTimer ();

	//this->addChild(m_pcGCTimer->getTimerText(), 10);
	this->addChild (m_pcGCTimer->getTimerBar (), 50);
	this->addChild (m_pcGCTimer->getTimerBarUI (), 51);

	///////////////////////////////////////////////////////////////////////////
	// set up physics 
	///////////////////////////////////////////////////////////////////////////

	// set "self" as contact listener
	B2dGetWorld ()->SetContactListener (this);

	// load the physics shapes from the plist created with PhysicsEditor
	B2dLoadShapesFromPlist ("PhysicsEditor/GameShapes.plist");

	///////////////////////////////////////////////////////////////////////////
	// stop mario from leaving the screen
	///////////////////////////////////////////////////////////////////////////

	// get window size
	//Size s = Director::getInstance()->getWinSize();

	// PTM_RATIO
	f32 PTM_RATIO = IGCGAMELAYER_B2D_PIXELS_PER_METER;

	b2Vec2	b2v2ScreenCentre_Pixels (( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ));
	Vec2	v2ScreenCentre_Pixels (( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ));



	// define the ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position = IGCGameLayer::B2dPixelsToWorld (b2v2ScreenCentre_Pixels);
	groundBodyDef.type = b2_kinematicBody;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = B2dGetWorld ()->CreateBody (&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// bottom
	groundBox.SetAsBox (( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.5f, b2Vec2 (0.0f, -( ( visibleSize.height * 0.5f ) / PTM_RATIO )), 0.0f);
	groundBody->CreateFixture (&groundBox, 0);

	// top
	groundBox.SetAsBox (( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.5f, b2Vec2 (0.0f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO )), 0.0f);
	groundBody->CreateFixture (&groundBox, 0);

	// left
	groundBox.SetAsBox (0.5f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO ), b2Vec2 (-( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.0f), 0.0f);
	groundBody->CreateFixture (&groundBox, 0);

	// right
	groundBox.SetAsBox (0.5f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO ), b2Vec2 (( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.0f), 0.0f);
	groundBody->CreateFixture (&groundBox, 0);


	///////////////////////////////////////////////////////////////////////////
	// N.B. this is where you would load a level file, using the factory to
	// create the class instances specified by the level file by passing their
	// class names and init data
	//
	// In order to ensure stuff is correctly cleaned up you will need to either:
	//
	// 1) cache pointers to all created CGCObjSpritePhysics created via the factory and destroy them on shutdown / level unload, or
	//
	// 2) make sure all the CGCObjSpritePhysics derived instances you create are in an object group and have the groups destroy them
	//
	// Personally I favour option 1, as I reckon it's a) more elegant and b) more philosophically 'correct'.
	//
	// The invaders are currently destroyed by using option 2 - see CGCObjGroupInvader::DestroyInvaders
	///////////////////////////////////////////////////////////////////////////

	// load level data from Ogmo Editor

	// read the oel file for level 0
	m_cLevelLoader.LoadLevelFile (FileUtils::getInstance ()->fullPathForFilename (std::string ("OgmoEditor/GCOgmoTemplateLevel.oel")).c_str ());
	m_cLevelLoader.CreateObjects (CGCFactory_ObjSpritePhysics::GetFactory ());

	// note: we have now created all the items, platforms, & invaders specified in the level file


	///////////////////////////////////////////////////////////////////////////
	// add player - this shows manual use of class factory
	///////////////////////////////////////////////////////////////////////////

	// starting position
	cocos2d::Vec2 v2MarioStartPos (60, 120);

	//(( origin.x + ( visibleSize.width * 0.5f ) ),
	//	( origin.y + ( visibleSize.height * 0.5f ) ));

	// factory creation parameters
	// N.B. note m_sPlayerCreateParams is a member variable of this class which will stay in scope whilst mario is in scope
	CGCFactoryCreationParams& sParams = m_sPlayerCreateParams;
	sParams.strClassName = "CGCObjPlayer";
	sParams.strPlistFile = "TexturePacker/Sprites/Willy/Willy.plist";
	sParams.strPhysicsShape = "mm_character_willy";
	sParams.eB2dBody_BodyType = b2_dynamicBody;
	sParams.bB2dBody_FixedRotation = true;

	// create player object
	m_pcGCOPlayer = static_cast<CGCObjPlayer*>( CGCFactory_ObjSpritePhysics::GetFactory ().CreateInstance (sParams, v2MarioStartPos) );
	m_pcGCOPlayer->setJumpHeight (200.0f);

	//this->addChild(m_pcGCOPlayer->getLivesText(), 10);


	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI1 (), 10);

	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI2 (), 10);

	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI3 (), 10);


	this->addChild (m_pcGCOPlayer->getPlayerLivesUI1 (), 11);

	this->addChild (m_pcGCOPlayer->getPlayerLivesUI2 (), 11);

	this->addChild (m_pcGCOPlayer->getPlayerLivesUI3 (), 11);

	m_pcGCOPlayer->LivesUI();

	//this->addChild(m_pcGCOLives->getLivesUI(), 20);

	//this->addChild(m_pcGCOPlayer->getLivesUI1());

	//this->addChild(m_pcGCOPlayer->getLivesUI2());

	//////////////////////////////////////////////////////////////////////////
	// test new collision handler code
	// 
	// this is proof of concept code which could be used to replace the 
	// function HandleCollisions()
	// 
	// note it will need a little additional polish (simple & noted in the 
	// header...) before it's properly ready to be used in a game :)
	// 
	//////////////////////////////////////////////////////////////////////////
	//
	// you can also pass a regular (non member) function:
	// GetCollisionManager().AddCollisionHandler( CB_TestCollisionHandler );
	// 

	GetCollisionManager ().AddCollisionHandler ([](CGCObjPlayer& rcPlayer, CGCObjItem& rcItem, const b2Contact& rcContact) -> void
		{
			//COLLISIONTESTLOG ("(lambda) the player hit an item!");
		});



	GetCollisionManager ().AddCollisionHandler ([this](GCSwitch& rcSwitch, CGCObjSwitchPlatform1& rcSwitchPlatform, const b2Contact& rcContact) -> void
		{
			if (m_pcGCOPlayer->getSwitchesHit () >= 1)
			{
				rcSwitchPlatform.DestroyPlatform ();
			}
		});

	GetCollisionManager ().AddCollisionHandler ([this](GCSwitch& rcSwitch, CGCObjSwitchPlatform2& rcSwitchPlatform, const b2Contact& rcContact) -> void
		{
			if (m_pcGCOPlayer->getSwitchesHit () >= 2)
			{
				rcSwitchPlatform.DestroyPlatform ();
			}
		});
	GetCollisionManager ().AddCollisionHandler ([this](GCSwitch& rcSwitch, CGCObjPlayer& rc_player, const b2Contact& rcContact) -> void
		{
			if (rcContact.GetFixtureA()->IsSensor() ==false && rcContact.GetFixtureB ()->IsSensor () == false)
			{
				if (rcSwitch.getSwitchHit() == false)
				{
					rcSwitch.setSwitchHit (true);
					m_pcGCOPlayer->setSwitchesHit (m_pcGCOPlayer->getSwitchesHit () + 1);
					CCLOG ("AAAA12");
				}
				
			}
			
			
		});



	GetCollisionManager().AddCollisionHandler([](CGCObjPlayer& rcPlayer, CGCObjLadder& rcLadder, const b2Contact& rcContact) -> void
	{
		//COLLISIONTESTLOG("Collided with Ladder.");

		if( rcContact.IsTouching() )
			{
				rcPlayer.setOnLadder(true);
			}

		else if (rcContact.IsTouching () == false)
		{
			rcPlayer.setOnLadder(false);
		}
	});

	GetCollisionManager().AddCollisionHandler([](CGCObjFallingPlane& rcPlane, CGCObjScalingBasicPlatform& rcPlatform, const b2Contact& rcContact) -> void
	{
		//COLLISIONTESTLOG("Plane hit Platform!");
		//CGCObjectManager::ObjectKill (&rcPlane);
		rcPlane.ResetPosition();
	});

	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjFallingPlane& rcPlane, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		//CGCObjectManager::ObjectKill(&rcPlane);
		if( rcPlane.getJustCollided() == false )
		{
			rcPlane.setJustCollided(true);
			rcPlane.ResetPosition();
			CCLOG("Player hit by Plane.");
			rcPlayer.DecrementLives();
		}
	}
	);

	//GetCollisionManager ().AddCollisionHandler
	//(

	//	[]
	//(CGCObjPlayer& rcPlayer, CGCObjMovingPlatform& rcMovingPlatform, const b2Contact& rcContact) -> void
	//	{
	//		if (rcContact.IsTouching ())
	//		{
	//			rcPlayer.SetCanJump (true); // // Mia: If is touching Platform, the Player can jump
	//		}

	//		else if (rcContact.IsTouching () == false)
	//		{
	//			rcPlayer.SetCanJump (false); // Mia: If not touching, the Player cannot jump
	//		}
	//	}
	//);

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision checks if the player is touching a platform or not, if it is touching it gives the player the ability to jump
		// if it not touching then the player cannot jump
		[]
	(CGCObjPlayer& rcPlayer, CGCObjScalingBasicPlatform& rcPlatform, const b2Contact& rcContact) -> void
		{
			//if (rcContact.IsTouching ()) //checks if it is touching
			//{
			//	rcPlayer.SetCanJump (true);  //sets the bool can jump to true if it touching
			//}

			//else if (rcContact.IsTouching () == false)
			//{
			//	rcPlayer.SetCanJump (false); // sets the bool to false if it is not touching
			//}

		}
	);

	//Dan: Handle collision with the payer and the travelator 
	GetCollisionManager ().AddCollisionHandler
	(
		[]
	(CGCObjPlayer& rcPlayer, CGCObjTravelatorPlatform& rcTravelatorPlatform, const b2Contact& rcContact) -> void
		{

			//if (rcContact.IsTouching() && rcPlayer.getIsPlayerOnPlatform())
			//{

			//	rcPlayer.setOnTravelator (true);

			//	//rcPlayer.SetCanJump (true);//Dan: Setting jump to true so the player can jump when on the travelator(i.e. ground check)

			//	rcPlayer.SetVelocity(cocos2d::Vec2(rcTravelatorPlatform.getVelocity(),rcPlayer.GetVelocity().y));

			//	// Dan: When contact with the player is made the players velocity will be increased or decreased depending on if the value is + / -

			//}
			//else if (rcContact.IsTouching () == false)
			//{
			//	rcPlayer.setOnTravelator (false);//Dan :Sets the players velocity back to normal when the player is no longer touching the platform

			//	//rcPlayer.SetCanJump (false);//Dan : making sure that the player cant jump while in the air when they are falling off the platform
			//}
		}
	);


	// Mia: Handles the Collision between the Player and the Exit Door
	GetCollisionManager ().AddCollisionHandler
	(
		[this]
	(CGCObjExitDoor& rcExitDoor, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			
			
			if (m_iKeysCollected >= m_iTotalKeys) // Mia: If the Keys Collected by Player is more than or equal than to the Total Keys Collected
			{
				playDoorOpeningAudio ();
				
				m_pcGCOScore->ScoreWriteFile(m_pcGCOScore);

				m_pcGCOPlayer->PlayerLivesWriteFile();
			
				if (m_pcGCOScore->getScoreAmount() > m_pcGCOHighScore->getHighScoreValue())
				{
					m_pcGCOHighScore->HighScoreWriteFile(m_pcGCOScore);
					//ZAF m_pcGCOHighScore->saveHighScore( m_pcGCOScore->getScoreAmount() );
				}
			ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< GCLevel2 >::CreateScene()));
			
			//	m_bPlayerKeysGathered = true;

				 // Mia: Calls the Function which plays the Door Opening Audio
			}
		}
	);

	// Mia: Handles the Collision between the Player and the Keys
	GetCollisionManager ().AddCollisionHandler
	(
		[this]
	(CGCObjKeys& rcKeys, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			if (rcKeys.getJustCollided () == false)
			{
				rcKeys.setJustCollided (true); // Mia: When player has collided with a Key
				CGCObjectManager::ObjectKill (&rcKeys); // Mia: Destroy the Key Object Sprite
				keyCollected (); // Mia: Calls Function which adds on one Key to how many Player has obtained
				playKeyAudio (); // Mia: Then calls Function which plays Key Collected Audio
				
				
			}
		}
	);

	// Mia: Handles the Collision between the Player and the Time PickUp
	GetCollisionManager ().AddCollisionHandler
	(
		[this]
	(CGCObjTimePickUp& rcPickUp, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			if (rcPickUp.getJustCollided () == false)
			{
				if (m_pcGCTimer->getCurrentTime () >= 0) // Mia: If Current Time is greater or equal to zero
				{
					rcPickUp.setJustCollided (true); // Mia: When player has collided with a Timer PickUp
					CGCObjectManager::ObjectKill (&rcPickUp); // Mia: Destroy the Timer PickUp Object Sprite
					addOnTime (); // Mia: Calls the Function which adds on Timer Increase Value (20) to whatever is the current Air Time
					//playTimerPickUpAudio (); // Mia: Calls the Function which plays Timer PickUp Audio
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
	(CGCMovingEnemies& rcMEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			CGCObjectManager::ObjectKill (&rcMEnemies);
			CCLOG("HEUFH");
			if (rcMEnemies.getJustCollided () == false)
			{
				
				rcMEnemies.setJustCollided (true);
				if (m_pcGCOScore->getScoreAmount() > m_pcGCOHighScore->getHighScoreValue())
				{
					m_pcGCOHighScore->HighScoreWriteFile(m_pcGCOScore);
				}

				RequestReset ();
				//m_pcGCTimer->ResetTimer ();
				CCLOG ("Player wacked.");
				//CGCObjectManager::ObjectKill (&rcPlayer);
				//m_bPlayerHitHostile = true;
				rcPlayer.DecrementLives ();
				//PlayerDeathSceneSwap(); //Puia Lose a life when colliding
			}
		}
	);

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
		//it will reset the level from the start
		[]
	(CGCMovingEnemies& rcMEnemies, GCObjEnemyMovementCollider& rcCollider, const b2Contact& rcContact) -> void
		{

			if (rcMEnemies.getChangedDir() == false)
			{
				if (rcMEnemies.getDefaultDirection () == true)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (false);
				}
				else if (rcMEnemies.getDefaultDirection () == false)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (true);
				}
			}
		}
	);


	GetCollisionManager ().AddCollisionHandler ([this](CGCMovingEnemies& rcMEnemies, CGCObjSwitchPlatform1& rcSwitchPlatform, const b2Contact& rcContact) -> void
		{
			if (rcMEnemies.getChangedDir () == false)
			{
				if (rcMEnemies.getDefaultDirection () == true)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (false);
				}
				else if (rcMEnemies.getDefaultDirection () == false)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (true);
				}
			}
		
		});

	GetCollisionManager ().AddCollisionHandler ([this](CGCMovingEnemies& rcMEnemies, CGCObjSwitchPlatform2& rcSwitchPlatform, const b2Contact& rcContact) -> void
		{
			if (rcMEnemies.getChangedDir () == false)
			{
				if (rcMEnemies.getDefaultDirection () == true)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (false);
				}
				else if (rcMEnemies.getDefaultDirection () == false)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (true);
				}
			}
		
		});
	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
		//it will reset the level from the start
		[]
	(CGCMovingEnemy2& rcMEnemies, GCObjEnemyMovementCollider2& rcCollider, const b2Contact& rcContact) -> void
		{
			if (rcMEnemies.getChangedDir () == false)
			{
				if (rcMEnemies.getDefaultDirection () == true)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (false);
				}
				else if (rcMEnemies.getDefaultDirection () == false)
				{
					rcMEnemies.setChangedDir (true);
					rcMEnemies.setDefaultDirection (true);
				}
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
			if (rcContact.IsTouching ()&& rcContact.GetFixtureB()->IsSensor())
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
				CGCObjectManager::ObjectKill (&rcFallingPlatforms);
				//rcFallingPlatforms.SetPhysicsTransform (cocos2d::Vec2 (-300, -300), 0); //checks if the platform can be delted, if it can then it will delete itself
			}

			//if (rcContact.IsTouching ())							//checks if it is touching
			//{
			//	rcPlayer.SetCanJump (true);							//sets the bool can jump to true if it touching);
			//}

			//else if (rcContact.IsTouching () == false)
			//{
			//	rcPlayer.SetCanJump (false);						//Sets it to false if it is not touching 
		});
}

void CGCGameLayerPlatformer::PlayerDeathSceneSwap()
{
	Director::getInstance()->replaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCLossScene >::CreateScene()));
}

void CGCGameLayerPlatformer::HighScore()
{
	

}

//////////////////////////////////////////////////////////////////////////
// on update
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );
	
	// this shows how to iterate and respond to the box2d collision info
	HandleCollisions();	

	if(m_pcGCOPlayer->getPlayerCheckLives()== true)
	{
		PlayerDeathSceneSwap();
	}

	//std::ifstream inFile;
	//inFile.open("HighScore.txt");

	//if(inFile.fail())
	//{
	//	CCLOG("bruh");
	//	return;
	//}

	
	m_pcGCTimer->Update(fTimeStep);

	m_pcGCOHighScore->Update();
	
	if( ResetWasRequested() )
	{
		VOnReset();
		m_iKeysCollected = 0; // Mia: Resets Keys Collected
		ResetRequestWasHandled();
		m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio on Reset
		playBackgroundMusic(); // Mia: Calls this Function, so it doesn't overlay
	}

	if( SkipWasRequested() )
	{
		m_pcGCOPlayer->PlayerLivesWriteFile();
		SkipRequestWasHandled ();
		ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< GCLevel2 >::CreateScene()));
		
	}

	if( QuitWasRequested() )
	{
		QuitRequestWasHandled();
		ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCMainMenu >::CreateScene()));
	}


	if (m_pcGCTimer->getCurrentTime() <= 0)
	{
		m_pcGCTimer->setCurrentTime(m_pcGCTimer->getTotalTimerDuration());

		RequestReset();
	}

	
	//HighScore();
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

	// clean up the level
	m_cLevelLoader.DestroyObjects();

	delete m_pcGCSprBackGround;
	m_pcGCSprBackGround = nullptr;

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

	IGCGameLayer::VOnDestroy();
}


///////////////////////////////////////////////////////////////////////////////
// on quit button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnQuitButton( Ref* pSender )
{
	RequestQuit();
}


void CGCGameLayerPlatformer::Callback_OnSkipButton(Ref* pSender)
{
	RequestSkip();
}


///////////////////////////////////////////////////////////////////////////////
// on reset button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnResetButton(Ref* pSender)
{
	RequestReset();
}


///////////////////////////////////////////////////////////////////////////////
// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::BeginContact( b2Contact* pB2Contact )
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA ();
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB ();

	const b2Body* pBodyA = pFixtureA->GetBody ();
	const b2Body* pBodyB = pFixtureB->GetBody ();

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*) pBodyA->GetUserData ();
	// if( this is not a GC object )
	if (pGcSprPhysA == nullptr)
	{
		return;
	}

	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*) pBodyB->GetUserData ();
	// if( this is not a GC object )
	if (pGcSprPhysB == nullptr)
	{
		return;
	}

	

	//// ignore contact between player projectile and item for collision resolution purposes
	//if(	pGcSprPhysA->GetGCTypeID() != pGcSprPhysB->GetGCTypeID() )
	//{
	//	if(		(	( pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf( CGCObjPlayer ) )
	//			 &&	( pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCObjScalingFallingPlatform) ) )
	//		||	(	( pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CGCObjScalingFallingPlatform) )
	//			 &&	( pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCObjPlayer) ) ) )
	//	{
	//		// ignore the collision!

	//		if (m_pcGCOPlayer->GetVelocity ().y > 0)
	//		{
	//				// ignore the collision!
	//				pB2Contact->SetEnabled (false);

	//		}

	//		if (m_pcGCOPlayer->GetVelocity ().y <= 0)
	//		{
	//			if (pB2Contact->GetFixtureA ()->IsSensor () || pB2Contact->GetFixtureB ())
	//			{
	//				// ignore the collision!
	//				pB2Contact->SetEnabled (true);
	//			}
	//		}
	//		// ignore the collision!
	//		//pB2Contact->SetEnabled( true );
	//		//
	//		// insert logic relating to this collision here
	//		//
	//		//

	//		
	//	}

	//	if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
	//		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) )
	//		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
	//			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) ))
	//	{
	//		// ignore the collision!

	//		if (m_pcGCOPlayer->GetVelocity ().y > 0)
	//		{
	//			// ignore the collision!
	//			pB2Contact->SetEnabled (false);
	//			
	//		}

	//	
	//			if (m_pcGCOPlayer->GetVelocity ().y <= 0)
	//			{
	//				if (pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor () || pB2Contact->IsTouching () && pB2Contact->GetFixtureA ()->IsSensor ())
	//				{
	//				// ignore the collision!


	//					// ignore the collision!
	//				pB2Contact->SetEnabled (true);
	//			}
	//		}
	//		// ignore the collision!
	//		//pB2Contact->SetEnabled( true );
	//		//
	//		// insert logic relating to this collision here
	//		//
	//		//


	//	}


	//	if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
	//		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) ) ))
	//	{
	//		// ignore the collision!
	//		
	//		if (m_pcGCOPlayer->GetVelocity ().y > 3.0f)
	//		{
	//			pB2Contact->SetEnabled (false);
	//		}

	//		if (pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor ())
	//		{
	//		if (m_pcGCOPlayer->GetVelocity ().y <= 0)
	//		{
	//			// ignore the collision!
	//		
	//		
	//				// ignore the collision!
	//				pB2Contact->SetEnabled (true);
	//			}
	//		}
	//		// ignore the collision!
	//		//pB2Contact->SetEnabled( true );
	//		//
	//		// insert logic relating to this collision here
	//		//
	//		//


	//	}
	//}

	//if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
	//	&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) ) )
	//	|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) )
	//		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) ))
	//{
	//	// ignore the collision!

	//	if (m_pcGCOPlayer->GetVelocity ().y > 0)
	//	{
	//		pB2Contact->SetEnabled (false);
	//	}

	//	if (m_pcGCOPlayer->GetVelocity ().y <= 0)
	//	{
	//		if (pB2Contact->GetFixtureA ()->IsSensor () || pB2Contact->GetFixtureB ())
	//		{
	//			pB2Contact->SetEnabled (true);
	//		}
	//	}
	//	// ignore the collision!
	//	//pB2Contact->SetEnabled( true );
	//	//
	//	// insert logic relating to this collision here
	//	//
	//	//


	//}

	if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) ) )
		)
	{


		
		if (m_pcGCOPlayer->GetVelocity ().y > 0 && !pB2Contact->GetFixtureB ()->IsSensor ())
		{
			m_pcGCOPlayer->setIsPlayerOnPlatform (false);
			//m_bCheckIfPlayerIsAbovePlatform = false;
			pB2Contact->SetEnabled (false);
		}

		if (m_pcGCOPlayer->GetVelocity ().y <= 0 && pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor () == true)
		{
			m_pcGCOPlayer->setIsPlayerOnPlatform (true);
			//m_bCheckIfPlayerIsAbovePlatform = true;

			pB2Contact->SetEnabled (true);
		}
		//if (m_pcGCOPlayer->getPlayerDiedFromFalling())
		//{
		//	CGCObjectManager::ObjectKill (m_pcGCOPlayer);
		//}
	}

	if (( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) ))
	{
		if (m_pcGCOPlayer->GetVelocity ().y <= 0 && pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor () == true)

		{
			m_pcGCOPlayer->setOnTravelator (true);

			//rcPlayer.SetCanJump (true);//Dan: Setting jump to true so the player can jump when on the travelator(i.e. ground check)

			m_pcGCOPlayer->SetVelocity (cocos2d::Vec2 (m_pcGCOPlayer->getTravelatorVelocity (), m_pcGCOPlayer->GetVelocity ().y));

			// Dan: When contact with the player is made the players velocity will be increased or decreased depending on if the value is + / -
		}
	}
	
	if ((pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CGCBasicEnemies))
		&& (pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCObjPlayer))
		|| ((pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CGCObjPlayer))
			&& (pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCBasicEnemies))))
	{

		//CGCObjectManager::ObjectKill (&rcEnemies);
		//m_pcGCTimer->ResetTimer ();
		//CGCObjectManager::ObjectKill (&rcEnemies);
		
		if(m_pcGCOScore->getScoreAmount() > m_pcGCOHighScore->getHighScoreValue())
		{
			m_pcGCOHighScore->HighScoreWriteFile(m_pcGCOScore);
		}
		
		
		CCLOG("Player Died.");
		//m_bPlayerHitHostile = true;
		//PlayerDeathSceneSwap();
		RequestReset();
		m_pcGCOPlayer->DecrementLives(); //Puia Lose a life when colliding
		
	}

	
	

}


///////////////////////////////////////////////////////////////////////////////
// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerPlatformer::EndContact (b2Contact* pB2Contact)
{
	{
		const b2Fixture* pFixtureA = pB2Contact->GetFixtureA ();
		const b2Fixture* pFixtureB = pB2Contact->GetFixtureB ();

		const b2Body* pBodyA = pFixtureA->GetBody ();
		const b2Body* pBodyB = pFixtureB->GetBody ();

		CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*) pBodyA->GetUserData ();
		// if( this is not a GC object )
		if (pGcSprPhysA == nullptr)
		{
			return;
		}

		CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*) pBodyB->GetUserData ();
		// if( this is not a GC object )
		if (pGcSprPhysB == nullptr)
		{
			return;
		}

		if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
			|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
				&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) ) )
			)
		{
			if (pB2Contact->IsTouching () == false)
			{
				//m_pcGCOPlayer->SetCanJump (false);
				m_pcGCOPlayer->FallDamage ();
			}
			
		}
	}
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


	if (( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingBasicPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjMovingPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjScalingFallingPlatform) )  )
		)
	{


			pB2Contact->SetEnabled (false);
				
			if (m_pcGCOPlayer->getIsPlayerOnPlatform() == true)
			
			{
				pB2Contact->SetEnabled (true);
				m_pcGCOPlayer->SetCanJump (true);
				m_pcGCOPlayer->FallDamage ();
				
			}

			if( m_pcGCOPlayer->getPlayerDiedFromFalling() )
			{
				m_pcGCOPlayer->DecrementLives();
				RequestReset();
			}

	}

	 if ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) 
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )))
	 {
		 if (m_pcGCOPlayer->getIsPlayerOnPlatform () == true)

		 {
			 m_pcGCOPlayer->SetCanJump (true);

			 m_pcGCOPlayer->FallDamage ();
		 }
	 }

	 if (( pGcSprPhysA->GetGCTypeID () != GetGCTypeIDOf (CGCObjTravelatorPlatform) )
		 && ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		 || ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			 && ( pGcSprPhysB->GetGCTypeID () != GetGCTypeIDOf (CGCObjTravelatorPlatform) ) ))
	 {
		 {
			 m_pcGCOPlayer->setOnTravelator (false);//Dan :Sets the players velocity back to normal when the player is no longer touching the platform
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
void CGCGameLayerPlatformer::HandleCollisions()
{
	// check for collisions
	b2Body* pBodyToDestroy = nullptr;
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
		// and this is what we're checking for :)
		const std::string*	pstrCheckMe		= cocos2d::GB2ShapeCache::getFixtureIdText( pFixtureA );
		bool				bNameMatches	= ( 0 == pstrCheckMe->compare( "WillyBottomSensor" ) );
		bool				bIsASensor		= pFixtureA->IsSensor();

		if(	pstrCheckMe && bNameMatches && bIsASensor )
		{
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

		// is this collision an invader and a projectile?
		// if so, kill the invader
		if(	   pB2Contact->IsEnabled()
			&& ( pGcSprPhysA->GetGCTypeID() != pGcSprPhysB->GetGCTypeID() ) )
		{
			// returns a valid ptr if instance's EXACT type matches or nullptr if not
			CGCObjInvader* pInvaderA = CGCObject::SafeCastToDerived< CGCObjInvader* >( pGcSprPhysA );
			CGCObjInvader* pInvaderB = CGCObject::SafeCastToDerived< CGCObjInvader* >( pGcSprPhysB );

			// at least one of them is an invader?
			if(	pInvaderA || pInvaderB )
			{
				CGCObjInvader*	pKillMe			= ( pInvaderA ? pInvaderA : pInvaderB );
				GCTypeID		tidNotInvader	= ( pInvaderA ? pGcSprPhysB->GetGCTypeID() : pGcSprPhysA->GetGCTypeID() );
			
				if( GetGCTypeIDOf( CGCObjProjectilePlayer ) == tidNotInvader )
				{
					CGCObjectManager::ObjectKill( pKillMe );
				}
			}
		}
	}
}

