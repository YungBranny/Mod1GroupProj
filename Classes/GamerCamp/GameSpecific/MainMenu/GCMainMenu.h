#ifndef _MAINMENU_H_
#define _MAINMENU_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCMainMenu' Header File and Class File was created and was managed by Mehak Hussain.        //
// The purpose of this Class is to create the Main Menu used in our Game.                            //
// In this Class, I set up the buttons and sprites used for the Menu.                                //
///////////////////////////////////////////////////////////////////////////////////////////////////////

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