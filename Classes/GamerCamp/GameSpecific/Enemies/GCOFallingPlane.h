#ifndef _GCOFALLINGPLANE_
#define _GCOFALLINGPLANE_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjFallingPlane
	: public CGCObjSpritePhysics
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

	float					m_fGravity;

	cocos2d::Vec2			m_v2StartPosition;
	cocos2d::Vec2			m_v2EndPosition;
	cocos2d::Vec2			m_v2MoveRightVelocity;
	cocos2d::Vec2			m_v2MoveLeftVelocity;
	cocos2d::Vec2			m_v2MoveUpVelocity;
	cocos2d::Vec2			m_v2MoveDownVelocity;

	bool					m_bMoveUpAndDown;
	bool					m_bJustCollided;

	void					InitialiseMovementDirection();
	void					CollisionChecker();

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;

public:
	CGCObjFallingPlane();
	virtual ~CGCObjFallingPlane() {};

	GCFACTORY_DECLARE_CREATABLECLASS(CGCObjFallingPlane);

	unsigned short int getCollisionBuffer()			const { return m_iCollisionBuffer; }
	void  setCollisionBuffer(unsigned short int i) { m_iCollisionBuffer = i; }

	float getGravity()									const { return m_fGravity; }
	void  setGravity(float i) { m_fGravity = i; }

	bool  getJustCollided()							const { return m_bJustCollided; }
	void  setJustCollided(bool i) { m_bJustCollided = i; }

	// Setting up Getters
	cocos2d::Vec2	getStartPosition()					const { return m_v2StartPosition; }
	cocos2d::Vec2	getEndPosition()					const { return m_v2EndPosition; }
	cocos2d::Vec2	getMovingRightVelocity()			const { return m_v2MoveRightVelocity; }
	cocos2d::Vec2	getMovingLeftVelocity()				const { return m_v2MoveRightVelocity; }
	cocos2d::Vec2	getMovingUpVelocity()				const { return m_v2MoveUpVelocity; }
	cocos2d::Vec2	getMovingDownVelocity()				const { return m_v2MoveDownVelocity; }

	// Setting up Setters
	void setStartPosition(cocos2d::Vec2 i) { m_v2StartPosition = i; }
	void setEndPosition(cocos2d::Vec2 i) { m_v2EndPosition = i; }
	void setMovingRightVelocity(cocos2d::Vec2 i) { m_v2MoveRightVelocity = i; }
	void setMovingLeftVelocity(cocos2d::Vec2 i) { m_v2MoveLeftVelocity = i; }
	void setMovingUpVelocity(cocos2d::Vec2 i) { m_v2MoveUpVelocity = i; }
	void setMovingDownVelocityz(cocos2d::Vec2 i) { m_v2MoveDownVelocity = i; }

	//void OppositeDirection();
	void SettingVelocity();

	virtual void VOnResourceAcquire(void);
	virtual void VOnUpdate(f32 fTimestep);

	virtual void VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);
};

#endif