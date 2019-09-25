////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2019
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef _GCINPUTCONTROLLER_H_
#define _GCINPUTCONTROLLER_H_

#ifndef _GCINPUTCONTROLLERMANAGER_H_
	#include "GamerCamp/GameController/GCControllerManager.h"
#endif

#include "GamerCamp/Core/GCTypes.h"

#include "platform/CCGLView.h"
#include "cocos2d/external/glfw3/include/win32/glfw3.h"
#include "cocos/base/CCController.h"



#if defined (WIN32)

using namespace cocos2d;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CGCController
{
public:
					CGCController					( CGCControllerManager::EControllerId eControllerId );
					~CGCController					();
	
	bool			IsActive						();	 // actually only inlined in the .cpp as definition isn't visible

	void			Reset							();

	bool			ButtonIsPressed					( Controller::Key eKeyCode );

	bool			ButtonHasJustBeenPressed		( Controller::Key eKeyCode );
	bool			ButtonHasJustBeenReleased		( Controller::Key eKeyCode );

	f32				GetCurrentAxisValueRaw			( Controller::Key eAxisKeyCode );
	f32				GetCurrentAxisDeadzoned			( Controller::Key eAxisKeyCode, float fDeadzone );

	cocos2d::Vec2	GetCurrentStickValueRaw			( Controller::Key eAxisKeyCodeX, Controller::Key eAxisKeyCodeY );
	cocos2d::Vec2	GetCurrentStickValueDeadzoned	( Controller::Key eAxisKeyCodeX, Controller::Key eAxisKeyCodeY, float fDeadzone );

private:

	CGCControllerManager::EControllerId m_eControllerId;

	CGCController();
};



#endif // #if defined (WIN32)
#endif // #ifndef _GCINPUTCONTROLLER_H_