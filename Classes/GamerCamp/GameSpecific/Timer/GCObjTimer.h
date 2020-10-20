#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_

#include "2d/CCLabel.h"


#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"



class CGCObjTimer
	:CGCObjSprite
{
private:

	int m_iTotalTimerDuration; 
	int m_iCurrentTime;
	int m_iTimerDecreaseValue;
	int m_iTimerIncreaseValue;
	float m_fCurrentTimeBuffer;
	float m_fMaxTimeBuffer;
	float m_fScaleX;
	float m_fCurrentXScale;
	float m_fScaleDecreaseX;
	float m_fScaleDecreaseY;

	cocos2d::Label* m_pTimerText;

public:
	
	CGCObjTimer();

   ~CGCObjTimer();
	
	
	int getTotalTimerDuration() const	  { return m_iTotalTimerDuration;   } 
	void  setTotalTimerDuration(int f)	  { m_iTotalTimerDuration = f;      }

	int getCurrentTime() const			  { return  m_iCurrentTime;         }
	void  setCurrentTime(int f)           { m_iCurrentTime = f;             }

	int getTimerDecreaseValue() const     { return m_iTimerDecreaseValue;   }
	void setTimerDercreaseValue(int f)    { m_iTimerDecreaseValue = f;      }

	int getTimerIncreaseValue() const     { return m_iTimerIncreaseValue;   }
	void setTimerIncreaseValue(int f)     { m_iTimerIncreaseValue = f;      }

	float getMaxTimeBuffer() const		  { return  m_fMaxTimeBuffer;       }
	void setMaxTimeBuffer(float f)        { m_fMaxTimeBuffer = f;           }

	cocos2d::Label* getTimerText() const  { return m_pTimerText;			}
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t;				}

	float getCurrentTimeBuffer() const	  { return m_fCurrentTimeBuffer;	}
	void setCurrentTimeBuffer(float f)	  { m_fCurrentTimeBuffer = f;		}

	//virtual void VOnResourceAcquire(void) override;

	///////////////////////////////////////////////////////////////////////////////
	
	void DecreaseTimer();
	
	void ResetTimer();

	void ClampTimer();
	
	///////////////////////////////////////////////////////////////////////////////
	

	void Update();
	
	
	
};
#endif // #ifndef _GCOBJTIMER_H_

