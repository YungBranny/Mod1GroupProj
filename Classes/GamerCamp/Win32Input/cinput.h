//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef _CINPUT_H_
#define _CINPUT_H_
#include "GamerCamp/Core/GCTypes.h"

#include "platform/CCGLView.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListenerKeyboard.h"


//////////////////////////////////////////////////////////////////////////
#if defined (WIN32)

	class CInput
	{
	public:
		CInput	(void);
		~CInput	(void);

		enum
		{
			// N.B. KEY_PLAY is the last value in the enum at time of writing
			EKeyBufferSize = ( ((int) cocos2d::EventKeyboard::KeyCode::KEY_PLAY ) + 1 ),
		};

		void			Reset		( void );
		void			Update		( void );
		bool			KeyIsPressed( cocos2d::EventKeyboard::KeyCode eKeyCode );

	private:
		bool							m_abKeyBufferWrite	[ EKeyBufferSize ];
		bool							m_abKeyBufferRead	[ EKeyBufferSize ];
		cocos2d::EventListenerKeyboard*	m_pcKeyboardListener;
	};

#else

	class CInput
	{
	public:
		CInput	(void) {}
		~CInput	(void) {}

		void			Reset		( void ) {}
		void			Update		( void ) {}
		bool			KeyIsPressed( cocos2d::EventKeyboard::KeyCode eKeyCode ) { return false; }
	};


#endif // #if defined (WIN32)
#endif // #ifndef _CINPUT_H_