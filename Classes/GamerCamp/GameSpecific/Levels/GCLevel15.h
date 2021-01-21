////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the Header and Class files for Level 15. All of us as a team have contributed to this Class and //
// commented on what we worked on. This Class is for putting the Level together and loading it up.        //
// This Class also contains all the collisions needed for the Level.                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GCLEVEL15_H_
#define _GCLEVEL15_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"

#include "SimpleAudioEngine.h"

class CGCObjSprite;
class CGCObjPlayer;
class CGCObjPlatform;
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
class CGCObjScalingBasicPlatform;
class CGCObjScalingFallingPlatform;
class GCObjBrickPlatform;
class CGCObjLadder;
class CGCObjKeys;
class GCObjEnemyMovementCollider;
class GCObjEnemyMovementCollider2;
class CGCObjLives;
class CGCObjScore;
class CGCObjHighScore;
class GCSwitch;
class CHCOnjSwitchPlatform1;
class CHCOnjSwitchPlatform2;
class CGCObjFallingPlane;
class CGCObjFallingPlane2;
class CGCObjFallingPlane3;
class CGCObjFallingPlane4;
class CGCObjFallingPlane5;
class CGCObjFallingPlane6;
class CGCObjFallingPlane7;
class CGCObjFallingPlane8;
class CGCObjFallingPlane9;
class CGLossScene;

class CGCLevel15
: public IGCGameLayer
, public b2ContactListener 
{
private:
	CGCObjKeys*						m_pcGCOKeys;  // Mia: Variable for first set of Keys
	CGCObjKeys*						m_pcGCOKeys1; // Mia: Variable for second set of Keys
	CGCObjKeys*						m_pcGCOKeys2; // Mia: Variable for third set of Keys

	CGCObjTimer*					m_pcGCTimer;
	CGCObjLives*					m_pcGCOLives;
	CGCObjScore*					m_pcGCOScore; // Mia: Variable for Player Score
	CGCObjHighScore*				m_pcGCOHighScore;

	CGCObjPlayer*					m_pcGCOPlayer;
	CGCFactoryCreationParams		m_sPlayerCreateParams;

	CGCLevelLoader_Ogmo		m_cLevelLoader;

	bool					m_bCheckIfPlayerIsAbovePlatform;

	int						m_iKeysCollected; // Mia: Int for Keys Collected by Player

	int						m_iTotalKeys;	  // Mia: Int for the Total amount of Keys

	int						m_iHighScore;
	
	CocosDenshion::SimpleAudioEngine*	m_pcGCBackgroundAudio;   // Mia: Variable for Background music
	CocosDenshion::SimpleAudioEngine*	m_pcGCSoundEffectsAudio; // Mia: Variable for Sound Effects audio

public:
	CGCLevel15  ( void );
	~CGCLevel15 ( void );

	enum EPlayerActions
	{
		EPA_Up = 0,
		EPA_Down,
		EPA_Left,
		EPA_Right,
		EPA_Fire
	};

    void Callback_OnQuitButton	( Ref* pSender );
	void Callback_OnSkipButton  ( Ref* pSender );
    void Callback_OnResetButton	( Ref* pSender );

	void HandleCollisions( void );

	void keyCollected();		 // Mia: Key Collected by Player function

	void playBackgroundMusic();  // Mia: Play Background Music in Level function

	void playKeyAudio();		 // Mia: Play when a Key is picked up by Player audio function

	void playDoorOpeningAudio(); // Mia: Play when Player unlocks Door audio function

	void PlayerDeathSceneSwap();
	
	void HighScore();

	virtual void onEnter();

		virtual	void VOnCreate	( void );
		virtual void VOnUpdate	( f32 fTimeStep );
		virtual	void VOnDestroy ( void );	

		virtual void BeginContact	( b2Contact* pB2Contact );
		virtual void EndContact		( b2Contact* pB2Contact );
		virtual void PreSolve		( b2Contact* pB2Contact, const b2Manifold* pOldManifold );
		virtual void PostSolve		( b2Contact* pB2Contact, const b2ContactImpulse* pImpulse );
private:
	bool							m_bResetWasRequested; // Mia: Request Reset for cheat button
	bool							m_bQuitWasRequested;  // Mia: Request Quit for cheat button
	bool							m_bSkipWasRequested;  // Mia: Request Skip for cheat button
	bool							m_bDoorUnlocked;      //Brandon bool which is triggered when the door is unlocked
	
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

	void RequestSkip()
	{
		m_bSkipWasRequested = true;
	}

	void SkipRequestWasHandled()
	{
		m_bSkipWasRequested = false;
	}

	bool SkipWasRequested()
	{
		return m_bSkipWasRequested;
	}

	void RequestQuit()
	{
		m_bQuitWasRequested = true; 
	}

	void QuitRequestWasHandled()
	{
		m_bQuitWasRequested = false; 
	}

	bool QuitWasRequested()
	{
		return m_bQuitWasRequested; 
	}
};
#endif // __CGCLevel15_SCENE_H__