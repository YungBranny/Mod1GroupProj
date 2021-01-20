////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJPLAYER_H_
#define _GCOBJPLAYER_H_

#include "2d/CCLabel.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"


#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

#include "SimpleAudioEngine.h"

class CGCObjGroupProjectilePlayer;
template< typename TActionType > class TGCActionToKeyMap;

// enum of user defined input actions the class
enum EPlayerActions
{
	EPA_AxisMove_X,
	EPA_ButtonJump
};

class CGCObjPlayer 
: public CGCObjSpritePhysics
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

	float	m_fStartPositionY;
	float	m_fEndPositionY;
	float	m_fDropDistance;
	float	m_fMaximumDropDistance;
	float	m_fJumpHeight;

	float   m_fLivesStartPositionX;
	float	m_fLivesStartPositionY;
	float	m_fLivesSpacingX;

	float	m_fTravelatorVelocity;

	int		m_iNumberOfLives;

	int		m_iSwitchesHit;

	bool	m_bCanJump;
	bool	m_bOnTravelator;
	bool	m_bPlayerDiedFromFalling;
	bool	m_bOnLadder;
	bool	m_bChangeAnimation; // If more animations added, will be changed to enum or switch
	bool	m_bLostLife;
	bool    m_bPlayerLivesCheck;
	
	bool	m_bIsPlayerOnPlatform;

	cocos2d::Vec2 m_v2LivesStartPosition;

	cocos2d::Sprite* m_pLivesUI;
	cocos2d::Sprite* m_pLivesUI1;
	cocos2d::Sprite* m_pLivesUI2;

	cocos2d::Sprite* m_sprPlayerLives1;
	cocos2d::Sprite* m_sprPlayerLives2;
	cocos2d::Sprite* m_sprPlayerLives3;

	cocos2d::Sprite* m_sprPlayerLoseLives1;
	cocos2d::Sprite* m_sprPlayerLoseLives2;
	cocos2d::Sprite* m_sprPlayerLoseLives3;
	
	cocos2d::Label* m_pLivesText;

	// action map for controllers
	TGCActionToKeyMap< EPlayerActions >* m_pcControllerActionToKeyMap;

	cocos2d::Vec2			m_v2MovingRightVelocity;			 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_v2MovingLeftVelocity;				 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_v2MovingUpVelocity;				 
	cocos2d::Vec2			m_v2MovingDownVelocity;				 
	cocos2d::Vec2			m_v2StopMovingVelocity;				 //The velocitys for how fast the enemy should move
	b2Vec2					m_bv2jumpVel;

	b2Vec2					m_bv2CurrentPos;

	CocosDenshion::SimpleAudioEngine* m_pcJumpSoundEffectAudio;

public:
	CGCObjPlayer();

	enum class EChangeAnimation
	{
		Idle,
		Run,
		Jump	
	};

	CGCObjScore* m_score;
	
	EChangeAnimation m_eChangeAnimation;

	bool getOnTravelator() const { return m_bOnTravelator; }
	void setOnTravelator(bool b) { m_bOnTravelator = b; }

	bool getPlayerCheckLives() const { return m_bPlayerLivesCheck; }
	void setPlayerCheckLives(bool b) { m_bPlayerLivesCheck = b; }

	bool getIsPlayerOnPlatform () const { return m_bIsPlayerOnPlatform; }
	void setIsPlayerOnPlatform (bool i) { m_bIsPlayerOnPlatform = i; }

	bool getPlayerDiedFromFalling () { return m_bPlayerDiedFromFalling; };
	bool getOnLadder() const { return m_bOnLadder; }
	void setOnLadder(bool i) { m_bOnLadder = i; }

	float getJumpHeight () const { return m_fJumpHeight; }
	void setJumpHeight (float i) { m_fJumpHeight = i; }

	int getSwitchesHit () const { return m_iSwitchesHit; }
	void setSwitchesHit (int f) { m_iSwitchesHit = f; }

	int getPlayerLives() const { return m_iNumberOfLives; }
	void setPlayerLives (int f) { m_iNumberOfLives = f; }

	float getTravelatorVelocity () const { return m_fTravelatorVelocity; }
	void setTravelatorVelocity (int f) { m_fTravelatorVelocity = f; }

	b2Vec2 getCurrentPos () const { return m_bv2CurrentPos; }

	cocos2d::Sprite* getPlayerLivesUI1() const { return m_sprPlayerLives1; }
	void setPlayerLivesUI1(cocos2d::Sprite* t) { m_sprPlayerLives1 = t; }
	
	cocos2d::Sprite* getPlayerLivesUI2() const { return m_sprPlayerLives2; }
	void setPlayerLivesUI2(cocos2d::Sprite* t) { m_sprPlayerLives2 = t; }
	
	cocos2d::Sprite* getPlayerLivesUI3() const { return m_sprPlayerLives3; }
	void setPlayerLivesUI3(cocos2d::Sprite* t) { m_sprPlayerLives3 = t; }

	cocos2d::Sprite* getPlayerLoseLivesUI1() const { return m_sprPlayerLoseLives1; }
	void setPlayerLoseLivesUI1(cocos2d::Sprite* t) { m_sprPlayerLoseLives1 = t; }

	cocos2d::Sprite* getPlayerLoseLivesUI2() const { return m_sprPlayerLoseLives2; }
	void setPlayerLoseLivesUI2(cocos2d::Sprite* t) { m_sprPlayerLoseLives2 = t; }

	cocos2d::Sprite* getPlayerLoseLivesUI3() const { return m_sprPlayerLoseLives3; }
	void setPlayerLoseLivesUI3(cocos2d::Sprite* t) { m_sprPlayerLoseLives3 = t; }

	GCFACTORY_DECLARE_CREATABLECLASS ( CGCObjPlayer );

	virtual ~CGCObjPlayer()
	{}

	virtual void VOnResourceAcquire( void );

	virtual void VOnReset( void ); 
	
	virtual void VOnUpdate( f32 fTimeStep ); 

    virtual void VOnResourceRelease( void );

	virtual void VOnResurrected(void);

	void UpdateMovement( f32 fTimeStep );

	bool GetCanJump() { return m_bCanJump; }

	void SetCanJump(bool i) { m_bCanJump = i; }

	int GetNumberOfLives() { return m_iNumberOfLives; }

	void DecrementLives();

	void PlayerLivesReadFile();
	
	void PlayerLivesWriteFile();
	
	void ResetLives();

	void UpdateLives();

	void FallDamage();

	void CreateLives();

	void LivesUI();

	void ChangeAnimation();

	void playJumpAudio();

	cocos2d::Label* getLivesText() const { return m_pLivesText; }

	void setLivesText(cocos2d::Label* t) { m_pLivesText = t; }
};
#endif // #ifndef _GCOBJPLAYER_H_
