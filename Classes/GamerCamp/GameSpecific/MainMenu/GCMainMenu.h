#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"


class CGCObjSprite;

class CGCMainMenu
	: public IGCGameLayer
	, public b2ContactListener
{
private:


	CGCObjSprite* m_pcGCSprBackGround;


public:
	CGCMainMenu ();
	~CGCMainMenu ();


	void QuitGame (Ref* pSender);
	void LoadLevel (Ref* pSender);

	virtual void onEnter ();
	virtual	void VOnCreate (void);
	virtual	void VOnDestroy (void);


};



#endif