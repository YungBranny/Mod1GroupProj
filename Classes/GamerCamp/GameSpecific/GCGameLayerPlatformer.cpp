///////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
///////////////////////////////////////////////////////////////////////////////

#include "AppDelegate.h"
#include "GCGameLayerPlatformer.h"
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GameSpecific/Collectables/GCObjKeys.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCEnemyMovementCollider.h"
#include "GamerCamp/GameSpecific/Enemies/GCEnemyMovementCollider2.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane2.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane3.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane4.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane5.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane6.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane7.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane8.h"
#include "GamerCamp/GameSpecific/Enemies/Planes/GCOFallingPlane9.h"
#include "GamerCamp/GameSpecific/Enemies/GCHazardChild.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemy2.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDown.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDownSlow.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyUpDownFast.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyLRSlow.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemyLRFast.h"
#include "GamerCamp/GameSpecific/ExitDoor/GCObjExitDoor.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCLossScene.h"
#include "GamerCamp/GameSpecific/GameWinLossScenes/GCWinScene.h"
#include "GamerCamp/GameSpecific/Ladder/GCObjLadder.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"
#include "GamerCamp/GameSpecific/Levels/GCLevel2.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasePlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform1.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform2.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform3.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform4.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform5.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform6.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBasicPlatform7.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjBrickPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjMovingPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingBasicPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatformManager.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjScalingFallingPlatform.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCSwitch.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjSwitchPlatform1.h"
#include "GamerCamp/GameSpecific/NewPlatforms/CGCObjSwitchPlatform2.h"
#include "GamerCamp/GameSpecific/NewPlatforms/GCObjTravelatorPlatform.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"
#include "GamerCamp/GameSpecific/Score/GCObjScore.h"
#include "GamerCamp/GameSpecific/Score/GCObjHighScore.h"
#include "GamerCamp/GameSpecific/Timer/GCObjTimer.h"

USING_NS_CC;

CGCGameLayerPlatformer::CGCGameLayerPlatformer ()
	: IGCGameLayer ( GetGCTypeIDOf ( CGCGameLayerPlatformer ) )
	, m_pcGCGroupItem			   ( nullptr )
	, m_pcGCGroupInvader		   ( nullptr )
	, m_pcGCGroupProjectilePlayer  ( nullptr )
	, m_pcGCTimer				   ( nullptr )
	, m_pcGCOPlayer                ( nullptr )
	, m_pcGCOKeys                  ( nullptr )
	, m_pcGCOKeys1                 ( nullptr )
	, m_pcGCOKeys2                 ( nullptr )
	, m_pcGCOScore                 ( nullptr )
	, m_pcGCOHighScore             ( nullptr )
	, m_bResetWasRequested			  ( false )
	, m_bSkipWasRequested			  ( false )
	, m_bQuitWasRequested			  ( false )
	, m_bCheckIfPlayerIsAbovePlatform ( false )
	, m_bDoorUnlocked				  ( false )
{
	m_iTotalKeys = 5; // Mia: Sets the total amount of Keys the Player needs to obtain to be able to unlock the Exit Door and move on

	m_iKeysCollected = 0; // Mia: Sets Default Keys to 0, so we can add 1 more on as Player collects them
}

CGCGameLayerPlatformer::~CGCGameLayerPlatformer()
{

}

void CGCGameLayerPlatformer::keyCollected() // Mia: This function adds one more Key onto how many the Player obtains
{
	m_iKeysCollected++; // Mia: Adds a Key
	m_pcGCOScore->IncreaseScore(); // Mia: Calls IncreaseScore Function from GCObjScore.cpp
	CCLOG("Key Collected."); // Mia: Checks to make sure Player has picked up Key only once otherwise will call it continuously
}

void CGCGameLayerPlatformer::playBackgroundMusic() // Mia: Function that is called when we want the Background Music to play
{
	m_pcGCBackgroundAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCBackgroundAudio->playBackgroundMusic("Sounds/BackgroundMusic/CrystalCoralReefSvRV1.wav", true); // Mia: Play Audio by locating File, set to 'True' to loop
}

void CGCGameLayerPlatformer::playKeyAudio() // Mia: Function that is called when we want the Collected Key Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/Collectables/Key/item_pickup.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

void CGCGameLayerPlatformer::playDoorOpeningAudio() // Mia: Function that is called when we want the Door Opened Sound Effect to play
{
	m_pcGCSoundEffectsAudio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_pcGCSoundEffectsAudio->playEffect("Sounds/Door/OpeningDoor.wav", false); // Mia: Play Audio by locating File, set to 'False' to not loop
}

