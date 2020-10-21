#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef	_GCOBJSCALINGBASICPLATFORMMANAGER_H_
#define	_GCOBJSCALINGBASICPLATFORMMANAGER_H_

#ifndef MATH_VEC2_H
	#include "cocos2d/cocos/math/Vec2.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
	#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif



//////////////////////////////////////////////////////////////////////////
// responsible for newing, managing, & deleting the invaders
//
// This shows how an object group can be used as an allocation pool.
//
//////////////////////////////////////////////////////////////////////////
class CGCObjScalingBasicPlatformManager
: public CGCObjectGroup
{
private:

	int				m_iMaxPlatforms	;



	cocos2d::Vec2	m_v2FormationOrigin; // origin of the formation

	float m_fStartX;
	float m_fStartY;
	float m_fSpacingX;

	cocos2d::Vec2 m_v2PlatformStartPos;


	void	CreatePlatforms		();
	void	DestroyPlatforms	();

public:
	CGCObjScalingBasicPlatformManager ();
	virtual ~CGCObjScalingBasicPlatformManager () override;


	int 	GetMaxPlatforms () { return m_iMaxPlatforms; };

	void SetMaxPlatforms (int i) { m_iMaxPlatforms = i; }

	float 	GetStartX () { return m_fStartX; };
	float 	GetStartY () { return m_fStartY; };
	float 	GetSpacingX () { return m_fSpacingX; };

	void SetStartX (float i) { m_fStartX = i; }
	void SetStartY (float i) { m_fStartY = i; }
	void SetSpacingX (float i) { m_fSpacingX = i; }

	cocos2d::Vec2 GetPlatformStartPos () const { return m_v2PlatformStartPos; }
	void SetPlatformStartPos (cocos2d::Vec2 i) { m_v2PlatformStartPos = i; }


	void SetFormationOrigin( cocos2d::Vec2 m_v2FormationOrigin );

	void SetColumns( int iNumColumns, f32 fPixelSpacingRow, f32 fPixelSpacingColumn );

//////////////////////////////////////////////////////////////////////////
// overrides for CGCObjectGroup public interface

	// handles GCObjInvader
	virtual bool		VHandlesThisTypeId					( GCTypeID idQueryType ) override;

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId							() override;

	virtual void		VOnGroupResourceAcquire				() override;
	virtual void		VOnGroupResourceAcquire_PostObject	() override;
	virtual void		VOnGroupReset						() override;
	virtual void		VOnObjectReset						() override;
	virtual void		VOnGroupUpdate						( f32 fTimeStep ) override;
	virtual void		VOnGroupResourceRelease				() override;
	// CGCObjectGroup public interface
//////////////////////////////////////////////////////////////////////////
};

#endif
