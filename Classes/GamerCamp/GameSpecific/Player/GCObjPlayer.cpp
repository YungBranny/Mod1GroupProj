////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>

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



//////////////////////////////////////////////////////////////////////////
// implement the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
GCFACTORY_IMPLEMENT_CREATEABLECLASS( CGCObjPlayer );


//////////////////////////////////////////////////////////////////////////
// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
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
	, m_bOnLadder (false)
	, m_fStartPositionY (0)
	, m_fEndPositionY (0)
	, m_fDropDistance (0)
	, m_fMaximumDropDistance (20.0f)
	, m_fJumpHeight (12.0f)
	, m_bPlayerDiedFromFalling (false)
	, m_fLivesStartPositionX (1700)
	, m_fLivesStartPositionY (1015)
	, m_fLivesSpacingX (10.0f)
	, m_bIsPlayerOnPlatform (true)
	, m_fTravelatorVelocity (-20.0f)
	//, m_bv2CurrentPos(0,0)
	, m_bChangeAnimation (false)
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

	//m_pLivesUI = Sprite::create("Lives/ui_life_full.png");

	//m_pLivesUI->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));

	//m_pLivesUI->setParent(IGCGameLayer::ActiveInstance());

	//const char* pszLivesSprite = "Lives/ui_life_full.plist";
	//{
	//	CreateSprite(pszLivesSprite);
	//	SetResetPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));
	//	SetParent(IGCGameLayer::ActiveInstance());
	//	//SetScale(m_fScaleX, m_fScaleY);
	//}

	m_sprPlayerLoseLives1 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives2 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	m_sprPlayerLoseLives3 = Sprite::create("TexturePacker/Sprites/Lives/empty_heart.png");
	
	
	

	
	
	m_sprPlayerLives1	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");
	m_sprPlayerLives2	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");
	m_sprPlayerLives3	= Sprite::create(  "TexturePacker/Sprites/Lives/life_full.png");
	
	getPlayerLivesUI1()->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));
	getPlayerLivesUI2()->setPosition(Vec2(m_fLivesStartPositionX + 50, m_fLivesStartPositionY));
	getPlayerLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 100, m_fLivesStartPositionY));

}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlayer::VOnResourceAcquire()
{
	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszPlist_Willy = "TexturePacker/Sprites/Willy/Willy.plist";
	const char* pszAnim_WillyRun = "Run";
	const char* pszAnim_WillyIdle = "Idle";

	// animate!
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);

	if( m_bChangeAnimation == true )
	{
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_WillyIdle)));
	}

	else if( m_bChangeAnimation == false )
	{
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_WillyRun)));
	}

	// because we're just storing a vanilla pointer we must call delete on it in VOnResourceRelease or leak memory 
	// 
	// n.b. m_pcControllerActionToKeyMap is a "perfect use case" for std::unique_ptr...
	// 
	// n.n.b. ... however if we did use std::unique_ptr we'd need to use std::unique_ptr::reset in VOnResourceRelease if we wanted the memory allocate / free behaviour to be the same...
	m_pcControllerActionToKeyMap = TCreateActionToKeyMap( s_aePlayerActions, s_aeKeys );

}



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlayer::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();

	// reset velocity and flip state
	SetFlippedX( false );
	SetFlippedY( false );
	m_bOnTravelator = false;
	m_bIsPlayerOnPlatform = true;

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



//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjPlayer::VOnUpdate( f32 fTimeStep )
{
	// handle movement
	UpdateMovement(fTimeStep);

	
}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//virtual
void CGCObjPlayer::VOnResourceRelease()
{
    CGCObjSpritePhysics::VOnResourceRelease();
	delete m_pcControllerActionToKeyMap;
	m_pcControllerActionToKeyMap = nullptr;
}

void CGCObjPlayer::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();
	GetPhysicsBody ()->SetGravityScale (10.0f);
	m_bv2jumpVel = b2Vec2(GetPhysicsBody()->GetLinearVelocity().x, m_fJumpHeight);
}


