/////////////////////////////////////////////////////////////////// /////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCLEVEL2_H_
#define _GCLEVEL2_H_

#include "Classes/GamerCamp/GCCocosInterface/IGCGameLayer.h"

#ifndef _GCLEVELLOADER_OGMO_H_
#include "Classes/GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif

#include "SimpleAudioEngine.h"

//////////////////////////////////////////////////////////////////////////
// fwd decl
//class CGCGameLayerPlatformer;
class CGCObjSprite;
class CGCObjPlayer;
class CGCObjPlatform;
class CGCObjGroupPlatform;
class CGCObjItem;
class CGCObjGroupItem;
class CGCObjInvader;
class CGCObjGroupInvader;
class CGCObjGroupProjectilePlayer;
class CGCObjGroupProjectilePlayer;
class CGCObjTimer;
class CGCObjKeys;
class CGCBasicEnemies;
class CGCMovingEnemies;
class CGCMovingEnemy2;
class CGCMovingEnemyLRSlow;
class CGCMovingEnemyLRFast;
class CGCMovingEnemyUpDown;
class CGCMovingEnemyUpDownSlow;
class CGCMovingEnemyUpDownFast;
class CGCHazardChild;
class CGCObjTravelatorPlatform;
class CGCObjExitDoor;
class CGCObjTimePickUp;
class CGCObjScalingBasicPlatformManager;
class CGCObjScalingFallingPlatformManager;
class CGCObjScalingBasicPlatform;
class CGCObjScalingFallingPlatform;
class CGCObjMovingPlatform;
class GCObjBrickPlatform;
class CGCObjLadder;
class CGCObjKeys;
class GCObjEnemyMovementCollider;
class GCObjEnemyMovementCollider2;
class CGCObjLives;
class CGCObjScore;
class CGCGameLayerPlatformer;
class GCLevel3;

//////////////////////////////////////////////////////////////////////////
// sample class that creates a 'game' by deriving from IGCGameLayer
//////////////////////////////////////////////////////////////////////////
class GCLevel2
	: public IGCGameLayer
	, public b2ContactListener
{
private:
	// object groups
	CGCObjGroupPlatform* m_pcGCGroupPlatform;
	CGCObjGroupItem* m_pcGCGroupItem;
	CGCObjGroupInvader* m_pcGCGroupInvader;
	CGCObjGroupProjectilePlayer* m_pcGCGroupProjectilePlayer;

	CGCObjKeys* m_pcGCOKeys;
	CGCObjKeys* m_pcGCOKeys1;
	CGCObjKeys* m_pcGCOKeys2;

	//UI
	CGCObjTimer* m_pcGCTimer;

	//score
	CGCObjScore* m_pcGCOScore;

	// backgrounds
	CGCObjSprite* m_pcGCSprBackGround;

	// mario
	CGCObjPlayer* m_pcGCOPlayer;
	CGCFactoryCreationParams	m_sPlayerCreateParams;

	// level loader
	CGCLevelLoader_Ogmo		m_cLevelLoader;

	bool					m_bCheckIfPlayerIsAbovePlatform;

	int						m_iKeysCollected;

	int						m_iTotalKeys;

	int						m_iTimerPickedUp;

	CocosDenshion::SimpleAudioEngine* m_pcGCBackgroundAudio;
	CocosDenshion::SimpleAudioEngine* m_pcGCSoundEffectsAudio;

public:
	GCLevel2 (void);
	~GCLevel2 (void);

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
	void Callback_OnQuitButton (Ref* pSender);
	void Callback_OnResetButton (Ref* pSender);
	void Callback_OnSkipButton (Ref* pSender);
	// called from VOnUpdate
	void HandleCollisions (void);

	void keyCollected ();

	void addOnTime ();

	void playBackgroundMusic ();

	void playKeyAudio ();

	void playTimerPickUpAudio ();

	void playDoorOpeningAudio ();


	//////////////////////////////////////////////////////////////////////////
	// CCNode interface...
	virtual void onEnter ();
	// CCNode interface...
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface

	virtual	void VOnCreate (void);
	virtual void VOnUpdate (f32 fTimeStep);
	virtual	void VOnDestroy (void);

	// IGCGameLayer interface
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

	virtual void BeginContact (b2Contact* pB2Contact);
	virtual void EndContact (b2Contact* pB2Contact);
	virtual void PreSolve (b2Contact* pB2Contact, const b2Manifold* pOldManifold);
	virtual void PostSolve (b2Contact* pB2Contact, const b2ContactImpulse* pImpulse);

	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////// 
	// reset / quit handling
private:
	bool							m_bResetWasRequested;
	bool							m_bQuitWasRequested;
	bool							m_bSkipWasRequested;

	void RequestReset ()
	{
		m_bResetWasRequested = true;
	}

	void ResetRequestWasHandled ()
	{
		m_bResetWasRequested = false;
	}

	bool ResetWasRequested ()
	{
		return m_bResetWasRequested;
	}

	void RequestQuit ()
	{
		m_bQuitWasRequested = true;
	}

	void QuitRequestWasHandled ()
	{
		m_bQuitWasRequested = false;
	}

	bool QuitWasRequested ()
	{
		return m_bQuitWasRequested;
	}
	void RequestSkip ()
	{
		m_bSkipWasRequested = true;
	}

	void SkipRequestWasHandled ()
	{
		m_bSkipWasRequested = false;
	}

	bool SkipWasRequested ()
	{
		return m_bSkipWasRequested;
	}
};
//
#endif // __CGCGameLayerPlatformer_SCENE_H__
