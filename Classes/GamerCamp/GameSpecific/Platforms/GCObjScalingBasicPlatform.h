#ifndef _CGCOBJSCALINGBASICPLATFORM_
#define _CGCOBJSCALINGBASICPLATFORM__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

//#include "SimpleAudioEngine.h"
//#include "AudioEngine.h"



class CGCObjScalingBasicPlatform
	: public CGCObjSpritePhysics
{
private:
	//CocosDenshion::SimpleAudioEngine* m_audio;
	//cocos2d::experimental::AudioEngine* m_audio1;
	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;
public:

	GCFACTORY_DECLARE_CREATABLECLASS(CGCObjScalingBasicPlatform);
	
	CGCObjScalingBasicPlatform ();				//constructor
	virtual ~CGCObjScalingBasicPlatform () {};	//deconstuctor


	virtual void VOnResourceAcquire (void);

	virtual void VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);
	//virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
