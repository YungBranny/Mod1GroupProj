/////////////////////////////////////////////////////////////////// /////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMELAYERSPACEINVADERS_H_
#define _GAMELAYERSPACEINVADERS_H_

#include "../GCCocosInterface/IGCGameLayer.h"

#include "AudioEngine.h"

//////////////////////////////////////////////////////////////////////////
// fwd decl
class CGCObjSprite;
class CGCObjPlayer;
class CGCObjPlatform;
class CGCObjGroupPlatform;
class CGCObjItem;
class CGCObjGroupItem;
class CGCObjInvader;
class CGCObjGroupInvader;
class CGCObjGroupProjectilePlayer;
class CGCObjTimer;
//class CGCObjTimerBar;
class CGCObjKeys;
class CGCBasicEnemies;
class CGCMovingEnemies;
class CGCObjLongPlatformTest;
class CGCObjShortPlatformTest;
class CGCObjTravelatorPlatform;
class CGCObjFallingPlatform;
class CGCObjDoor;
class CGCObjTimePickUp;
class CGCObjScalingBasicPlatformManager;
class CGCObjScalingFallingPlatformManager;
class CGCObjMovingPlatform;


enum class ECGameStates
{
	EState_Playing = 0,
	EState_Menu,
	EState_GameWon,
	EState_GameLost,
	
};



//////////////////////////////////////////////////////////////////////////
// sample class that creates a 'game' by deriving from IGCGameLayer
//////////////////////////////////////////////////////////////////////////
class CGCGameLayerPlatformer 
: public IGCGameLayer
, public b2ContactListener 
{
private:
	// object groups
	CGCObjGroupPlatform*			m_pcGCGroupPlatform;
	CGCObjGroupItem*				m_pcGCGroupItem;
	CGCObjGroupInvader*				m_pcGCGroupInvader;
	CGCObjGroupProjectilePlayer*	m_pcGCGroupProjectilePlayer;

	
	CGCObjTimer*					m_pcGCTimer;
	//CGCObjTimerBar*					m_pcGCTimerBar;

	CGCObjKeys*                     m_pcGCOKeys;
	CGCObjKeys*                     m_pcGCOKeys1;
	CGCObjKeys*                     m_pcGCOKeys2;

	CGCObjTimePickUp*               m_pcGCOTimePickUp;

	CGCObjDoor*                     m_pcGCODoor;

	CGCBasicEnemies*				m_pcGCBasicEnemies;
	CGCBasicEnemies*				m_pcGCBasicEnemies2;
	CGCMovingEnemies*				m_pcGCMovingEnemies;

	//platforms
	CGCObjLongPlatformTest*			m_pcGCLongPlatformTest1;
	CGCObjLongPlatformTest*			m_pcGCLongPlatformTest2;
	CGCObjLongPlatformTest*			m_pcGCLongPlatformTest3;
	CGCObjLongPlatformTest*			m_pcGCLongPlatformTest4;
	CGCObjLongPlatformTest*			m_pcGCLongPlatformTest5;

	CGCObjShortPlatformTest*		m_pcGCShortPlatformTest1;
	CGCObjShortPlatformTest*		m_pcGCShortPlatformTest2;
	CGCObjShortPlatformTest*		m_pcGCShortPlatformTest3;
	CGCObjShortPlatformTest*		m_pcGCShortPlatformTest4;
	CGCObjShortPlatformTest*		m_pcGCShortPlatformTest5;

	CGCObjMovingPlatform*           m_pcGCOMovingPlatform;

	CGCObjFallingPlatform*			m_pcGCFallingPlatform1;

	CGCObjTravelatorPlatform*		m_pcGCTravelatorPlatform1;

	CGCObjScalingBasicPlatformManager*	m_pcGCScalingBasicPlatformManager;
	CGCObjScalingFallingPlatformManager* m_pcGCScalingFallingPlatformManager;

	CGCObjScalingBasicPlatformManager*	m_pcGCScalingBasicPlatformManagerMiddle;

	CGCObjScalingBasicPlatformManager*	m_pcGCScalingBasicPlatformManagerTop;

	CGCObjScalingBasicPlatformManager* m_pcGCScalingBasicPlatformManager1;
	CGCObjScalingFallingPlatformManager* m_pcGCScalingFallingPlatformManager1;
	CGCObjScalingBasicPlatformManager* m_pcGCScalingBasicPlatformManager2;
	CGCObjScalingFallingPlatformManager* m_pcGCScalingFallingPlatformManager2;


	// backgrounds
	CGCObjSprite*					m_pcGCSprBackGround;
	//CGCObjSprite*					m_pcGCsprTimerBar;

	//test audio
	cocos2d::experimental::AudioEngine*		m_pcGCBackgroundAudio;

	// mario
	CGCObjPlayer*					m_pcGCOPlayer;

	int m_iKeysCollected;

	int m_iTotalKeys;

	int m_iTimerPickedUp;

	bool m_bPlayerHitHostile;

	bool m_bPlayerKeysGathered;

public:

	ECGameStates mState;

	
	CGCGameLayerPlatformer	( void );
	~CGCGameLayerPlatformer	( void );

	void keyCollected();

	void addOnTime();

	void replaceSceneWin();

	void replaceSceneLose();

	void replaceSceneMenu();

	void backgroundMusic();

	//
	//////////////////////////////////////////////////////////////////////////
	// player actions 
	enum EPlayerActions
	{
		EPA_Up = 0,
		EPA_Down,
		EPA_Left,
		EPA_Right,
		EPA_Fire
	};
	// player actions 
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
    // 'selector' callbacks for menu buttons
    void Callback_OnQuitButton	( Ref* pSender );
    void Callback_OnResetButton	( Ref* pSender );

	// called from VOnUpdate
	void ManuallyHandleCollisions( void );

	//////////////////////////////////////////////////////////////////////////
	// CCNode interface...
	virtual void onEnter();
	// CCNode interface...
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface

		virtual	void VOnCreate	( void );
		virtual void VOnUpdate	( f32 fTimeStep );
		virtual	void VOnDestroy ( void );	

	// IGCGameLayer interface
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

		virtual void BeginContact	( b2Contact* pB2Contact );
		virtual void EndContact		( b2Contact* pB2Contact );
		virtual void PreSolve		( b2Contact* pB2Contact, const b2Manifold* pOldManifold );
		virtual void PostSolve		( b2Contact* pB2Contact, const b2ContactImpulse* pImpulse );

	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are
	//////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////// 
	// reset handling
private:
	bool							m_bResetWasRequested;

	void RequestReset()
	{
		m_bResetWasRequested = true; 
	}

	void ResetRequestWasHandled()
	{
		m_bResetWasRequested = false; 
	}

	bool ResetWasRequested()
	{
		return m_bResetWasRequested; 
	}
};

#endif // __CGCGameLayerPlatformer_SCENE_H__
