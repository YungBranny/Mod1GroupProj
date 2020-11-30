#ifndef _GCSWITCH_
#define _GCSWITCH__


//Brandon Middleton
//This class draws a single platform which will be thrown into a platform manager to make it scaleable

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

//#include "SimpleAudioEngine.h"
//#include "AudioEngine.h"



class GCSwitch
	: public CGCObjSpritePhysics
{
private:
	//CocosDenshion::SimpleAudioEngine* m_audio;
	//cocos2d::experimental::AudioEngine* m_audio1;
	bool m_bSwitchHit;
public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCSwitch);

	GCSwitch ();				//constructor
	virtual ~GCSwitch () {};	//deconstuctor

	bool getSwitchHit ()const { return m_bSwitchHit; }
	void setSwitchHit (bool i) { m_bSwitchHit = i; }
	
	virtual void VOnResurrected ();
	virtual void VOnReset ();



	//virtual void VOnUpdate (f32 fTimestep);

	// this function exists purely to better illustrate the EXAMPLE collision detection functionality in CGCGameLayerSpaceInvaders
	//void NotifyOfCollisionWithPlayer ();





};

#endif
