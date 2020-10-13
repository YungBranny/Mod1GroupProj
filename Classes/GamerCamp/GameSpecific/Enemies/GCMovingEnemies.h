#ifndef _GCMOVINGENEMIES_
#define _GCMOVINGENEMIES_


//#include "Classes/GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"



class CGCMovingEnemies
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

	cocos2d::Vec2			m_vEndDestination1;
	cocos2d::Vec2			m_vEndDesitnation2;

	cocos2d::Vec2			m_vMovingRightVelocity;
	cocos2d::Vec2			m_vMovingLeftVelocity;
	cocos2d::Vec2			m_vMovingUpVelocity;
	cocos2d::Vec2			m_vMovingDownVelocity;

	bool					m_bMovingLeftAndRight;
	bool					m_bJustCollided;

	void					InitialiseMovementDirection ();
	void					CollisionChecker ();

public:

	CGCMovingEnemies ();
	virtual ~CGCMovingEnemies () {};

	unsigned short int getCollisionBuffer () { return m_iCollisionBuffer; }
	void  setCollisionBuffer (unsigned short int i) { m_iCollisionBuffer = i; }


	float getGravity () const { return m_fGravity; }
	void  setGravity (float i) { m_fGravity = i; }

	bool  getJustCollided ()		{return m_bJustCollided;}
	void  setJustCollided (bool i)	{ m_bJustCollided = i;	}


	cocos2d::Vec2	getEndDestination1		()	{ return m_vEndDestination1;	}
	cocos2d::Vec2	getEndDesination2		()	{ return m_vEndDesitnation2;	}
	cocos2d::Vec2	getMovingRightVelocity	()	{ return m_vMovingRightVelocity;}
	cocos2d::Vec2	getMovingLeftVelocity	()	{ return m_vMovingRightVelocity;}
	cocos2d::Vec2	getMovingUpVelocity		()	{ return m_vMovingUpVelocity;	}
	cocos2d::Vec2	getMovingDownVelocity	()	{ return m_vMovingDownVelocity;	}

	void setEndDesination1			(cocos2d::Vec2 i) { m_vEndDestination1 = i;		}
	void setEndDesination2			(cocos2d::Vec2 i) { m_vEndDesitnation2 = i;		}
	void setMovingRightVelocity		(cocos2d::Vec2 i) { m_vMovingRightVelocity = i; }
	void setMovingLeftVelocity		(cocos2d::Vec2 i) { m_vMovingLeftVelocity = i;	}
	void setMovingUpVelocity		(cocos2d::Vec2 i) { m_vMovingUpVelocity = i;	}
	void setMovingDownVelocity		(cocos2d::Vec2 i) { m_vMovingDownVelocity = i;	}
										 
	void ChangeDirection ();
	void Movement ();

	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);


	virtual void VOnUpdate (f32 fTimestep);



};
#endif
