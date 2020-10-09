#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_

#include "2d/CCLabel.h"


#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"



class CGCObjTimer
	/*:CGCObjSprite*/
{
private:

	int m_fTotalTimerDuration;
	int m_fCurrentTime;
	int m_fTimerDecreaseValue;
	float m_fCurrentTimeBuffer;
	float m_fMaxTimeBuffer;

	cocos2d::Label* m_pTimerText;

	

public:

	/*CGCObjSprite* m_pcGCOTimerBar;*/
	
	int getTotalTimerDuration()			  { return m_fTotalTimerDuration;   }
	void  setTotalTimerDuration(int f)	  { m_fTotalTimerDuration = f;      }

	int getCurrentTime()				  { return  m_fCurrentTime;         }
	void  setCurrentTime(int f)           { m_fCurrentTime = f;             }

	int getTimerDecreaseValue()           { return m_fTimerDecreaseValue;   }
	void setTimerDercreaseValue(int f)    { m_fTimerDecreaseValue = f;      }

	float getMaxTimeBuffer()              { return  m_fMaxTimeBuffer;       }
	void setMaxTimeBuffer(float f)        { m_fMaxTimeBuffer = f;           }

	cocos2d::Label* getTimerText()        { return m_pTimerText;			}
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t;				}

	float getCurrentTimeBuffer()		  { return m_fCurrentTimeBuffer;	}
	void setCurrentTimeBuffer(float f)	  { m_fCurrentTimeBuffer = f;		}

	//CGCObjSprite* getTimerBar()			  { return m_pcGCOTimerBar;			}
	//void setTimerBar(CGCObjSprite* t)     { m_pcGCOTimerBar = t;		    }


	/*virtual void VOnResourceAcquire(void) override;*/
	
	void DecreaseTimer();
	
	void Update();

	void ResetTimer();
	
	
	CGCObjTimer();

   ~CGCObjTimer();
	
};
#endif // #ifndef _GCOBJTIMER_H_

