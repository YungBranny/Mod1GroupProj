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
//#include "GamerCamp/GameSpecific/Timer/GCObjTimerBar.h"
#include "GamerCamp/GameSpecific/Keys/GCObjKeys.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemies.h"
#include "GamerCamp/GameSpecific/PlatformTest/GCObjLongPlatformTest.h"
#include "GamerCamp/GameSpecific/PlatformTest/GCObjShortPlatformTest.h"
#include "GamerCamp/GameSpecific/Door/GCObjDoor.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"
#include "GamerCamp/GameSpecific/Keys/GCObjTimePickUp.h"

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
, m_pcGCGroupItem				( nullptr )
, m_pcGCGroupInvader			( nullptr )
, m_pcGCGroupProjectilePlayer	( nullptr )
, m_pcGCSprBackGround			( nullptr )
//, m_pcGCsprTimerBar				( nullptr )
, m_pcGCOPlayer					( nullptr )
, m_pcGCTimer					( nullptr )
//, m_pcGCTimerBar				( nullptr )
, m_pcGCOKeys                   ( nullptr )
, m_pcGCOKeys1                  ( nullptr )
, m_pcGCOKeys2                  ( nullptr )
, m_pcGCOTimePickUp             ( nullptr )
, m_pcGCODoor                   ( nullptr )
, m_pcGCBasicEnemies			( nullptr )
, m_pcGCBasicEnemies2			( nullptr )
, m_pcGCMovingEnemies			( nullptr )
, m_pcGCLongPlatformTest1		( nullptr )
, m_pcGCShortPlatformTest1      ( nullptr )
, m_pcGCLongPlatformTest2		( nullptr )
, m_pcGCShortPlatformTest2		( nullptr )
, m_pcGCLongPlatformTest3		( nullptr )
, m_pcGCShortPlatformTest3		( nullptr )
, m_pcGCLongPlatformTest4		( nullptr )
, m_pcGCShortPlatformTest4		( nullptr )
, m_pcGCLongPlatformTest5		( nullptr )
, m_pcGCShortPlatformTest5		( nullptr )
, m_bResetWasRequested			( false )

{

	m_totalKeys = 3;

	m_keysCollected = 0;
	
}


//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
CGCGameLayerPlatformer::~CGCGameLayerPlatformer()
{
}