void CGCGameLayerPlatformer::onEnter()
{
	IGCGameLayer::onEnter();

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
	Size visibleSize = Director::getInstance ()->getVisibleSize ();
	Point origin = Director::getInstance ()->getVisibleOrigin ();

	// create the default object group
	IGCGameLayer::VOnCreate ();

	// create and register the object group for the platform objects
	m_pcGCGroupPlatform = new CGCObjGroupPlatform ();
	CGCObjectManager::ObjectGroupRegister (m_pcGCGroupPlatform);

	// Mia: Here are three 'cheat' buttons we used for testing purposes. These buttons are located on the right side of each and every Level
	MenuItemImage* pResetItem // Mia: This button resets the Level
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnResetButton, this));

	pResetItem->setPosition (Vec2 (( ( visibleSize.width - ( pResetItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( ( pResetItem->getContentSize ().height * 0.5f ) + origin.y ) )));

	MenuItemImage* pSkipItem // Mia: This button skips a Level onto the next
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnSkipButton, this));

	pSkipItem->setPosition (Vec2 (( ( visibleSize.width - ( pSkipItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( ( pSkipItem->getContentSize ().height * 6.5f ) + origin.y ) )));

	MenuItemImage* pQuitItem // Mia: This button quits the Game back onto the Main Menu
		= MenuItemImage::create ("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1 (CGCGameLayerPlatformer::Callback_OnQuitButton, this));

	pQuitItem->setPosition (Vec2 (( ( visibleSize.width - ( pQuitItem->getContentSize ().width * 0.5f ) ) + origin.x ),
		( ( visibleSize.height - ( pQuitItem->getContentSize ().height * 0.8f ) ) + origin.y )));

	Menu* pMenu = Menu::create (pResetItem, pSkipItem, pQuitItem, nullptr);
	pMenu->setPosition (Vec2::ZERO);
	this->addChild (pMenu, 1);
	
	m_pcGCOScore = new CGCObjScore (); // Mia: Creates Score

	this->addChild (m_pcGCOScore->getScoreText(), 10); // Mia: Adds Score Text and sets size to the Level UI

	m_pcGCOScore->ScoreClearFile(m_pcGCOScore); //Dan: When the game is started the score inside of the external file will be set to 0
	
	m_pcGCOHighScore = new CGCObjHighScore(m_pcGCOScore); //Dan: Creating Highscore

	m_pcGCOHighScore->HighScoreReadFile(m_pcGCOScore); //Dan: opens the highscore external file and gets the value inside and sets to the highscore
	
	this->addChild(m_pcGCOHighScore->getHighScoreText(), 10); //Dan: adding highscore to UI layer

	playBackgroundMusic(); // Mia: Calling 'playBackgroundMusic' Function, so the Audio plays as soon as level loads

	m_pcGCTimer = new CGCObjTimer (); //Dan: creating Timer

	//this->addChild(m_pcGCTimer->getTimerText(), 10);
	this->addChild (m_pcGCTimer->getTimerBar (), 50);//Dan: Timer layer UI set
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

	//Dan: Adds player lose lives UI to the scene

	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI1 (), 10);

	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI2 (), 10);

	this->addChild (m_pcGCOPlayer->getPlayerLoseLivesUI3 (), 10);

	//Dan: Adds player lives UI to the scene

	this->addChild (m_pcGCOPlayer->getPlayerLivesUI1 (), 11);

	this->addChild (m_pcGCOPlayer->getPlayerLivesUI2 (), 11);

	this->addChild (m_pcGCOPlayer->getPlayerLivesUI3 (), 11);

	m_pcGCOPlayer->LivesUI();

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


	//Brandon - This is where the switches will delete the platforms/doors associated with them  when the player has has collided with a switch.
	//It does this by adding up every time the player hits a switch which will then cause the if statement to be set to true allowing the platform/Wall to be deleted 
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
				}
				
			}
			
			
		});

	// Mia: Handles the collision between Plane Enemy and Basic Platform
	GetCollisionManager().AddCollisionHandler([](CGCObjFallingPlane& rcPlane, CGCObjScalingBasicPlatform& rcPlatform, const b2Contact& rcContact) -> void
	{
		rcPlane.ResetPosition(); // Mia: The position of the Plane is reset back to its original position
	});

	// Mia: Handles the collision between Plane Enemy and Travelator Platform
	GetCollisionManager().AddCollisionHandler([](CGCObjFallingPlane& rcPlane, CGCObjTravelatorPlatform& rcPlatform, const b2Contact& rcContact) -> void
	{
		rcPlane.ResetPosition(); // Mia: The position of the Plane Enemy is reset back to its original position
	});

	// Mia: Handles the collision between Plane Enemy and Player
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjFallingPlane& rcPlane, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		if( rcPlane.getJustCollided() == false )
		{
			rcPlane.setJustCollided(true); // Mia: When Plane Enemy collides with Player
			rcPlane.ResetPosition(); // Mia: Reset the Plane Enemys position to original position
			CCLOG("Player hit by Plane."); // Mia: Shows in the output for debug purposes that Plane has indeed hit Player and only once
			rcPlayer.DecrementLives(); // Mia: Decreases Player Lives by one
		}
	}
	);


	//Dan: Handle collision with the player and the travelator 
	GetCollisionManager ().AddCollisionHandler
	(
		[]
	(CGCObjPlayer& rcPlayer, CGCObjTravelatorPlatform& rcTravelatorPlatform, const b2Contact& rcContact) -> void
		{

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

	GetCollisionManager ().AddCollisionHandler
	(
		//Brandon Middleton
		//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
		//it will reset the level from the start
		[this]
	(CGCMovingEnemies& rcMEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			CGCObjectManager::ObjectKill (&rcMEnemies);
			if (rcMEnemies.getJustCollided () == false)
			{	
				rcMEnemies.setJustCollided (true);
				if (m_pcGCOScore->getScoreAmount() > m_pcGCOHighScore->getHighScoreValue())
				{
					//Dan: Sets highscore if the score value passes it
					m_pcGCOHighScore->HighScoreWriteFile(m_pcGCOScore);
				}
				RequestReset ();
				CCLOG ("Player wacked.");
				rcPlayer.DecrementLives ();
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

	//Brandon Middleton
	//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
	//it will reset the level from the start
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

	//Brandon Middleton
	//This collision is in charge of detecting if the player has collided with an enemy or not, if it has collided with an enemy it
	//it will reset the level from the start
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

			if (rcFallingPlatforms.GetCanDelete () == true) //checks if the platform can be deleted, if it can then it will delete itself
			{
				CGCObjectManager::ObjectKill (&rcFallingPlatforms);
			}
		});
}

void CGCGameLayerPlatformer::PlayerDeathSceneSwap()
{
	//Dan: When the player dies the scene is replaced with the death scene
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.1f, TGCGameLayerSceneCreator< CGCLossScene >::CreateScene()));
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
		//Dan: if the player dies the death screen is shown
		PlayerDeathSceneSwap();
	}
	
	//Brandon this checks to see if the door is open and if it has been collided with yet, if it has then it disables the players movement, decreases the timer until it has ran out and then it switches scene 
	if (m_pcGCTimer->getCurrentTime () > 2.0f && m_bDoorUnlocked == true)
	{
		m_pcGCTimer->setCurrentTime (m_pcGCTimer->getCurrentTime () - 0.4f);
		m_pcGCOScore->IncreaseScore(); // Mia: Calls IncreaseScore function from GCObjScore.cpp when Player collides with door
		m_pcGCOScore->ScoreWriteFile(m_pcGCOScore); // Mia: Writes over previous Score and saves it, so Player can continue to next Level with updates Score
	}

	if (m_bDoorUnlocked == true && m_pcGCTimer->getCurrentTime () < 2.0f)
	{
		ReplaceScene (TransitionMoveInR::create (0.1f, TGCGameLayerSceneCreator< GCLevel2 >::CreateScene ()));
	}
	if(m_bDoorUnlocked == true)
	{
		m_pcGCOPlayer->SetVelocity (Vec2 (0, 0));
	}
	
	
	m_pcGCTimer->Update(fTimeStep);

	m_pcGCOHighScore->Update();
	
	if( ResetWasRequested() )
	{
		VOnReset();
		m_iKeysCollected = 0; // Mia: Resets Keys Collected by Player to 0
		ResetRequestWasHandled();
		m_pcGCBackgroundAudio->stopBackgroundMusic(); // Mia: Stops all Background Audio on Reset
		playBackgroundMusic(); // Mia: Calls this Function, so it doesn't overlay
	}

	if( SkipWasRequested() )
	{
		m_pcGCOPlayer->PlayerLivesWriteFile();
		SkipRequestWasHandled ();
		ReplaceScene(TransitionMoveInR::create(0.1f, TGCGameLayerSceneCreator< GCLevel2 >::CreateScene()));
		
	}

	if( QuitWasRequested() )
	{
		QuitRequestWasHandled();
		ReplaceScene(TransitionMoveInR::create(0.1f, TGCGameLayerSceneCreator< CGCMainMenu >::CreateScene()));
	}


	if (m_pcGCTimer->getCurrentTime() <= 0)
	{
		//Dan: Reset Timer 
		m_pcGCTimer->setCurrentTime(m_pcGCTimer->getTotalTimerDuration());

		RequestReset();
	}

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

	///////////////////////////////////////////////////////////////////////////
	// N.B. because object groups must register manually, 
	// we also unregister them manually
	///////////////////////////////////////////////////////////////////////////
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

	//Brandon Checks if the players sensor located on his fees has collided with any of the platforms,
	//depending on if this is true or not collision will be enabled/disabled allowing the player to jump from underneath a platform to land on top of it 
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
			pB2Contact->SetEnabled (false);
		}
		if (m_pcGCOPlayer->GetVelocity ().y <= 0 && pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor () == true)
		{
			m_pcGCOPlayer->setIsPlayerOnPlatform (true);
			pB2Contact->SetEnabled (true);
		}
	}

	if (( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjTravelatorPlatform) ) ))
	{
		if (m_pcGCOPlayer->GetVelocity ().y <= 0 && pB2Contact->IsTouching () && pB2Contact->GetFixtureB ()->IsSensor () == true)

		{
			m_pcGCOPlayer->setOnTravelator (true);
			m_pcGCOPlayer->SetVelocity (cocos2d::Vec2 (m_pcGCOPlayer->getTravelatorVelocity (), m_pcGCOPlayer->GetVelocity ().y));
			// Dan: When contact with the player is made the players velocity will be increased or decreased depending on if the value is + / -
		}
	}

	//detects if the player has collided with a basic enemy (hazard) if true the player will lose a life and the level will reset 
	if ((pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CGCBasicEnemies))
		&& (pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCObjPlayer))
		|| ((pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CGCObjPlayer))
			&& (pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CGCBasicEnemies))))
	{		
		if(m_pcGCOScore->getScoreAmount() > m_pcGCOHighScore->getHighScoreValue())
		{
			m_pcGCOHighScore->HighScoreWriteFile(m_pcGCOScore);
		}
		RequestReset();
		m_pcGCOPlayer->DecrementLives(); //Dan: When the player collides with any of the above they lose a life
		
	}

	if (( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjExitDoor) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjExitDoor) ) ))
	{
			if (m_iKeysCollected >= m_iTotalKeys) // Mia: If the Keys Collected by Player is more than or equal than to the Total Keys Collected
			{
				if (m_bDoorUnlocked == false)
				{
					playDoorOpeningAudio (); // Mia: Calls the Function which plays the Door Opening Audio
				}
				
				m_bDoorUnlocked = true;
				m_pcGCOScore->ScoreWriteFile (m_pcGCOScore);// Dan: when the next level is loaded the score is writen to an external file before, then read on the next level
				m_pcGCOPlayer->PlayerLivesWriteFile ();//Dan: PLayer lives saved to external file
				if (m_pcGCOScore->getScoreAmount () > m_pcGCOHighScore->getHighScoreValue ())
				{
					//Dan:Check if the score is higher then the current highscore, if so replace the highscore
					m_pcGCOHighScore->HighScoreWriteFile (m_pcGCOScore);
				}
			}
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
				m_pcGCOPlayer->FallDamage (); // Mia: Call FallDamage function from GCObjPlayer.cpp
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

	//Brandon - Presolve this function also helps the collision be enabled/disabled with the player and collisions, it also sets the players ability to jump depending if the player is on a platform
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
				m_pcGCOPlayer->FallDamage (); // Mia: Call FallDamage function from GCObjPlayer.cpp
				
			}
			if( m_pcGCOPlayer->getPlayerDiedFromFalling() ) // Mia: If this function is called
			{
				m_pcGCOPlayer->DecrementLives(); // Mia: Decrease Player Lives by one
				RequestReset(); // Mia: Then request reset
			}
	}

	//Sets the players jump to true when collided, this is in its own seperate function as the collision with the brick platforms should always be enabled
	 if ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )
		&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) ) 
		|| ( ( pGcSprPhysA->GetGCTypeID () == GetGCTypeIDOf (CGCObjPlayer) )
			&& ( pGcSprPhysB->GetGCTypeID () == GetGCTypeIDOf (GCObjBrickPlatform) )))
	 {
		 if (m_pcGCOPlayer->getIsPlayerOnPlatform () == true)

		 {
			 m_pcGCOPlayer->SetCanJump (true);

			 m_pcGCOPlayer->FallDamage (); // Mia: Call FallDamage function from GCObjPlayer.cpp
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

