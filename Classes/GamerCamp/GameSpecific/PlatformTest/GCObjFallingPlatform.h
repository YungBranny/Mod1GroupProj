#ifndef _CGCOBJFALLINGPLATFORM__
#define _CGCOBJFALLINGPLATFORM__

//Brandon Middleton
//This class draws a platform when falls when it is stood on
//I will no longer use the class as the platform isnt needed in the game and will
//refactoring it in the scalablefalling platform

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjFallingPlatform
	: public CGCObjSpritePhysics
{
private:
	cocos2d::Vec2 m_v2StartPos; //Vector2 which will be set as the start/reset position

	cocos2d::Vec2 m_v2EndPos; //vector2 for the endposition which is no longer needed

	cocos2d::Vec2 m_v2FallingVelocity; //vector2 for the Falling velocity/speed which is no longer needed

	cocos2d::Vec2 m_v2DefaultVelocity; //vector2 for the Velocity which is no longer needed

	bool m_bContactWithPlayer; //Bool which needs to be set to true if the player is colliding with this platform
	bool m_bCanDelete; // Bool that needs to be set to true once the destroyplatform tick has reached 0 which will then allow the platform to be delete

	float m_fDestroyPlatformTick; // A float that counts down to 0, once it has reached 0 it will set the can delete bool to true

public:

	CGCObjFallingPlatform (); //constructor
	virtual ~CGCObjFallingPlatform () {}; //deconstructor

	cocos2d::Vec2 GetStartPos () const { return m_v2StartPos; }					//getter for the start pos
	void SetStartPos (cocos2d::Vec2 i) { m_v2StartPos = i; }					//setter fro the start pos

	cocos2d::Vec2 GetEndPos () const { return m_v2EndPos; }						//getter for the end pos
	void SetEndPos (cocos2d::Vec2 i) { m_v2EndPos = i; }						//setter fro the end pos

	cocos2d::Vec2 GetCurrentVelocity () const { return m_v2FallingVelocity; }	//getter for the Current velocity
	void SetCurrentVelocity (cocos2d::Vec2 i) { m_v2FallingVelocity = i; }		//setter fro the Current velocity

	cocos2d::Vec2 GetDefaultVelocity () const { return m_v2DefaultVelocity; }	//getter for the Default Velocity
	void SetDefaultVelocity (cocos2d::Vec2 i) { m_v2DefaultVelocity = i; }		//setter fro the Default Velocity

	bool GetContactWithPlayer () const { return m_bContactWithPlayer; }			//getter for the Contact with player bool
	void SetContactWithPlayer (bool i) { m_bContactWithPlayer = i; }			//setter fro the Contact with player bool

	bool GetCanDelete () const { return m_bCanDelete; }							//getter for the Can delete float
	void SetCanDelete (bool i) { m_bCanDelete = i; }							//setter fro the Can delete float


	virtual void VOnResourceAcquire (void);	  //Default functions needed
	virtual void VOnResurrected (void);		  //Default functions needed
	virtual void VOnResourceRelease (void);	  //Default functions needed
	virtual void VOnReset (void);			  //Default functions needed


	void MoveDownOnContact (); //Function that moved the platform down on contact, no longer needed but will be refactored

	virtual void VOnUpdate (f32 fTimestep); //Update
}; 

#endif
