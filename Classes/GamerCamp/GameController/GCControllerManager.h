////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2019
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef _CINPUTCONTROLLER_H_
#define _CINPUTCONTROLLER_H_
#include "GamerCamp/Core/GCTypes.h"

#include "platform/CCGLView.h"
#include "cocos/base/CCController.h"

#include "base/CCEventKeyboard.h"
#include "base/CCEventListenerKeyboard.h"


//////////////////////////////////////////////////////////////////////////
#error read comment below!!
//					PLAN
//					
// * get this working passing the explicit controller ID to CC code from gameplay code
// 
// * once working add a controller class which wraps the ID and which calls the right functions on GCControllerManager
// 
// * MAYBE, IF THERE'S TIME!
// 
//	 * add a listener to listen to connect / disconnect messages
//			* cache connected Controllers 
//			* use a handle to access the controllers (index into std::vec of Controller* plus controller connection counter should do it...)
//				int					m_iConnectionCount;					// starts at 1, ticks up with each connection
//				std::vector< int >	m_vecControllerIDs; 				// stores controller ID in 1st free index
//				std::vector< int >	m_vecCorrespondingConnectionCounts; // stores m_iConnectionCount at same index the newly connected controllerId is stored at
//																																								 
//				* handle is index into these two arrays plus connection count at creation to check handle is still valid (since the controller could connect / disconnect)
//				
//			* DO NOT OVER ENGINEER! JUST BRUTE FORCE SEARCH FOR A FREE INDEX!
//		
#if defined (WIN32)

using namespace cocos2d;

class GCControllerManager
{
public:
	GCControllerManager											();
	~GCControllerManager										();

	void				Reset									();
	void				Update									();

	bool				ControllerIsActive						( i32 iControllerID );

	bool				ControllerButtonIsPressed				( i32 iControllerID, Controller::Key eKeyCode );

	bool				ControllerButtonHasJustBeenPressed		( i32 iControllerID, Controller::Key eKeyCode );
	bool				ControllerButtonHasJustBeenReleased		( i32 iControllerID, Controller::Key eKeyCode );

	f32					ControllerGetCurrentAxisValueRaw		( i32 iControllerID, Controller::Key eAxisKeyCode );
	f32					ControllerGetCurrentAxisDeadzoned		( i32 iControllerID, Controller::Key eAxisKeyCode, float fDeadzone );

	cocos2d::Vec2		ControllerGetCurrentStickValueRaw		( i32 iControllerID, Controller::Key eAxisKeyCodeX, Controller::Key eAxisKeyCodeY );
	cocos2d::Vec2		ControllerGetCurrentStickValueDeadzoned ( i32 iControllerID, Controller::Key eAxisKeyCodeX, Controller::Key eAxisKeyCodeY, float fDeadzone );


private:

	cocos2d::EventListenerController*	m_pcControllerListener;
};



#endif // #if defined (WIN32)
#endif // #ifndef _CINPUTCONTROLLER_H_