////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GCGameLayerSpaceInvaders.h"
#include <algorithm>
#include <stdlib.h> 


#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GCCocosInterface/GCObjTileLayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "MenuScene.h"
#ifndef _APP_DELEGATE_H_
	#include "AppDelegate.h"
#endif

USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
CGCGameLayerSpaceInvaders::CGCGameLayerSpaceInvaders( void )
: IGCGameLayer					( GetGCTypeIDOf( CGCGameLayerSpaceInvaders ) ) 
, m_pcGCGroupInvader			( NULL )
, m_pcGCGroupProjectilePlayer	( NULL )
, m_pcGCSprBackGround			( NULL )
, m_pcGCOPlayer					( NULL )
, m_uNumCollisionsInCache		( 0 ) 
{
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
CGCGameLayerSpaceInvaders::~CGCGameLayerSpaceInvaders( void )
{
}


//////////////////////////////////////////////////////////////////////////
// on "init" you need to initialize your instance
//////////////////////////////////////////////////////////////////////////
bool CGCGameLayerSpaceInvaders::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !IGCGameLayer::init() )
    {
        return false;
    }

	return true;
}


//////////////////////////////////////////////////////////////////////////
// in order to guarantee the actions this layer expects we need to 
// initialise the keyboard action map every time onEnter is called - this
// fixes the case where an IGCGameLayer with a different mapping was
// pushed over this one on Director's scene stack
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::onEnter()
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
// 
//////////////////////////////////////////////////////////////////////////
//virtual
void CGCGameLayerSpaceInvaders::VOnCreate( void )
{ 
	//////////////////////////////////////////////////////////////////////////
	// creates the default object group
	IGCGameLayer::VOnCreate();

	//////////////////////////////////////////////////////////////////////////
	// cache some useful values 
    Size visibleSize	= Director::getInstance()->getVisibleSize();
    Vec2 origin			= Director::getInstance()->getVisibleOrigin();


	//////////////////////////////////////////////////////////////////////////
	// create and register our group for the invaders
	// 
	// N.B. can't do this in CGCObjectGroup internally on construction because ObjectGroupRegister calls a virtual 
	// function in the CGCObjectManager interface to check the types of objects that the group handles
	m_pcGCGroupInvader = new CGCObjGroupInvader();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupInvader );

	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer();
	CGCObjectManager::ObjectGroupRegister( m_pcGCGroupProjectilePlayer );


    //////////////////////////////////////////////////////////////////////////
    // Add Menu

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage* pResetItem 
		= MenuItemImage::create(	"Loose/CloseNormal.png",
                                    "Loose/CloseSelected.png",
                                    CC_CALLBACK_1( CGCGameLayerSpaceInvaders::Callback_OnResetButton, this ) );
    
    pResetItem->setPosition(	Vec2(	( ( visibleSize.width - ( pResetItem->getContentSize().width * 0.5f ) ) + origin.x ), 
										( ( ( pResetItem->getContentSize().height * 0.5f ) + origin.y ) ) ) );
 
    MenuItemImage* pQuitItem 
		= MenuItemImage::create(	"Loose/CloseNormal.png",
                                    "Loose/CloseSelected.png",
                                    CC_CALLBACK_1( CGCGameLayerSpaceInvaders::Callback_OnQuitButton, this ) );
    
    pQuitItem->setPosition(		Vec2(	( ( visibleSize.width - ( pQuitItem->getContentSize().width * 0.5f ) ) + origin.x ), 
										( ( visibleSize.height - ( pQuitItem->getContentSize().height * 0.5f ) ) + origin.y ) ) );

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create( pResetItem, pQuitItem, NULL );
    pMenu->setPosition( Vec2::ZERO );
    this->addChild( pMenu, 1 );


    //////////////////////////////////////////////////////////////////////////
    // Add label

    // create and initialize a label
    Label* pLabel = Label::createWithTTF( "Game - Top button to Quit, bottom button to Reset", "fonts/arial.ttf", 24 );

    // position the label on the center of the screen
    pLabel->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height - 50 + origin.y ) );

    // add the label as a child to this layer
    this->addChild( pLabel, 1 );

    // add "CGCGameLayerSpaceInvaders" splash screen"
	const char* pszPlist_background = "TexturePacker/Backgrounds/Placeholder/background.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite();
		m_pcGCSprBackGround->CreateSprite( pszPlist_background );
		m_pcGCSprBackGround->SetResetPosition( b2Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ) );
		m_pcGCSprBackGround->SetParent( IGCGameLayer::ActiveInstance() );
 	}


	//////////////////////////////////////////////////////////////////////////
	// add player 
	m_pcGCOPlayer = new CGCObjPlayer(); 

	// set mario's position from data in the TMX
	b2Vec2 v2MarioStartPos( 64.0f, 160.0f ); 
	m_pcGCOPlayer->SetResetPosition( v2MarioStartPos );

	// init invader group's formation from mario's position too
	m_pcGCGroupInvader->SetFormationOrigin( v2MarioStartPos );
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCGameLayerSpaceInvaders::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );
	HandleCollisions();	
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
// virtual
void CGCGameLayerSpaceInvaders::VOnDestroy( void )
{
	// clean up anything we allocated in opposite order to creation
	delete m_pcGCOPlayer;
	m_pcGCOPlayer = NULL;

	m_pcGCSprBackGround->DestroySprite();
	delete m_pcGCSprBackGround;
	m_pcGCSprBackGround = NULL;

	// N.B. because object groups must register manually, we also unregister them manually
	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupProjectilePlayer );
	delete m_pcGCGroupProjectilePlayer;
	m_pcGCGroupProjectilePlayer = NULL;

	CGCObjectManager::ObjectGroupUnRegister( m_pcGCGroupInvader );
	delete m_pcGCGroupInvader;
	m_pcGCGroupInvader = NULL;

	IGCGameLayer::VOnDestroy();
}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::Callback_OnQuitButton( Ref* pSender )
{
	ReplaceScene( TransitionRotoZoom::create( 1.0f, CMenuLayer::scene() ) );
}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::Callback_OnResetButton(Ref* pSender)
{
	CGCObjectManager::OnReset();
}



