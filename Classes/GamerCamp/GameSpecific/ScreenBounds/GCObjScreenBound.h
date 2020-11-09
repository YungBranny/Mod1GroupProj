////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJSCREENBOUND_H_
#define _GCOBJSCREENBOUND_H_

#include "../../GCCocosInterface/GCObjSpritePhysics.h"

class CGCObjScreenBound
: public CGCObjSpritePhysics
{
public:

	enum EScreenBoundType
	{
		Left,
		Right,
		Top,
		Bottom,
	};

	CGCObjScreenBound( EScreenBoundType eBoundType, cocos2d::Vec2 v2Position, f32 fWidth, f32 fHeight, f32 fAngle);

	EScreenBoundType GetScreenBoundType() const { return m_eBoundType; }

	// screen bounds have no sprite & don't use the standard "create from predefined shape" approach to make their body
	// so we need to subvert the base class behaviours in GCObjSpritePhysics to just allow them to collide
	virtual void VOnResourceAcquire		()							override;
	virtual void VOnReset				()							override;
	virtual void VOnUpdate				( float fTimeStep )			override;
	virtual void VOnResourceRelease		()							override;
	virtual void VOnKilled				()							override;
	virtual void VOnResurrected			()							override;
	virtual void VUpdateSpriteFromBody	( const b2Body* pcb2Body )	override;

private:
	EScreenBoundType	m_eBoundType;
	b2Body*				m_pb2ScreenBoundBody;
	b2PolygonShape		m_b2ScreenBoundShape;
};


#endif
