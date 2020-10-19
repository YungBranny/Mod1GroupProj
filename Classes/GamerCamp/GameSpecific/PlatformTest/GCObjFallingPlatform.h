#ifndef _CGCOBJFALLINGPLATFORM_
#define _CGCOBJFALLINGPLATFORM__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjFallingPlatform
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2StartPos;

	cocos2d::Vec2 m_v2EndPos;

	cocos2d::Vec2 m_v2FallingVelocity;

	cocos2d::Vec2 m_v2DefaultVelocity;

	bool m_bContactWithPlayer;

	float m_fDestroyPlatformTick;

public:

	CGCObjFallingPlatform ();
	virtual ~CGCObjFallingPlatform () {};

	cocos2d::Vec2 GetStartPos () { return m_v2StartPos; }
	void SetStartPos (cocos2d::Vec2 i) { m_v2StartPos = i; }

	cocos2d::Vec2 GetEndPos () { return m_v2EndPos; }
	void SetEndPos (cocos2d::Vec2 i) { m_v2EndPos = i; }

	cocos2d::Vec2 GetCurrentVelocity () { return m_v2FallingVelocity; }
	void SetCurrentVelocity (cocos2d::Vec2 i) { m_v2FallingVelocity = i; }

	cocos2d::Vec2 GetDefaultVelocity () { return m_v2DefaultVelocity; }
	void SetDefaultVelocity (cocos2d::Vec2 i) { m_v2DefaultVelocity = i; }

	bool GetContactWithPlayer () { return m_bContactWithPlayer; }
	void SetContactWithPlayer (bool i) { m_bContactWithPlayer = i; }


	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);


	void MoveDownOnContact ();

	virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
