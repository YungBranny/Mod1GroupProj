////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJPLAYER_H_
#define _GCOBJPLAYER_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjGroupProjectilePlayer;



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
{
private:
	// used to fire projectiles
	CGCObjGroupProjectilePlayer* m_pProjectileManager; 

	// member variables for 'physicsy' handling
	// N.B. uses sprite to store position and has no rotation
	f32		m_fMaximumMoveForce_Horizontal;
	f32		m_fMaximumMoveForce_Vertical;
	f32		m_fDragCoefficient_Linear;
	f32		m_fDragCoefficient_Square;
	f32		m_fNoInput_ExtraDrag_Square;
	f32		m_fNoInput_VelocityThreshold;

public:
	CGCObjPlayer();

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

	// overridden virtuals from the game object interface
	//////////////////////////////////////////////////////////////////////////

	// updates the movement of the CCSprite
	void UpdateMovement( f32 fTimeStep );

	b2Vec2	GetControlVector( f32 fTImeStep );

	bool	FireWasJustPressed();

    // this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
    void NotifyOfCollisionWithInvader();


	//////////////////////////////////////////////////////////////////////////
	// example function to show how to use a callback function with an object
	// NOT derived from cocos2d::Object in a CCSequence
	//////////////////////////////////////////////////////////////////////////
	static void TestCBFunction( void* pData )
	{
		// we assume this cast is safe because we passed the void* to the function
		// see line 219 of GCObjPlayer.cpp
		CGCObjPlayer* pThis = reinterpret_cast< CGCObjPlayer* >( pData );
		CCLOG(" callback fn! data %s\n", pThis->GetName().c_str() );
	}
};
#endif // #ifndef _GCOBJPLAYER_H_