#ifndef _GCLOSSSCENE_H_
#define _GCLOSSSCENE_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"


class CGCObjSprite;

class CGCLossScene
	: public IGCGameLayer
	, public b2ContactListener
{
private:

	bool m_bResetWasRequested; //Reset

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

	CGCObjSprite* m_pcGCSprBackGround;// background sprite


public:
	
	CGCLossScene();
   ~CGCLossScene();
   //////////////////////////////////////////////////////////////////////////

	//Buttons on the Menu
	void Callback_OnQuitButton(Ref* pSender);
	void Callback_OnResetButton(Ref* pSender);


	//////////////////////////////////////////////////////////////////////////
	
	virtual void onEnter();
	virtual	void VOnCreate(void);
	virtual void VOnUpdate(f32 fTimeStep);
	virtual	void VOnDestroy(void);

	//////////////////////////////////////////////////////////////////////////
	//if collisions are needed
	
	virtual void BeginContact(b2Contact* pB2Contact);
	virtual void EndContact(b2Contact* pB2Contact);
	
	//////////////////////////////////////////////////////////////////////////
};



#endif