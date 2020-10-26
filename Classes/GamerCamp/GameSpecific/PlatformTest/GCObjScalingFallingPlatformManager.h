#ifndef	_GCOBJSCALINGFallingPLATFORMMANAGER_H_
#define	_GCOBJSCALINGFallingPLATFORMMANAGER_H_

#ifndef MATH_VEC2_H
#include "cocos2d/cocos/math/Vec2.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif



//Brandon Middleton
//This class is for managing and drawing multiple falling platforms and grouping them together
//The way the class is designed can make it look like the platforms are scaled so its longer

class CGCObjScalingFallingPlatform;

class CGCObjScalingFallingPlatformManager
	: public CGCObjectGroup
{
private:


	CGCObjScalingFallingPlatform* m_pcGCScalingFallingPlatform;	//pointer to the default fallingplatform class

	int				m_iMaxPlatforms;							//sets how many platforms should spawn

	float m_fStartX;											//Start Positions
	float m_fStartY;											//Start Positions
	float m_fSpacingX;											//Spacing inbetween each platform on the x axis

	cocos2d::Vec2 m_v2PlatformStartPos;							//Start vec2


	void	CreatePlatforms ();									//Function to create  the platforms
	void	DestroyPlatforms ();								//Function to destroy the platforms

public:
	CGCObjScalingFallingPlatformManager ();						//Constructor
	virtual ~CGCObjScalingFallingPlatformManager () override;	//Deconstructor


	int		GetMaxPlatforms () { return m_iMaxPlatforms; };		//Getter and setter for the MaxPlatforms
	void	SetMaxPlatforms (int i) { m_iMaxPlatforms = i; }	//Getter and setter for the MaxPlatforms

	float 	GetStartX () { return m_fStartX; };					//Getter for StartX
	float 	GetStartY () { return m_fStartY; };					//Getter for StartY
	float 	GetSpacingX () { return m_fSpacingX; };				//Getter for SpacingX

	void	SetStartX (float i) {m_fStartX = i; }				//Setting for StartX
	void	SetStartY (float i) {m_fStartY = i; }				//Setting for StartY
	void	SetSpacingX (float i) { m_fSpacingX = i; }			//Setting for SpacingX

	cocos2d::Vec2 GetPlatformStartPos () const { return m_v2PlatformStartPos; }	//Getter and setter for the platform start pos	
	void	SetPlatformStartPos (cocos2d::Vec2 i) { m_v2PlatformStartPos = i; }	//Getter and setter for the platform start pos

	// overrides for CGCObjectGroup public interface

	// handles the platform
	virtual bool		VHandlesThisTypeId (GCTypeID idQueryType) override;		//Default functions needed
																				//Default functions needed
	virtual GCTypeID	VGetTypeId () override;									//Default functions needed
																				//Default functions needed
	virtual void		VOnGroupResourceAcquire () override;					//Default functions needed
	virtual void		VOnGroupResourceAcquire_PostObject () override;			//Default functions needed
	virtual void		VOnGroupReset () override;								//Default functions needed
	virtual void		VOnObjectReset () override;								//Default functions needed
	virtual void		VOnGroupUpdate (f32 fTimeStep) override;				//Default functions needed
	virtual void		VOnGroupResourceRelease () override;					//Default functions needed

};

#endif