//////////////////////////////////////////////////////////////////////////
// updates the movement of the CCSprite owned by this instance
//
// N.B. globals that we can edit in the debugger used to override the 
// values of the members for debugging control code
f32 g_CGCObjPlayer_fMass						= 1.0f;		// kg
f32	g_CGCObjPlayer_fMaximumMoveForce_Horizontal	= 20.0f;	// newton
f32	g_CGCObjPlayer_fMaximumMoveForce_Vertical	= 40.0f;	// newton
f32	g_CGCObjPlayer_fDragCoefficient_Linear		= 0.25f;	// unitless
f32	g_CGCObjPlayer_fDragCoefficient_Square		= 0.2f;		// unitless
f32 g_CGCObjPlayer_m_fNoInput_ExtraDrag_Square	= 0.2f;		// unitless
f32 g_CGCObjPlayer_fNoInput_VelocityThreshold	= 0.25f;	// m/s
f32 g_GCGameLayer_fPixelsPerMetre				= 20.0f;	// pixels / metre
f32 g_GCGameLayer_fDamping						= 0.999f;	// unitless
//
//////////////////////////////////////////////////////////////////////////
void CGCObjPlayer::UpdateMovement(f32 fTimeStep)
{
	if (GetVelocity ().y > 0 || GetVelocity ().y < 0)
	{
		m_bCanJump = false;
	}
	////////////////////////////////////////////////////////////////////////////////
	///// VARIABLES NOT USED
	////////////////////////////////////////////////////////////////////////////////
		//m_fMaximumMoveForce_Horizontal	= g_CGCObjPlayer_fMaximumMoveForce_Horizontal;
		//m_fMaximumMoveForce_Vertical	= g_CGCObjPlayer_fMaximumMoveForce_Vertical;
		//m_fDragCoefficient_Linear		= g_CGCObjPlayer_fDragCoefficient_Linear;
		//m_fDragCoefficient_Square		= g_CGCObjPlayer_fDragCoefficient_Square;
		//m_fNoInput_ExtraDrag_Square		= g_CGCObjPlayer_m_fNoInput_ExtraDrag_Square;
		//m_fNoInput_VelocityThreshold	= g_CGCObjPlayer_fNoInput_VelocityThreshold;

		// we accumulate total force over the frame and apply it at the end
		//Vec2 v2TotalForce( 0.0f, 0.0f);


		// * calculate the control force direction
		//Vec2 v2ControlForceDirection( 0.0f, 0.0f );

		// this float is used to add / remove the effect of various terms 
		// in equations based on whether input has been applied this frame
		//f32 fIsInputInactive = 1.0f;

		// instantiating templates is one of the few use cases where auto is a big improvement & arguably the best thing to do
		// e.g.
		//	auto cController = ... ;
	////////////////////////////////////////////////////////////////////////////////
	///// VARIABLES NOT USED
	////////////////////////////////////////////////////////////////////////////////

	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, ( *m_pcControllerActionToKeyMap ));

	////////////////////////////////////////////////////////////////////////////////
	///// START OLD CODE
	////////////////////////////////////////////////////////////////////////////////
	//	if( cController.IsActive() )
		//{
		//	Vec2 v2LeftStickRaw			= cController.GetCurrentStickValueRaw( EPA_AxisMove_X, EPA_AxisMove_Y );
			//v2ControlForceDirection.x	= v2LeftStickRaw.x;
		//	v2ControlForceDirection.y	= v2LeftStickRaw.y;

			//if( v2ControlForceDirection.length() > 0.0f )
			//{
				//fIsInputInactive = 0.0f;
			//}
		//}
		//else
	//	{
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
	////////////////////////////////////////////////////////////////////////////////
	///// END OLD CODE
	////////////////////////////////////////////////////////////////////////////////

	if (m_bOnTravelator != true)
	{

		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Left))
		{


			if (m_bCanJump == true)
			{

				SetVelocity(cocos2d::Vec2(m_v2MovingLeftVelocity.x, GetVelocity().y));
				SetFlippedX(false);

			}

		}
		else if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Right))
		{


			if (m_bCanJump == true)
			{

				SetVelocity(cocos2d::Vec2(m_v2MovingRightVelocity.x, GetVelocity().y));
				SetFlippedX(true);
			}
		}

		else if( pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Up) ) // Mia: Once Player presses Up
		{
			if( m_bOnLadder == true ) // Mia: If Player is on Ladder
			{
				SetVelocity(cocos2d::Vec2(GetVelocity().x, m_v2MovingUpVelocity.x)); // Mia: The Player is able to move upwards
			}
		}

		else if( pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Down) ) // Mia: Once Player presses Down
		{
			if( m_bOnLadder == true ) // Mia: If Player is on Ladder
			{
				SetVelocity(cocos2d::Vec2(GetVelocity().x, m_v2MovingDownVelocity.x)); // Mia: The Player is able to move downwards
			}
		}

		else
		{

			if (m_bCanJump == true)
			{
				//GetPhysicsBody ()->ApplyForce (b2Vec2 (0, 500), GetPhysicsBody ()->GetWorldCenter (), true);
				SetVelocity(cocos2d::Vec2(0, GetVelocity().y));

			}
			
		}
		  
	}
	else if (m_bOnTravelator == true) 
	{


	}
	////////////////////////////////////////////////////////////////////////////////
	///// Start OLD CODE
	////////////////////////////////////////////////////////////////////////////////
		//}

		// normalise the control vector and multiply by movement force
		//v2ControlForceDirection.x *= m_fMaximumMoveForce_Horizontal;
	//	v2ControlForceDirection.y *= m_fMaximumMoveForce_Vertical;

		// accumulate the force
		//v2TotalForce += v2ControlForceDirection;


		// * calculate drag force
	//	Vec2 v2Velocity_Unit	= GetVelocity();
	//	f32 fVelocity			= v2Velocity_Unit.normalize();

		// This is not the real equation for drag.
		// This is a simple mathematical function that approximates the behaviour 
		// of drag in a very tunable way - it misses out loads of the real factors
		// involved in real aerodynamic drag. I have a feeling I got it from a 
		// game physics textbook, but I can't remember for sure.
		//
		// For the 'proper' drag equation see this: 
		// http://en.wikipedia.org/wiki/Drag_(physics)#Drag_at_high_velocity

		// N.B. the last term evaluates to 0.0f if there is controller input

	//	f32 fDragForce = (		( m_fDragCoefficient_Linear * fVelocity ) 
	//						+	( m_fDragCoefficient_Square * ( fVelocity * fVelocity ) ) 
	//					+	( m_fNoInput_ExtraDrag_Square * ( fVelocity * fVelocity ) * fIsInputInactive ) );

		// drag is applied in the opposite direction to the current velocity of the object
		// so scale out unit version of the object's velocity by -fDragForce
		// N.B. operator* is only defined for (float, Vec2) and not for (Vec2, float) !?!
	//	v2TotalForce += ( -fDragForce * v2Velocity_Unit );


		// physics calcs handled by box 2d based on force applied
		//ApplyForceToCenter( v2TotalForce );
	////////////////////////////////////////////////////////////////////////////////
	///// END OLD CODE
	////////////////////////////////////////////////////////////////////////////////


		// * set sprite flip based on velocity
		// N.B. the else-if looks redundant, but we want the sprite's flip 
		// state to stay the same if its velocity is set to (0.0f, 0.0f)
	if (GetVelocity().y >= 0.0f)
	{
		SetFlippedY(false);
	}
	else if (GetVelocity().y < 0.0f)
	{
		SetFlippedY(false);
	}

	//if( GetVelocity().x > 0.0f || GetVelocity().x < 0.0f)
	//{
	//	m_bChangeAnimation = true;
	//	ChangeAnimation();
	//	SetFlippedX( true );
	//}
	//else if( GetVelocity().x == 0.0f )
	//{
	//	m_bChangeAnimation = false;
	//	ChangeAnimation();
	//	SetFlippedX( false );
	//}

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
		if (GetVelocity ().x > 0)
		{
			SetVelocity (cocos2d::Vec2 (GetVelocity ().x, m_v2MovingDownVelocity.x));
			float impulse = GetPhysicsBody ()->GetMass () * 40;
			GetPhysicsBody ()->ApplyLinearImpulse (b2Vec2 (0, impulse * 1.07f), GetPhysicsBody ()->GetWorldCenter (), true);
		};
		if (GetVelocity ().x < 0)
		{
			SetVelocity (cocos2d::Vec2 (GetVelocity ().x, m_v2MovingDownVelocity.x));
			float impulse = GetPhysicsBody ()->GetMass () * 40;
			GetPhysicsBody ()->ApplyLinearImpulse (b2Vec2 (0, impulse* 1.07f), GetPhysicsBody ()->GetWorldCenter (), true);
		};
		if (GetVelocity ().x == 0 )
		{
			float impulse = GetPhysicsBody ()->GetMass () * 41.5;
			GetPhysicsBody ()->ApplyLinearImpulse (b2Vec2 (0, impulse), GetPhysicsBody ()->GetWorldCenter (), true);
		};
	
		
		
	}

}

