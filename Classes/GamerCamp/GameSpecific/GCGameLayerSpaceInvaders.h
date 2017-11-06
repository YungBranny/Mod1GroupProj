/////////////////////////////////////////////////////////////////// /////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMELAYERSPACEINVADERS_H_
#define _GAMELAYERSPACEINVADERS_H_

#include "../GCCocosInterface/IGCGameLayer.h"


//////////////////////////////////////////////////////////////////////////
// fwd decl
class CGCObjSprite;
class CGCObjTileLayer;
class CGCObjPlayer;
class CGCObjInvader;
class CGCObjGroupInvader;
class CGCObjGroupProjectilePlayer;


//////////////////////////////////////////////////////////////////////////
// sample class that creates a 'game' by deriving from IGCGameLayer
//////////////////////////////////////////////////////////////////////////
class CGCGameLayerSpaceInvaders 
: public IGCGameLayer 
{
private:
	// object groups
	CGCObjGroupInvader*				m_pcGCGroupInvader;
	CGCObjGroupProjectilePlayer*	m_pcGCGroupProjectilePlayer;

	// backgrounds
	CGCObjSprite*			m_pcGCSprBackGround;

	// mario
	CGCObjPlayer*			m_pcGCOPlayer;

public:
	CGCGameLayerSpaceInvaders	( void );
	~CGCGameLayerSpaceInvaders	( void );

	//////////////////////////////////////////////////////////////////////////
	// Node interface...
    virtual bool init();
	virtual void onEnter();
	// Node interface...
	//////////////////////////////////////////////////////////////////////////
    
    // 'selector' callbacks
    void Callback_OnQuitButton	( Ref* pSender );
    void Callback_OnResetButton	( Ref* pSender );


	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface
		virtual	void VOnCreate	( void );

		virtual void VOnUpdate	( f32 fTimeStep );

		virtual	void VOnDestroy ( void );	
	// IGCGameLayer interface
	//////////////////////////////////////////////////////////////////////////


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
// collision handling
public:
	// n.b. collisions supported only between CGCObjSprites with this code
	struct SCollisionPair
	{
		CGCObjSprite*	pcGCObjSpriteOne; 
		CGCObjSprite* 	pcGCObjSpriteTwo;
	};

	// used to pass arrays of gcobjsprites for doing collision detection
	struct SCollisionArray
	{
		CGCObjSprite**	papcArray;	// pointer to an array of gcsprite pointers
		u32				uNumInArray;
	};

	// typedef for collision list iterator callback	required by IterateCollisions()
	// pUserData:		the user data passed to IterateCollisions()
	// rsCollisionPair:	a collision pair in the collision cache
	// return:			true to keep iterating, false to stop
	typedef bool (*pfnCB_CollisionListIterator)( void* pUserData, const SCollisionPair& rsCollisionPair );

	// resets collision cache
	void FlushCollisions	( void );

	// collides one array of CGCObjSprite* against another and stores the results in m_asCollisionsThisFrame
	// N.B. this code assumes that no CGCObjSprite is in both arrays
	void CheckForCollisions	( const SCollisionArray* pFirst, const SCollisionArray* pSecond );

	// iterates collision cache for each sCollisionPair it will call pCB_ForEachCollision with pUserData and the sCollisionPair
	void IterateCollisions	( void* pUserData, pfnCB_CollisionListIterator pCB_ForEachCollision );

private:
	// maximum collisions that can be stored in one frame
	static const u32 k_uMaxCollisionsPerFrame = 128;

	// collision data is stored here when CheckForCollisions is called
	SCollisionPair	m_asCollisionCache[ k_uMaxCollisionsPerFrame ];
	u32				m_uNumCollisionsInCache;

// collision handling
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// our game's update loop 

	// done after VOnUpdate	to handle collisions based on this frame's update
	void HandleCollisions( void );

	// static function that conforms to the typedef for pfnCB_CollisionListIterator
	// this is used to iterate the collisions via IterateCollisions()
	static bool CB_CollIter_HandleLogic_PlayerVsInvader( void* pGameLayerSpaceInvadersInstance, const SCollisionPair& rsCollisionPair );

	// static function that conforms to the typedef for pfnCB_CollisionListIterator
	// this is used to iterate the collisions via IterateCollisions()
	static bool CB_CollIter_HandleLogic_ProjectileVsInvader( void* pNotUsed, const SCollisionPair& rsCollisionPair );

// our game's update loop 
//////////////////////////////////////////////////////////////////////////

};

#endif // __CGCGameLayerSpaceInvaders_SCENE_H__
