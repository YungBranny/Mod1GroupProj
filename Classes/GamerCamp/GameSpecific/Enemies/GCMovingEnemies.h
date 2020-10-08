#ifndef _GCMOVINGENEMIES_
#define _GCMOVINGENEMIES_


#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

class CGCMovingEnemies
	:public CGCObjSpritePhysics
{
private:
	enum EMoveDirection
	{
		Left,
		Right,
		Up,
		Down
	};
			
	EMoveDirection			m_eMoveDirection;
	float					m_fTimeInCurrentMoveDirection;
	float					m_fGravity;
	cocos2d::Vec2			m_fEndDestination1;
	cocos2d::Vec2			m_fEndDesitnation2;

	bool					m_bMovingLeftAndRight;


public:

	CGCMovingEnemies ();
	virtual ~CGCMovingEnemies () {};


	float getGravity () { return m_fGravity; }
	void  setGravity (float i) { m_fGravity = i; }

	virtual void VOnResourceAcquire (void);
	virtual void VOnResurrected (void);
	virtual void VOnResourceRelease (void);
	virtual void VOnReset (void);


	virtual void VOnUpdate (f32 fTimestep);



};
#endif
