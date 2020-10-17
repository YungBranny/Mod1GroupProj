#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"


class CGCObjSprite;

class CGCMainMenu
	: public IGCGameLayer
	, public b2ContactListener
{
private:

	bool m_bResetWasRequested;

	void RequestReset ()
	{
		m_bResetWasRequested = true;
	}

	void ResetRequestWasHandled ()
	{
		m_bResetWasRequested = false;
	}

	bool ResetWasRequested ()
	{
		return m_bResetWasRequested;
	}

	CGCObjSprite* m_pcGCSprBackGround;


public:
	CGCMainMenu ();
	~CGCMainMenu ();


	// 'selector' callbacks for menu buttons
	void Callback_OnQuitButton (Ref* pSender);
	void Callback_OnResetButton (Ref* pSender);

	// called from VOnUpdate
	//void ManuallyHandleCollisions (void);

	//////////////////////////////////////////////////////////////////////////
	// CCNode interface...
	virtual void onEnter ();
	// CCNode interface...
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface

	virtual	void VOnCreate (void);
	virtual void VOnUpdate (f32 fTimeStep);
	virtual	void VOnDestroy (void);

	// IGCGameLayer interface
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

	virtual void BeginContact (b2Contact* pB2Contact);
	virtual void EndContact (b2Contact* pB2Contact);
	//virtual void PreSolve (b2Contact* pB2Contact, const b2Manifold* pOldManifold);
	//virtual void PostSolve (b2Contact* pB2Contact, const b2ContactImpulse* pImpulse);

	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////// 
	// reset handling





};



#endif