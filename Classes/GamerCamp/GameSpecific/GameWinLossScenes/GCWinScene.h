#ifndef _GCWINSCENE_H_
#define _GCWINSCENE_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"


class CGCObjSprite;

class CGCWinScene
	: public IGCGameLayer
	, public b2ContactListener
{
private:

	bool m_bResetWasRequested;

	void RequestReset()
	{
		m_bResetWasRequested = true;
	}

	void ResetRequestWasHandled()
	{
		m_bResetWasRequested = false;
	}

	bool ResetWasRequested()
	{
		return m_bResetWasRequested;
	}

	CGCObjSprite* m_pcGCSprBackGround;


public:
	CGCWinScene();
   ~CGCWinScene();

   //////////////////////////////////////////////////////////////////////////

	// 'selector' callbacks for menu buttons
	void Callback_OnQuitButton(Ref* pSender);
	void Callback_OnResetButton(Ref* pSender);

	

	//////////////////////////////////////////////////////////////////////////
	// Default functions
	
	virtual void onEnter();
	virtual	void VOnCreate(void);
	virtual void VOnUpdate(f32 fTimeStep);
	virtual	void VOnDestroy(void);

	
	//////////////////////////////////////////////////////////////////////////
	//Here if collision is required

	virtual void BeginContact(b2Contact* pB2Contact);
	virtual void EndContact(b2Contact* pB2Contact);
	





};



#endif