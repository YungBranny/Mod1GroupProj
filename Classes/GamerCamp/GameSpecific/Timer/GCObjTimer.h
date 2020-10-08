#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_
#include "2d/CCLabel.h"


///////////////////////////////////////////////////////////////////////////
// Forward Declare
class CGCObjSprite;



class CGCObjTimer
{
private:

	int m_fTotalTimerDuration;
	int m_fCurrentTime;
	int m_fTimerDecreaseValue;
	float m_fTimeBuffer;

	


	cocos2d::Label* m_pTimerText;

public:

	
	int getTotalTimerDuration()        { return m_fTotalTimerDuration;   }
	void  setTotalTimerDuration(int f) { m_fTotalTimerDuration = f;      }

	int getCurrentTime()               { return  m_fCurrentTime;         }
	void  setCurrentTime(int f)        { m_fCurrentTime = f;             }

	int getTimerDecreaseValue()        { return m_fTimerDecreaseValue;   }
	void setTimerDercreaseValue(int f) { m_fTimerDecreaseValue = f;      }

	float getTimeBuffer()                { return  m_fTimeBuffer;          };
	void setTimeBuffer(float f)          { m_fTimeBuffer = f;              };

	cocos2d::Label* getTimerText()       { return m_pTimerText; }
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t; }

	void DecreaseTimer();
	
	void Update();

	void ResetTimer();
	
	
	CGCObjTimer();

   ~CGCObjTimer();
	
};
#endif // #ifndef _GCOBJTIMER_H_

