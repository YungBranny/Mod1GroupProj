////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJPLAYER_H_
#define _GCOBJPLAYER_H_

#include "2d/CCLabel.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjGroupProjectilePlayer;
template< typename TActionType > class TGCActionToKeyMap;

// enum of user defined input actions the class
enum EPlayerActions
{
	EPA_AxisMove_X,
	EPA_ButtonJump
};

//////////////////////////////////////////////////////////////////////////
// This is a sample class derived from CGCObject.
// 
// It could be the basis of your player object, it's up to you really.
//
// The player will be the only gameplay object in the default object group
//
//////////////////////////////////////////////////////////////////////////
class CGCObjPlayer 
: public CGCObjSpritePhysics
//, CGCObjSprite
{
private:
	// member variables for 'physicsy' handling
	// N.B. uses sprite to store position and has no rotation
	f32		m_fMaximumMoveForce_Horizontal;
	f32		m_fMaximumMoveForce_Vertical;
	f32		m_fDragCoefficient_Linear;
	f32		m_fDragCoefficient_Square;
	f32		m_fNoInput_ExtraDrag_Square;
	f32		m_fNoInput_VelocityThreshold;

	float	m_fLivesFontSize;
	float	m_iLivesTextOutlineSize;
	float	m_iLivesBarHeightX;
	float	m_iLivesBarHeightY;

	int		m_iNumberOfLives;

	bool	m_bCanJump;
	bool	m_bOnTravelator;

	bool	m_bOnLadder;

	cocos2d::Label* m_pLivesText;

	// action map for controllers
	TGCActionToKeyMap< EPlayerActions >* m_pcControllerActionToKeyMap;

	cocos2d::Vec2			m_v2MovingRightVelocity;			 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_v2MovingLeftVelocity;				 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_v2MovingUpVelocity;				 // Mia: Up Velocity for when Player interacts with a Ladder.
	cocos2d::Vec2			m_v2MovingDownVelocity;				 // Mia: Down Velocity for when Player interacts with a Ladder.
	cocos2d::Vec2			m_v2StopMovingVelocity;				 //The velocitys for how fast the enemy should move
	b2Vec2					m_bv2jumpVel;

public:
	CGCObjPlayer();

	bool getOnTravelator() const { return m_bOnTravelator; }
	void setOnTravelator(bool b) { m_bOnTravelator = b; }

	bool getOnLadder() const { return m_bOnLadder; }
	void setOnLadder(bool i) { m_bOnLadder = i; }

	//////////////////////////////////////////////////////////////////////////
	// declare the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
	GCFACTORY_DECLARE_CREATABLECLASS( CGCObjPlayer );

	//////////////////////////////////////////////////////////////////////////
	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types.
	virtual ~CGCObjPlayer()
	{}


	//////////////////////////////////////////////////////////////////////////
	// overridden virtuals from the game object interface

		// This will be called exactly once for each CGCObject derived class instance 
		// registered with CGCObjectManager as soon as the TGB level file has stopped 
		// loading- it is an "explicit constructor".
		virtual void VOnResourceAcquire( void );

		// OnReset is called for each CGCObject derived class when CGCObjectManager is 
		// reset
		virtual void VOnReset( void ); 

		// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
		// updated in t2dSCeneGraph onProcessTick()
		virtual void VOnUpdate( f32 fTimeStep ); 

        // called immediately before the managing object group releases its own assets
        virtual void VOnResourceRelease( void );

		virtual void VOnResurrected(void);

	// overridden virtuals from the game object interface
	//////////////////////////////////////////////////////////////////////////

	// updates the movement of the CCSprite
	void UpdateMovement( f32 fTimeStep );

    // this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
    void NotifyOfCollisionWithInvader();

	bool GetCanJump() { return m_bCanJump; }

	void SetCanJump(bool i) { m_bCanJump = i; }

	int GetNumberOfLives() { return m_iNumberOfLives; }

	void DecrementLives();

	void ResetLives();

	void UpdateLives();

	cocos2d::Label* getLivesText() const { return m_pLivesText; }

	void setLivesText(cocos2d::Label* t) { m_pLivesText = t; }
};
#endif // #ifndef _GCOBJPLAYER_H_
