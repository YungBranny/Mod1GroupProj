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
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCMovingEnemies.h"

#include "AppDelegate.h"


USING_NS_CC;


///////////////////////////////////////////////////////////////////////////
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
, m_pcGCOPlayer					( nullptr )
, m_bResetWasRequested			( false )
, m_bQuitWasRequested			( false )
{
}


//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
CGCGameLayerPlatformer::~CGCGameLayerPlatformer()
{
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
	m_pcGCGroupInvader = new CGCObjGroupInvader();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupInvader );

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


    ///////////////////////////////////////////////////////////////////////////
    // add label
	///////////////////////////////////////////////////////////////////////////

 	// create and initialize a label
    Label* pLabel = Label::createWithTTF( "Game - Top button to Quit, bottom button to Reset", "fonts/arial.ttf", 24);

    // position the label on the center of the screen
    pLabel->setPosition( Vec2( visibleSize.width/2, visibleSize.height - 50 ) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "CGCGameLayerPlatformer" splash screen"
	const char* pszPlist_background = "TexturePacker/Backgrounds/Placeholder/background.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite();
		m_pcGCSprBackGround->CreateSprite( pszPlist_background );
		m_pcGCSprBackGround->SetResetPosition( Vec2( visibleSize.width/2, visibleSize.height/2 ) );
		m_pcGCSprBackGround->SetParent( IGCGameLayer::ActiveInstance() );
 	}


	///////////////////////////////////////////////////////////////////////////
	// set up physics 
	///////////////////////////////////////////////////////////////////////////

	// set "self" as contact listener
	B2dGetWorld()->SetContactListener( this ); 

	// load the physics shapes from the plist created with PhysicsEditor
	B2dLoadShapesFromPlist( "PhysicsEditor/GameShapes.plist" );	

	///////////////////////////////////////////////////////////////////////////
	// stop mario from leaving the screen
	///////////////////////////////////////////////////////////////////////////

	// get window size
	//Size s = Director::getInstance()->getWinSize();

	// PTM_RATIO
	f32 PTM_RATIO = IGCGAMELAYER_B2D_PIXELS_PER_METER;
	
	b2Vec2	b2v2ScreenCentre_Pixels( ( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ) );
	Vec2	v2ScreenCentre_Pixels( ( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ) );



	// define the ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position	=	IGCGameLayer::B2dPixelsToWorld( b2v2ScreenCentre_Pixels );
	groundBodyDef.type		=	b2_kinematicBody;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = B2dGetWorld()->CreateBody( &groundBodyDef );

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// bottom
	groundBox.SetAsBox( ( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.5f, b2Vec2( 0.0f, - ( ( visibleSize.height * 0.5f ) / PTM_RATIO ) ), 0.0f );
	groundBody->CreateFixture(&groundBox, 0);

	// top
	groundBox.SetAsBox( ( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.5f, b2Vec2( 0.0f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO ) ), 0.0f );
	groundBody->CreateFixture( &groundBox, 0 );

	// left
	groundBox.SetAsBox( 0.5f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO ), b2Vec2( -( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.0f ), 0.0f );
	groundBody->CreateFixture( &groundBox, 0 );

	// right
	groundBox.SetAsBox( 0.5f, ( ( visibleSize.height * 0.5f ) / PTM_RATIO ), b2Vec2( ( ( visibleSize.width * 0.5f ) / PTM_RATIO ), 0.0f ), 0.0f );
	groundBody->CreateFixture( &groundBox, 0 );


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
	m_cLevelLoader.LoadLevelFile( FileUtils::getInstance()->fullPathForFilename( std::string( "OgmoEditor/GCOgmoTemplateLevel.oel" ) ).c_str() );
	m_cLevelLoader.CreateObjects( CGCFactory_ObjSpritePhysics::GetFactory() );

	// note: we have now created all the items, platforms, & invaders specified in the level file


	///////////////////////////////////////////////////////////////////////////
	// add player - this shows manual use of class factory
	///////////////////////////////////////////////////////////////////////////

	// starting position
	cocos2d::Vec2 v2MarioStartPos(	( origin.x + ( visibleSize.width * 0.5f) ),
									( origin.y + ( visibleSize.height * 0.5f ) ) );

	// factory creation parameters
	// N.B. note m_sPlayerCreateParams is a member variable of this class which will stay in scope whilst mario is in scope
	CGCFactoryCreationParams& sParams	= m_sPlayerCreateParams;
	sParams.strClassName				= "CGCObjPlayer";
	sParams.strPlistFile				= "TexturePacker/Sprites/Willy/Willy.plist";
	sParams.strPhysicsShape				= "Willy";
	sParams.eB2dBody_BodyType			= b2_dynamicBody;
	sParams.bB2dBody_FixedRotation		= true;

	// create player object
	m_pcGCOPlayer = static_cast< CGCObjPlayer* >( CGCFactory_ObjSpritePhysics::GetFactory().CreateInstance( sParams, v2MarioStartPos ) );

	
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

	GetCollisionManager().AddCollisionHandler( [] ( CGCObjPlayer& rcPlayer, CGCObjItem& rcItem, const b2Contact& rcContact ) -> void
	{
		COLLISIONTESTLOG( "(lambda) the player hit an item!" );
	} );
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

	if( ResetWasRequested() )
	{
		VOnReset();
		ResetRequestWasHandled();
	}

	if( QuitWasRequested() )
	{
		QuitRequestWasHandled();
		ReplaceScene( TransitionRotoZoom::create( 1.0f, CMenuLayer::scene() ) );
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

	delete m_pcGCSprBackGround;
	m_pcGCSprBackGround = nullptr;

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

	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupInvader );
	delete m_pcGCGroupInvader;
	m_pcGCGroupInvader = nullptr;

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
	RequestQuit();
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
		bool				bNameMatches	= ( 0 == pstrCheckMe->compare( "bottom_left" ) );
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