//////////////////////////////////////////////////////////////////////////
// resets collision cache - called once per frame before 
// IGCGameLayer VOnUpdate (i.e. before any GC types get updated)
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::FlushCollisions( void )
{
	m_uNumCollisionsInCache = 0;
}



//////////////////////////////////////////////////////////////////////////
// collides one array of CGCObjSprite* against another and stores the 
// detected collisions in m_asCollisionsThisFrame
// N.B. this code assumes that no CGCObjSprite is in both arrays
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::CheckForCollisions( const SCollisionArray* pFirst, const SCollisionArray* pSecond )
{
	// iterate both loops and check each pair of sprites.
	// add any collisions to m_asCollisionCache
	for( u32 uIdxFirst = 0; uIdxFirst < pFirst->uNumInArray; ++uIdxFirst )
	{
		const CGCObjSprite* pGCSprFirst = pFirst->papcArray[ uIdxFirst ];

		for( u32 uIdxSecond = 0; uIdxSecond < pSecond->uNumInArray; ++uIdxSecond )
		{
			const CGCObjSprite* pGCSprSecond = pSecond->papcArray[ uIdxSecond ];

			if( pGCSprFirst->GetBoundingBox().intersectsRect( pGCSprSecond->GetBoundingBox() ) )
			{
				m_asCollisionCache[ m_uNumCollisionsInCache ].pcGCObjSpriteOne = const_cast< CGCObjSprite* >( pGCSprFirst );
				m_asCollisionCache[ m_uNumCollisionsInCache ].pcGCObjSpriteTwo = const_cast< CGCObjSprite* >( pGCSprSecond );
				++m_uNumCollisionsInCache;
			}
		}
	}
}



//////////////////////////////////////////////////////////////////////////
// iterates collision cache for each sCollisionPair it will call 
// pCB_ForEachCollision with pUserData and the sCollisionPair
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::IterateCollisions( void* pUserData, pfnCB_CollisionListIterator pCB_ForEachCollision )
{
	CCAssert( NULL != pCB_ForEachCollision, "pCB_ForEachCollision pased as NULL" );
	for( u32 uLoop = 0; uLoop < m_uNumCollisionsInCache; ++uLoop )
	{
		// stop iterating if the CB returns false
		if( !pCB_ForEachCollision( pUserData, m_asCollisionCache[ uLoop ] ) )
		{
			break;
		}
	}
}



