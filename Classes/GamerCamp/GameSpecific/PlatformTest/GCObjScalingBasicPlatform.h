#ifndef _CGCOBJSCALINGBASICPLATFORM_
#define _CGCOBJSCALINGBASICPLATFORM__


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

#include "SimpleAudioEngine.h"
#include "AudioEngine.h"



class CGCObjScalingBasicPlatform
	: public CGCObjSpritePhysics
{
private:
	CocosDenshion::SimpleAudioEngine* m_audio;
	cocos2d::experimental::AudioEngine* m_audio1;
public:

	CGCObjScalingBasicPlatform ();
	virtual ~CGCObjScalingBasicPlatform () {};


	void createScalingPlatforms ();

	virtual void VOnResourceAcquire (void);


	//virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