//Function to be called when losing a life
void CGCObjPlayer::DecrementLives()
{
	m_iNumberOfLives--;
	//getLivesText()->setString("Lives: " + std::to_string(GetNumberOfLives()));
	LivesUI();
}

//Function to reset lives
void CGCObjPlayer::ResetLives()
{
	m_iNumberOfLives = 3;
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
		
		getPlayerLoseLivesUI1()->setPosition(Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY));
	}
	else if (m_iNumberOfLives == 1)
	{
		getPlayerLivesUI2()->setVisible(false);
	
		getPlayerLoseLivesUI2()->setPosition(Vec2(m_fLivesStartPositionX + 50, m_fLivesStartPositionY));
	}
	else if (m_iNumberOfLives == 2)
	{
		
		getPlayerLivesUI3()->setVisible(false);
		
		getPlayerLoseLivesUI3()->setPosition(Vec2(m_fLivesStartPositionX + 100, m_fLivesStartPositionY));
	}

}

void CGCObjPlayer::ChangeAnimation()
{


}


// Mia: Can use for refactoring once Lives is put into a GroupLives Class
//void CGCObjPlayer::CreateLives()
//{
//	for( i32 iLoop = 0; iLoop < m_iNumberOfLives; ++iLoop )
//	{
//		m_v2LivesStartPosition = cocos2d::Vec2(m_fLivesStartPositionX, m_fLivesStartPositionY);
//		Sprite* m_pLivesUI = new Sprite();
//		m_pLivesUI = Sprite::create("Lives/ui_life_full.png");
//		m_pLivesUI->setPosition(m_v2LivesStartPosition);
//		m_fLivesStartPositionX += m_fLivesSpacingX;
//	}
//}

//////////////////////////////////////////////////////////////////////////
// this function exists purely to better illustrate the EXAMPLE collision 
// detection functionality in CGCGameLayerPlatformer
//////////////////////////////////////////////////////////////////////////
void CGCObjPlayer::NotifyOfCollisionWithInvader()
{
    CCLOG( "CGCObjPlayer::NotifyOfCollisionWithInvader - Aiee! I have collided with an invader!" );
}