//////////////////////////////////////////////////////////////////////////
// done after VOnUpdate	to handle collisions based on this frame's update
//////////////////////////////////////////////////////////////////////////
void CGCGameLayerSpaceInvaders::HandleCollisions( void )
{
	struct SFixedArrayOfSprites
	{
		std::uint32_t	uCount;
		CGCObjSprite*	apSprites[ std::max( CGCObjGroupInvader::k_uNumProjectiles, CGCObjGroupProjectilePlayer::k_uNumInvaders ) ];
	};

	//////////////////////////////////////////////////////////////////////
	// collide the player against the invaders

		// N.B. this is relatively 'C' style code, lots of ugly casting.
		// N.N.B. the downside to 'C++ifying' it would be an explosion of classes

		// find the player
		CGCObject*		pcPlayerAsGCObj		= CGCObjectManager::FindObject( NULL, GetGCTypeIDOf( CGCObjPlayer ) );
		CGCObjSprite* 	pcPlayerAsGCSprite	= static_cast< CGCObjSprite* >( pcPlayerAsGCObj );

		// get an array of all live invaders (as gcobjsprites)
		SFixedArrayOfSprites sArray_Invaders = { 0, { 0 } };

		// C++11 style visitor pattern using lambda. AWESOME! 
		m_pcGCGroupInvader->ForEachObjectIn_LiveList( [&]( CGCObject* pObject )
		{
			sArray_Invaders.apSprites[ sArray_Invaders.uCount++ ] = static_cast< CGCObjSprite* >( pObject );
			return true;
		} );

		// N.B. we pass pcPlayerAsGCSprite as an 'array of 1'  
		SCollisionArray sPlayer;
		sPlayer.papcArray	= &pcPlayerAsGCSprite;
		sPlayer.uNumInArray	= 1;

		// this one we can use 'as is'
		SCollisionArray sInvaders;
		sInvaders.papcArray		= &sArray_Invaders.apSprites[ 0 ];
		sInvaders.uNumInArray	= sArray_Invaders.uCount;

		// flush previous collisions
		FlushCollisions();

		// check for then iterate collisions
		CheckForCollisions( &sPlayer, &sInvaders ); 

		// iterate killing invaders that collide with the player
        IterateCollisions( reinterpret_cast< void* >( this ), CB_CollIter_HandleLogic_PlayerVsInvader );
	// collide the player against the invaders
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// player projectiles against the invaders
		// get an array of all live invaders (as gcobjsprites)
		SFixedArrayOfSprites sArray_Projectiles = { 0, { 0 } };
	
		// C++11 style visitor pattern using lambda. AWESOME! 
		m_pcGCGroupProjectilePlayer->ForEachObjectIn_LiveList( [&]( CGCObject* pObject )
		{
			sArray_Projectiles.apSprites[ sArray_Projectiles.uCount++ ] = static_cast< CGCObjSprite* >( pObject );
			return true;
		} );

		// this one we can use 'as is'
		SCollisionArray sProjectiles;
		sProjectiles.papcArray		= &sArray_Projectiles.apSprites[ 0 ];
		sProjectiles.uNumInArray	= sArray_Projectiles.uCount;

		// flush previous collisions
		FlushCollisions();

		// check for then iterate collisions
		CheckForCollisions( &sProjectiles, &sInvaders ); 

		// iterate killing invaders that collide with the player
		IterateCollisions( NULL, CB_CollIter_HandleLogic_ProjectileVsInvader );
	// player projectiles against the invaders
	//////////////////////////////////////////////////////////////////////
}



//////////////////////////////////////////////////////////////////////////
// function conforming to the typedef 
// CGCGameLayerSpaceInvaders::pfnCB_CollisionListIterator used by 
// CGCObjGroupPlayerProjectile::VOnUpdate to kill invaders that have 
// collided with the player  
//////////////////////////////////////////////////////////////////////////
// static
bool CGCGameLayerSpaceInvaders::CB_CollIter_HandleLogic_PlayerVsInvader
( 
	void*												pGameLayerSpaceInvadersInstance, 
	const CGCGameLayerSpaceInvaders::SCollisionPair&	rsCollisionPair 
)
{
    // notify the player of the collision
    // when this function was called on line 363 as follows
    //
    //  IterateCollisions( reinterpret_cast< void* >( this ), CB_CollIter_HandleLogic_PlayerVsInvader );
    //
    // the 'this' pointer of CGCGameLayerSpaceInvaders::HandleCollisions, which is a 
    // CGCGameLayerSpaceInvaders* was passed through as a void*
    // we need to turn it back into a CGCGameLayerSpaceInvaders* to use it.
    //
    // N.B. this is ONLY safe because *we*know* that we passed a valid pointer in!
    CGCGameLayerSpaceInvaders* pThis = reinterpret_cast< CGCGameLayerSpaceInvaders* >( pGameLayerSpaceInvadersInstance );
  
    // now we have told the compiler to treat it as what we know it is we can use it
    pThis->m_pcGCOPlayer->NotifyOfCollisionWithInvader();


	// Note that because of how and WHEN we use this function
	// (see CGCGameLayerSpaceInvaders::HandleCollisions) we know that 
	// the only possible collisions are player vs. invader
	if( GetGCTypeIDOf( CGCObjInvader ) == rsCollisionPair.pcGCObjSpriteOne->GetGCTypeID() )
	{
		CGCObjectManager::ObjectKill( rsCollisionPair.pcGCObjSpriteOne );
	}
	else
	{
		CGCObjectManager::ObjectKill( rsCollisionPair.pcGCObjSpriteTwo );
	}
	return true;
}



//////////////////////////////////////////////////////////////////////////
// function conforming to the typedef 
// CGCGameLayerSpaceInvaders::pfnCB_CollisionListIterator used by 
// CGCObjGroupPlayerProjectile::VOnUpdate to kill invaders and projectiles
// when they collide 
//////////////////////////////////////////////////////////////////////////
// static
bool CGCGameLayerSpaceInvaders::CB_CollIter_HandleLogic_ProjectileVsInvader
	( void* pNotUsed, const CGCGameLayerSpaceInvaders::SCollisionPair&	rsCollisionPair )
{
	// Note that because of how and WHEN we use this function
	// (see CGCGameLayerSpaceInvaders::HandleCollisions) we know that 
	// the only possible collisions are player projectile vs. invader
	CGCObjectManager::ObjectKill( rsCollisionPair.pcGCObjSpriteOne );
	CGCObjectManager::ObjectKill( rsCollisionPair.pcGCObjSpriteTwo );

	return true;
}
