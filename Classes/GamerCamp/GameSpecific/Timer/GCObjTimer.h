#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_
#include "2d/CCLabel.h"


///////////////////////////////////////////////////////////////////////////
// Forward Declare
class CGCObjSprite;



class CGCObjTimer
{
private:

	float m_fTotalTimerDuration;
	float m_fCurrentTime;
	float m_fTimerDecreaseValue;
	float m_fTimeBuffer;

	


	cocos2d::Label* m_pTimerText;

public:

	
	float getTotalTimerDuration()        { return m_fTotalTimerDuration;   };
	void  setTotalTimerDuration(float f) { m_fTotalTimerDuration = f;      };

	float getCurrentTime()               { return  m_fCurrentTime;         };
	void  setCurrentTime(float f)        { m_fCurrentTime = f;             };

	float getTimerDecreaseValue()        { return m_fTimerDecreaseValue;   };
	void setTimerDercreaseValue(float f) { m_fTimerDecreaseValue = f;      };

	float getTimeBuffer()                { return  m_fTimeBuffer;          };
	void setTimeBuffer(float f)          { m_fTimeBuffer = f;              };

	cocos2d::Label* getTimerText()       { return m_pTimerText; }
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t; };

	void DecreaseTimer();
	
	void Update();

	void ResetTimer();
	
	
	CGCObjTimer();

   ~CGCObjTimer();
	
};
#endif // #ifndef _GCOBJTIMER_H_

