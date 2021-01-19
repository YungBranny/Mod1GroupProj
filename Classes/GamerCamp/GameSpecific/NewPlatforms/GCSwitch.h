#ifndef _GCSWITCH_
#define _GCSWITCH__


//Brandon Middleton
//This class draws a switch which triggers and event in gameD

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class GCSwitch
	: public CGCObjSpritePhysics
{
private:
	bool m_bSwitchHit;
public:

	GCFACTORY_DECLARE_CREATABLECLASS (GCSwitch);

	GCSwitch ();				//constructor
	virtual ~GCSwitch () {};	//deconstuctor

	bool getSwitchHit ()const { return m_bSwitchHit; } //bool to say if the switch has been hit or not
	void setSwitchHit (bool i) { m_bSwitchHit = i; }
	
	virtual void VOnResurrected ();
	virtual void VOnReset ();
};

#endif
