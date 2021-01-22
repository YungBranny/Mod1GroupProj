#ifndef _CGCOBJTRAVELATORPLATFORM_
#define _CGCOBJTRAVELATORPLATFORM__

#ifndef TINYXML2_INCLUDED
#include "external\tinyxml2\tinyxml2.h"
#endif

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"


#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"



class CGCObjTravelatorPlatform
	: public CGCObjSpritePhysics
{
private:
	//cocos2d::Vec2 m_v2StartPos;

	float m_fVelocity;

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
	
public:

	CGCObjTravelatorPlatform();
	virtual ~CGCObjTravelatorPlatform() {};
	
	GCFACTORY_DECLARE_CREATABLECLASS(CGCObjTravelatorPlatform);
	
	/////////////////////////////////////////////////////////////////////////////
	
	//cocos2d::Vec2 GetStartPos() { return m_v2StartPos; }
	//void SetStartPos(cocos2d::Vec2 i) { m_v2StartPos = i; }

	/////////////////////////////////////////////////////////////////////////////
	//virtual void VOnResourceAcquire(void);
	//virtual void VOnResurrected(void);
	//virtual void VOnResourceRelease(void);
	//virtual void VOnReset(void);
	virtual void VOnUpdate(f32 fTimestep);
	
	float getVelocity() const { return m_fVelocity; }
	void setVelocity(float f) { m_fVelocity = f;	}

	virtual void VHandleFactoryParams(const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);
	
	/////////////////////////////////////////////////////////////////////////////

	
};

#endif