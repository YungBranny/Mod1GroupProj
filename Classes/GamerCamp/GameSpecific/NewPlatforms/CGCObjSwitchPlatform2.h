#ifndef _CGCOBJSWITCHPLATFORM2_
#define _CGCOBJSWITCHPLATFORM2__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"



class CGCObjSwitchPlatform2
	: public CGCObjSpritePhysics
{
private:
	//CocosDenshion::SimpleAudioEngine* m_audio;
	//cocos2d::experimental::AudioEngine* m_audio1;
public:

	GCFACTORY_DECLARE_CREATABLECLASS (CGCObjSwitchPlatform2);

	CGCObjSwitchPlatform2 ();				//constructor
	virtual ~CGCObjSwitchPlatform2 () {};	//deconstuctor


//	virtual void VOnResourceAcquire (void);

	void DestroyPlatform ();
	void movePlatform ();
	bool i = false;
	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();

	virtual void VOnUpdate (f32 fTimeStep);

	virtual void VOnResurrected ();


};

#endif
