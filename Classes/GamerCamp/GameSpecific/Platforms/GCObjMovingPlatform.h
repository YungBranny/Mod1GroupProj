#ifndef _GCOBJMOVINGPLATFORM_
#define _GCOBJMOVINGPLATFORM_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCMovingPlatform
	:public CGCObjSpritePhysics
{
private:
	enum class EMoveDirection
	{
		Left,
		Right,
		Up,
		Down
	};

	unsigned short int		m_iCollisionBuffer;


	EMoveDirection			m_eMoveDirection;

	float					m_fTimeInCurrentMoveDirection;
	float					m_fGravity;

	cocos2d::Vec2			m_v2StartPosition;
	cocos2d::Vec2			m_v2EndPosition;
	cocos2d::Vec2			m_vMovingRightVelocity;
	cocos2d::Vec2			m_vMovingLeftVelocity;
	cocos2d::Vec2			m_vMovingUpVelocity;
	cocos2d::Vec2			m_vMovingDownVelocity;

	bool					m_bMoveUpAndDown;
	bool					m_bJustCollided;

	void					InitialiseMovementDirection();
	void					CollisionChecker();

public:

	CGCMovingPlatform();
	virtual ~CGCMovingPlatform() {};

	unsigned short int getCollisionBuffer() const { return m_iCollisionBuffer; }
	void  setCollisionBuffer(unsigned short int i) { m_iCollisionBuffer = i; }


	float getGravity() const { return m_fGravity; }
	void  setGravity(float i) { m_fGravity = i; }

	bool  getJustCollided() const { return m_bJustCollided; }
	void  setJustCollided(bool i) { m_bJustCollided = i; }


	cocos2d::Vec2	getStartPosition()	        const { return m_v2StartPosition; }
	cocos2d::Vec2	getEndPosition()	        const { return m_v2EndPosition; }
	cocos2d::Vec2	getMovingRightVelocity()	const { return m_vMovingRightVelocity; }
	cocos2d::Vec2	getMovingLeftVelocity()	    const { return m_vMovingRightVelocity; }
	cocos2d::Vec2	getMovingUpVelocity()	    const { return m_vMovingUpVelocity; }
	cocos2d::Vec2	getMovingDownVelocity()	    const { return m_vMovingDownVelocity; }

	void setStartPosition       (cocos2d::Vec2 i) { m_v2StartPosition = i; }
	void setEndPosition         (cocos2d::Vec2 i) { m_v2EndPosition = i; }
	void setMovingRightVelocity (cocos2d::Vec2 i) { m_vMovingRightVelocity = i; }
	void setMovingLeftVelocity  (cocos2d::Vec2 i) { m_vMovingLeftVelocity = i; }
	void setMovingUpVelocity    (cocos2d::Vec2 i) { m_vMovingUpVelocity = i; }
	void setMovingDownVelocityz (cocos2d::Vec2 i) { m_vMovingDownVelocity = i; }

	void Movement();
	void SettingVelocity();

	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnUpdate(f32 fTimestep);



};

#endif