void CGCGameLayerPlatformer::keyCollected()
{
	m_keysCollected++;
	CCLOG("Key Collected");
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
	
	// create and register the object group for the invader objects
	//m_pcGCGroupInvader = new CGCObjGroupInvader( 64 );
	//CGCObjectManager::ObjectGroupRegister( m_pcGCGroupInvader );

	// create and register the object group for the player projectile objects
	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupProjectilePlayer );


	


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
	

	


	
	//m_pcGCTimerBar = new CGCObjTimerBar();
	
	
	

	//const char* keysSprite = "TexturePacker/Sprites/Coin/Coin.plist";
	//{
	//	m_pcGCOKeys = new CGCObjKeys();
	//	m_pcGCOKeys->CreateSprite(keysSprite);
	//	m_pcGCOKeys->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//	m_pcGCOKeys->SetParent(IGCGameLayer::ActiveInstance());
	//}

	//m_pcGCOKeys = new CGCObjKeys();
	//m_pcGCOKeys->CreateSprite("TexturePacker/Sprites/Coin/Coin.plist");
	//m_pcGCOKeys->SetSpritePosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.5));
	//this->addChild();
	//m_pcGCOKeys->CreateSprite("TexturePacker/Sprites/Coin/Coin.png");
	
	
    ///////////////////////////////////////////////////////////////////////////
    // add label
	///////////////////////////////////////////////////////////////////////////

 	// create and initialize a label
    Label* pLabel = Label::createWithTTF( "Game - Top button to Quit, bottom button to Reset", "fonts/arial.ttf", 24);

    // position the label on the center of the screen
    pLabel->setPosition( Vec2( visibleSize.width/2, visibleSize.height - 50 ) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

	//"TexturePacker/Backgrounds/Placeholder/background.plist"
    //
    // add "CGCGameLayerPlatformer" splash screen"

	/*const char* pszPlist_TimerBar = "TexturePacker/Sprites/TimerBar/WhiteSquare.plist";
	{
		m_pcGCsprTimerBar = new CGCObjSprite();
		
		m_pcGCsprTimerBar->CreateSprite(pszPlist_TimerBar);
		m_pcGCsprTimerBar->SetResetPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2) );
		m_pcGCsprTimerBar->SetParent(IGCGameLayer::ActiveInstance());
		m_pcGCsprTimerBar->SetScale(0.1f, 0.1f);
	}*/
	
	const char* pszPlist_background = "TexturePacker/Backgrounds/Placeholder/background.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite();
		m_pcGCSprBackGround->CreateSprite( pszPlist_background );
		m_pcGCSprBackGround->SetResetPosition( Vec2( visibleSize.width/2, visibleSize.height/2 ) );
		m_pcGCSprBackGround->SetParent( IGCGameLayer::ActiveInstance() );
		
 	}

	m_pcGCTimer = new CGCObjTimer();
	
   this->addChild(m_pcGCTimer->getTimerText(), 10);
	
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
	m_pcGCOPlayer->SetResetPosition( cocos2d::Vec2(50,130) );

	m_pcGCOKeys = new CGCObjKeys();
	m_pcGCOKeys1 = new CGCObjKeys();
	m_pcGCOKeys1->SetResetPosition(cocos2d::Vec2(570, 300));
	m_pcGCOKeys2 = new CGCObjKeys();
	m_pcGCOKeys2->SetResetPosition(cocos2d::Vec2(750, 220));

	m_pcGCOTimePickUp - new CGCObjTimePickUp();

	m_pcGCODoor = new CGCObjDoor();

	///////// Platforms

	m_pcGCLongPlatformTest1		=	new CGCObjLongPlatformTest	();
	m_pcGCLongPlatformTest1->SetStartPos (cocos2d::Vec2 (0, 100));
	m_pcGCLongPlatformTest2		=	new CGCObjLongPlatformTest	();
	m_pcGCLongPlatformTest2->SetStartPos (cocos2d::Vec2 (130, 100));
	m_pcGCLongPlatformTest3		=	new CGCObjLongPlatformTest	();
	m_pcGCLongPlatformTest3->SetStartPos (cocos2d::Vec2 (260, 100));
	m_pcGCLongPlatformTest4		=	new CGCObjLongPlatformTest	();
	m_pcGCLongPlatformTest4->SetStartPos (cocos2d::Vec2 (390, 100));
	m_pcGCLongPlatformTest5		=	new CGCObjLongPlatformTest	();
	m_pcGCLongPlatformTest5->SetStartPos (cocos2d::Vec2 (520, 100));

	m_pcGCShortPlatformTest1	=	new CGCObjShortPlatformTest ();
	m_pcGCShortPlatformTest1->SetStartPos (cocos2d::Vec2 (650, 150));
	m_pcGCShortPlatformTest2	=	new CGCObjShortPlatformTest ();
	m_pcGCShortPlatformTest2->SetStartPos (cocos2d::Vec2 (750, 200));
	m_pcGCShortPlatformTest3	=	new CGCObjShortPlatformTest ();
	m_pcGCShortPlatformTest3->SetStartPos (cocos2d::Vec2 (830, 250));
	m_pcGCShortPlatformTest4	=	new CGCObjShortPlatformTest ();
	m_pcGCShortPlatformTest4->SetStartPos (cocos2d::Vec2 (700, 300));
	m_pcGCShortPlatformTest5	=	new CGCObjShortPlatformTest	();
	m_pcGCShortPlatformTest5->SetStartPos (cocos2d::Vec2 (570, 250));
	//m_pcGCPlatformTest1->SetResetPosition (v2MarioStartPos);
	
	//enemy
	Vec2 v2Enemy1StartPos = ( cocos2d::Vec2(570,120) );
	m_pcGCBasicEnemies = new CGCBasicEnemies ();
	m_pcGCBasicEnemies->SetResetPosition (v2Enemy1StartPos);
	m_pcGCBasicEnemies->setGravity(1.0);

	//m_pcGCBasicEnemies2 = new CGCBasicEnemies ();
	//m_pcGCBasicEnemies2->SetResetPosition (v2Enemy1StartPos);
	//m_pcGCBasicEnemies2->setGravity (0.0f);

	m_pcGCMovingEnemies = new CGCMovingEnemies ();
	m_pcGCMovingEnemies->SetResetPosition (cocos2d::Vec2(250,130));
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


	// handle collisions between invader and projectile - both are killed
	GetCollisionManager().AddCollisionHandler
	( 
		[] 
		( CGCObjProjectilePlayer& rcProjectile, CGCObjInvader& rcInvader, const b2Contact& rcContact ) -> void
		{
			CGCObjectManager::ObjectKill( &rcProjectile );
			CGCObjectManager::ObjectKill( &rcInvader );
		} 
	);

	GetCollisionManager().AddCollisionHandler
	(
		[]
	(CGCObjPlayer& rcPlayer, CGCObjShortPlatformTest& rcShortPlatformTest, const b2Contact& rcContact) -> void
		{
			rcPlayer.SetCanJump(true);
		}
	);

	GetCollisionManager().AddCollisionHandler
	(
		[]
	(CGCObjPlayer& rcPlayer, CGCObjLongPlatformTest& rcLongPlatformTest, const b2Contact& rcContact) -> void
		{
			rcPlayer.SetCanJump(true);
		}
	);

	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjDoor& rcDoor, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		if( m_keysCollected >= m_totalKeys )
		{
			Director::getInstance ()->replaceScene (TransitionRotoZoom::create (1.0f, TGCGameLayerSceneCreator< CGCMainMenu >::CreateScene ()));
			//ReplaceScene(TransitionCrossFade::create(1.0f, CMenuLayer::scene()));
		}
	}
	);

	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjKeys& rcKeys, CGCObjPlayer &rcPlayer, const b2Contact& rcContact) -> void
	{
		if( rcKeys.getJustCollided() == false )
		{
			rcKeys.setJustCollided(true);
			CGCObjectManager::ObjectKill(&rcKeys);
			keyCollected();
		}
	}
	);

	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CGCObjTimePickUp& rcPickUp, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
	{
		if( m_pcGCTimer->getCurrentTime() >= 0 )
		{
			rcPickUp.setJustCollided(true);
			CGCObjectManager::ObjectKill(&rcPickUp);
			//m_pcGCTimer->setCurrentTime(m_pcGCTimer->getTimerIncreaseValue());
			m_pcGCTimer->setCurrentTime(m_pcGCTimer->getCurrentTime() + m_pcGCTimer->getTimerIncreaseValue());
		}
		}
		);

	GetCollisionManager ().AddCollisionHandler
	(
		[this]
	(CGCBasicEnemies& rcEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{

			RequestReset ();
			m_pcGCTimer->ResetTimer ();
			CGCObjectManager::ObjectKill (&rcEnemies);
			CCLOG ("Player Died.");
			//CGCObjectManager::ObjectKill (&rcInvader);
		}
	);

	

	GetCollisionManager ().AddCollisionHandler
	(
		[this]
	(CGCMovingEnemies& rcMEnemies, CGCObjPlayer& rcPlayer, const b2Contact& rcContact) -> void
		{
			if (rcMEnemies.getJustCollided() == false)
			{
				rcMEnemies.setJustCollided (true);
				RequestReset ();
				m_pcGCTimer->ResetTimer ();
				//CGCObjectManager::ObjectKill (&rcMEnemies);
				CCLOG ("Player wacked.");
				CGCObjectManager::ObjectKill (&rcPlayer);
			}
		}
	);


}// void CGCGameLayerPlatformer::VOnCreate() { ...


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
	//m_pcGCMovingEnemies->VOnUpdate (fTimeStep);

	//m_pcGCOKeys->VOnUpdate(fTimeStep);
	
	//m_pcGCBasicEnemies->SetVelocity (cocos2d::Vec2(1,0));
	//m_pcGCBasicEnemies->SetVelocity (cocos2d::Vec2 (10, 0));
	
	if( ResetWasRequested() )
	{
		VOnReset();
		m_keysCollected = 0;
		ResetRequestWasHandled();
	}

	if(m_pcGCTimer->getCurrentTime() <= 0)
	{
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

	delete m_pcGCBasicEnemies;
	m_pcGCBasicEnemies = nullptr;

	delete m_pcGCBasicEnemies2;
	m_pcGCBasicEnemies2 = nullptr;

	delete m_pcGCSprBackGround;
	m_pcGCSprBackGround = nullptr;

	/*delete m_pcGCsprTimerBar;
	m_pcGCsprTimerBar = nullptr;*/
	
	delete m_pcGCODoor;
	m_pcGCODoor = nullptr;

	///////////////////////////////////////////////////////////////////////////
	// N.B. because object groups must register manually, 
	// we also unregister them manually
	///////////////////////////////////////////////////////////////////////////
	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupPlatform );
	delete m_pcGCGroupPlatform;
	m_pcGCGroupPlatform = nullptr;

	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupProjectilePlayer );
	delete m_pcGCGroupProjectilePlayer;
	m_pcGCGroupProjectilePlayer = nullptr;

	//CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupInvader );
	//delete m_pcGCGroupInvader;
	//m_pcGCGroupInvader = nullptr;

	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupItem );
	delete m_pcGCGroupItem;
	m_pcGCGroupItem = nullptr;

	IGCGameLayer::VOnDestroy();
}


///////////////////////////////////////////////////////////////////////////////
// on quit button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnQuitButton( Ref* pSender )
{
	ReplaceScene( TransitionRotoZoom::create( 1.0f, CMenuLayer::scene() ) );
}



///////////////////////////////////////////////////////////////////////////////
// on reset button
///////////////////////////////////////////////////////////////////////////////
void CGCGameLayerPlatformer::Callback_OnResetButton(Ref* pSender)
{
	m_pcGCTimer->ResetTimer();
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

