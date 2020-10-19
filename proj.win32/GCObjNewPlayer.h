#ifndef _GCOBJNEWPLAYER_H_
#define _GCOBJNEWPLAYER_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

enum EPlayerActions
{
	EPA_AxisMove_X,
	EPA_AxisMove_Y,
	EPA_ButtonFire
};

class CGCObjNewPlayer
	: public CGCObjSpritePhysics
{
private:

	cocos2d::Vec2 m_v2MovementSpeed;
	f32 m_fMovementSpeedx;
	f32 m_fJumpPower;

	bool m_bCanJump;

	TGCActionToKeyMap< EPlayerActions >* m_pcControllerActionToKeyMap;

public:

	CGCObjNewPlayer();

	virtual ~CGCObjNewPlayer()
	{}

	virtual void VOnResourceAcquire(void);

	virtual void VOnReset(void);

	virtual void VOnUpdate(f32 fTimeStep);

	virtual void VOnResourceRelease(void);

	void UpdateMovement(f32 fTimeStep);

	bool GetCanJump() { return m_bCanJump; }

	void SetCanJump(bool i) { m_bCanJump = i; }

};

#endif
