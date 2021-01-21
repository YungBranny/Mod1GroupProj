#ifndef _GCOFALLINGPLANE9_
#define _GCOFALLINGPLANE9_

///////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCOFallingPlane9' Header File and Class File was created and was managed by Mehak Hussain.  //
// The purpose of this Class is to create the Falling Plane Enemy.                                   //
// In this Class, I set the collision and velocity for the Plane.                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Enemies/GCBasicEnemies.h"

class CGCObjFallingPlane9
	: public CGCObjSpritePhysics
{
private:
	enum class EMoveDirection
	{
		Down
	};

	unsigned short int		m_iCollisionBuffer;

	EMoveDirection			m_eMoveDirection;

	float					m_fGravity;

	b2Vec2					m_v2StartPosition;
	cocos2d::Vec2			m_v2MoveUpVelocity;
	cocos2d::Vec2			m_v2MoveDownVelocity;

	bool					m_bJustCollided;

	void					InitialiseMovementDirection();
	void					CollisionChecker();

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;

public:
	CGCObjFallingPlane9();
	virtual ~CGCObjFallingPlane9() {};

	GCFACTORY_DECLARE_CREATABLECLASS ( CGCObjFallingPlane9 );

	unsigned short int getCollisionBuffer()				const { return m_iCollisionBuffer; }
	void  setCollisionBuffer ( unsigned short int i )   { m_iCollisionBuffer = i;		   }

	float getGravity()									const { return m_fGravity;		   }
	void  setGravity		 ( float i )				{ m_fGravity = i;				   }

	bool  getJustCollided()								const { return m_bJustCollided;	   }
	void  setJustCollided	 ( bool i  )				{ m_bJustCollided = i;			   }

	// Setting up Getters
	b2Vec2			getStartPosition()					const { return m_v2StartPosition;	  }
	cocos2d::Vec2	getMovingUpVelocity()				const { return m_v2MoveUpVelocity;	  }
	cocos2d::Vec2	getMovingDownVelocity()				const { return m_v2MoveDownVelocity;  }

	// Setting up Setters
	void setStartPosition		( b2Vec2 i )					{ m_v2StartPosition = i;	 }
	void setMovingUpVelocity	( cocos2d::Vec2 i )				{ m_v2MoveUpVelocity = i;    }
	void setMovingDownVelocity  ( cocos2d::Vec2 i )				{ m_v2MoveDownVelocity = i;  }

	void SettingVelocity();
	void ResetPosition();

	virtual void VOnResourceAcquire	( void );
	virtual void VOnResurrected		( void );
	virtual void VOnUpdate			( f32 fTimestep );

	virtual void VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);
};
#endif