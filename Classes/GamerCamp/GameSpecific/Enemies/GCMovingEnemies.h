#ifndef _GCMOVINGENEMIES_
#define _GCMOVINGENEMIES_


//Brandon Middleton
//This is the moving enemy class which spawns an enemy that can move either left and right or up and down
//This is done by setting a bool to true or false which ultimately decided which direction it should move in
//Inside this class are two end desitnations which need to be set for the enemy to move too

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"




class CGCMovingEnemies
	:public CGCObjSpritePhysics

{
private:
	enum class EMoveDirection	//EmovementDirections
	{							//EmovementDirections
		Left,					//EmovementDirections
		Right,					//EmovementDirections
		Up,						//EmovementDirections
		Down					//EmovementDirections
	};

	unsigned short int		m_iCollisionBuffer;				//A buffer which gets triggered when the player hits the enemy so collision with this obj cannot be called more than once until its reset

	unsigned short int		m_iCollisionDirBuffer;				//A buffer which gets triggered when the Enemy Hits a collider

	EMoveDirection			m_eMoveDirection;				 //EmoveDirection which sets what direction it starts in
	float					m_fGravity;						 //Gravit float which will ultimately be removed

	cocos2d::Vec2			m_vEndDestination1;				 //The end destinations
	cocos2d::Vec2			m_vEndDesitnation2;				 //The end destinations

	cocos2d::Vec2			m_vMovingRightVelocity;			 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_vMovingLeftVelocity;			 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_vMovingUpVelocity;			 //The velocitys for how fast the enemy should move
	cocos2d::Vec2			m_vMovingDownVelocity;			 //The velocitys for how fast the enemy should move

	bool					m_bMovingLeftAndRight;			 //Bool to say which direction the enemy is moving in
	bool					m_bJustCollided;				 //Bool to say if the enemy has just collided with the player
	bool					m_bDefaultDirection;			 //Bool which is triggered when the enemy collides witht the collider which will help change its direction
	bool					m_bJustChangedDir;

	void					InitialiseMovementDirection ();	 //Function which checks if the moving left and right bool is true or false, if it is true then the enemy will go left/right if it false the enemy will go up or down
	void VOnResourceAcquire ();
	void					CollisionChecker ();			 //Function which checks if the just collided bool is true or false#
	void					CollisionDirChecker ();

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;

public:



	CGCMovingEnemies ();
	virtual ~CGCMovingEnemies () {};

	GCFACTORY_DECLARE_CREATABLECLASS (CGCMovingEnemies);



	unsigned short int getCollisionDirBuffer ()	const { return m_iCollisionDirBuffer; }	//Getter for CollisionBuffer
	void  setCollisionDirBuffer (unsigned short int i) { m_iCollisionDirBuffer = i; }	//Setter for CollisionBuffer

	unsigned short int getCollisionBuffer ()	const { return m_iCollisionBuffer; }	//Getter for CollisionBuffer
	void  setCollisionBuffer (unsigned short int i) { m_iCollisionBuffer = i; }	//Setter for CollisionBuffer


	float getGravity ()							const { return m_fGravity; }	//Getter for Gravity
	void  setGravity (float i) { m_fGravity = i; }	//Setter for Gravity

	bool  getJustCollided ()					const { return m_bJustCollided; }	//Getter for CollisionBuffer
	void  setJustCollided (bool i) { m_bJustCollided = i; }	//Setter for CollisionBuffer

	bool  getChangedDir ()					const { return m_bJustChangedDir; }	//Getter for CollisionBuffer
	void  setChangedDir (bool i) { m_bJustChangedDir = i; }	//Setter for CollisionBuffer



	bool  getDefaultDirection ()				const { return m_bDefaultDirection; }	//Getter for DefaultDirection
	void  setDefaultDirection (bool i) { m_bDefaultDirection = i; }	//Setter for DefaultDirection

	cocos2d::Vec2	getEndDestination1 ()	const { return m_vEndDestination1; }	//Getter for EndDesination1
	cocos2d::Vec2	getEndDesination2 ()	const { return m_vEndDesitnation2; }	//Getter for EndDesination2
	cocos2d::Vec2	getMovingRightVelocity ()	const { return m_vMovingRightVelocity; }	//Getter for MovingRightVelocity
	cocos2d::Vec2	getMovingLeftVelocity ()	const { return m_vMovingRightVelocity; }	//Getter for MovingLeftVelocity
	cocos2d::Vec2	getMovingUpVelocity ()	const { return m_vMovingUpVelocity; }	//Getter for MovingUpVelocity
	cocos2d::Vec2	getMovingDownVelocity ()	const { return m_vMovingDownVelocity; }	//Getter for DownVelocity

	void setEndDesination1 (cocos2d::Vec2 i) { m_vEndDestination1 = i; }	//Setter for EndDesination1
	void setEndDesination2 (cocos2d::Vec2 i) { m_vEndDesitnation2 = i; }	//Setter for EndDesination2
	void setMovingRightVelocity (cocos2d::Vec2 i) { m_vMovingRightVelocity = i; }	//Setter for MovingRightVelocity
	void setMovingLeftVelocity (cocos2d::Vec2 i) { m_vMovingLeftVelocity = i; }	//Setter for MovingLeftVelocity
	void setMovingUpVelocity (cocos2d::Vec2 i) { m_vMovingUpVelocity = i; }	//Setter for MovingUpVelocity
	void setMovingDownVelocity (cocos2d::Vec2 i) { m_vMovingDownVelocity = i; }	//Setter for DownVelocity

	void ChangeDirection ();					  //Function which contains the logic to change direction
	void Movement ();							  //Function which 

	//virtual void VOnResourceAcquire (void);		  //Default functions for spritephysics
	virtual void VOnResurrected (void);			  //Default functions for spritephysics
	virtual void VOnResourceRelease (void);		  //Default functions for spritephysics
	//virtual void VOnReset (void);				  //Default functions for spritephysics
	virtual void VOnUpdate (f32 fTimestep);		  //Default functions for spritephysics

	virtual void VHandleFactoryParams (const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition);


};
#endif
