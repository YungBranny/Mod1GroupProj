#ifndef _CGCOBJTRAVELATORPLATFORM_
#define _CGCOBJTRAVELATORPLATFORM__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjTravelatorPlatform
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2StartPos;



public:

	CGCObjTravelatorPlatform();
	virtual ~CGCObjTravelatorPlatform() {};
	
	/////////////////////////////////////////////////////////////////////////////
	
	cocos2d::Vec2 GetStartPos() { return m_v2StartPos; }
	void SetStartPos(cocos2d::Vec2 i) { m_v2StartPos = i; }

	/////////////////////////////////////////////////////////////////////////////
	virtual void VOnResourceAcquire(void);
	virtual void VOnResurrected(void);
	virtual void VOnResourceRelease(void);
	virtual void VOnReset(void);
	virtual void VOnUpdate(f32 fTimestep);

	/////////////////////////////////////////////////////////////////////////////

};

#endif
