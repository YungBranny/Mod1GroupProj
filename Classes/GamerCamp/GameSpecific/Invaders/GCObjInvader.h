////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GCOBJINVADER_H_
#define _GCOBJINVADER_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#endif

//////////////////////////////////////////////////////////////////////////
// This is a sample class derived from CGCObject.
// 
// It could be the basis of your invader object, it's up to you really.
//
//////////////////////////////////////////////////////////////////////////
class CGCObjInvader 
: public CGCObjSpritePhysics
{
private:

public:
	CGCObjInvader();

	//////////////////////////////////////////////////////////////////////////
	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types.
	virtual ~CGCObjInvader()
	{}

	//////////////////////////////////////////////////////////////////////////
	// overridden virtuals from the game object interface
	virtual void VOnResourceAcquire	( void ) override;

	virtual void VOnResurrected		( void ) override;

};
#endif // #ifndef _GCOBJINVADER_H_