#ifndef _GCTMHAZARDDOWN_
#define _GCTMHAZARDDOWN_


//Brandon Middleton
//This class is used for a basic enemy (spike/Hazard)

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCTMHazardDown
	: public CGCObjSpritePhysics
{
private:
	float m_fGravity;										//float for gravity


	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
public:

	CGCTMHazardDown ();										//constructor
	virtual ~CGCTMHazardDown () {};							//deconstructor

	GCFACTORY_DECLARE_CREATABLECLASS (CGCTMHazardDown);


	float getGravity () { return m_fGravity; }	//Getter and setter for gravity
	void  setGravity (float i) { m_fGravity = i; }	//Getter and setter for gravity




	virtual void VOnResourceAcquire (void);				//Default Functions
	virtual void VOnResurrected (void);				//Default Functions
	virtual void VOnResourceRelease (void);				//Default Functions
	virtual void VOnReset (void);				//Default Functions

	virtual void VOnUpdate (f32 fTimestep);					//Update
	virtual void VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);

};

#endif