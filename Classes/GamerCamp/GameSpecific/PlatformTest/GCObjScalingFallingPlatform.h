#ifndef _CGCOBJSCALINGFALLINGPLATFORM_
#define _CGCOBJSCALINGFALLINGPLATFORM__



//Brandon Middleton
//This class draws a single platform when falls when it is stood on, this is intended to be used in the platform manager so it can be scaled
//Refactoring needs to be done so the platform doesnt move down but just deletes after a while

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjScalingFallingPlatform
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2FallingVelocity;	//vector2 for the Falling velocity/speed which is no longer needed

	cocos2d::Vec2 m_v2DefaultVelocity;	//vector2 for the Velocity which is no longer needed

	bool m_bContactWithPlayer;			//Bool which needs to be set to true if the player is colliding with this platform
	bool m_bCanDelete;					//Bool that needs to be set to true once the destroyplatform tick has reached 0 which will then allow the platform to be delete

	float m_fDestroyPlatformTick;		// A float that counts down to 0, once it has reached 0 it will set the can delete bool to true


public:

	CGCObjScalingFallingPlatform ();												//constructor
	virtual ~CGCObjScalingFallingPlatform () {};									//deconstructor

	cocos2d::Vec2 GetFallingVelocity () const { return m_v2FallingVelocity; }		//getter for the Current velocity
	void SetFallingVelocity (cocos2d::Vec2 i) { m_v2FallingVelocity = i; }			//setter for the Current velocity

	cocos2d::Vec2 GetDefaultVelocity () const { return m_v2DefaultVelocity; }		//getter for the Default Velocity
	void SetDefaultVelocity (cocos2d::Vec2 i) { m_v2DefaultVelocity = i; }			//setter for the Default Velocity

	bool GetContactWithPlayer () const { return m_bContactWithPlayer; }				//getter for the Contact with player bool
	void SetContactWithPlayer (bool i) { m_bContactWithPlayer = i; }				//setter for the Contact with player bool

	bool GetCanDelete () const { return m_bCanDelete; }								//getter for the Can delete float
	void SetCanDelete (bool i) { m_bCanDelete = i; }								//setter for the Can delete float


	virtual void VOnResourceAcquire (void);											//Default Function

	void MoveDownOnContact ();														//Function that moved the platform down on contact, no longer needed but will be refactored
	virtual void VOnUpdate (f32 fTimestep);											//UpdateFunction

};

#endif
