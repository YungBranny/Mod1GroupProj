#ifndef _CGCOBJSCALINGFALLINGPLATFORM_
#define _CGCOBJSCALINGFALLINGPLATFORM__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjScalingFallingPlatform
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2FallingVelocity;

	cocos2d::Vec2 m_v2DefaultVelocity;

	bool m_bContactWithPlayer;
	bool m_bCanDelete;

	float m_fDestroyPlatformTick;

public:

	CGCObjScalingFallingPlatform ();
	virtual ~CGCObjScalingFallingPlatform () {};


	cocos2d::Vec2 GetFallingVelocity () const { return m_v2FallingVelocity; }
	void SetFallingVelocity (cocos2d::Vec2 i) { m_v2FallingVelocity = i; }

	cocos2d::Vec2 GetDefaultVelocity () const { return m_v2DefaultVelocity; }
	void SetDefaultVelocity (cocos2d::Vec2 i) { m_v2DefaultVelocity = i; }

	bool GetContactWithPlayer () const { return m_bContactWithPlayer; }
	void SetContactWithPlayer (bool i) { m_bContactWithPlayer = i; }

	bool GetCanDelete () const { return m_bCanDelete; }
	void SetCanDelete (bool i) { m_bCanDelete = i; }


	virtual void VOnResourceAcquire (void);

	void MoveDownOnContact ();
	virtual void VOnUpdate (f32 fTimestep);

	//virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
