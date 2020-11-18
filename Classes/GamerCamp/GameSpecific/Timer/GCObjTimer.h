#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_

#include "2d/CCLabel.h"


#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

#include "cocos2d/cocos/2d/CCProgressTimer.h"
#include "cocos2d/cocos/2d/CCSprite.h"


namespace cocos2d {
}

class CGCObjTimer
	:CGCObjSprite
{
private:

	int m_iTotalTimerDuration; 
	int m_iCurrentTime;
	int m_iTimerDecreaseValue;
	int m_iTimerIncreaseValue;
	int m_iTimerTextOutlineSize;
	int m_iTimerBarHeightX;
	int m_iTimerBarHeightY;
	int m_iTimerBufferDecrease;
	float m_fCurrentTimeBuffer;
	float m_fMaxTimeBuffer;
	float m_fScaleX;
	float m_fScaleY;
	float m_fCurrentXScale;
	float m_fScaleDecreaseX;
	float m_fScaleDecreaseY;
	float m_fTimerTextFontSize;
	float m_fTimerBarStartPosY;
	float m_fTimerBarStartPosX;
	

	
	cocos2d::Label* m_pTimerText;

	cocos2d::ProgressTimer* m_TimerBar;

	cocos2d::Sprite* m_TimerBarSprite;

public:
	
	CGCObjTimer();

   ~CGCObjTimer();
	
   ///////////////////////////////////////////////////////////////////////////////
	
	int getTotalTimerDuration() const	  { return m_iTotalTimerDuration;   } 	//Getter and Setter for getting the Total timer duration
	void  setTotalTimerDuration(int f)	  { m_iTotalTimerDuration = f;      }	
																				
	int getCurrentTime() const			  { return  m_iCurrentTime;         }	//Getter and Setter for getting the current time
	void  setCurrentTime(int f)           { m_iCurrentTime = f;             }	
																				
	int getTimerDecreaseValue() const     { return m_iTimerDecreaseValue;   }	//Getter and Setter for getting the timer decrease amount 
	void setTimerDercreaseValue(int f)    { m_iTimerDecreaseValue = f;      }	
																				
	int getTimerIncreaseValue() const     { return m_iTimerIncreaseValue;   }	//Getter and Setter for getting the timer increase amount
	void setTimerIncreaseValue(int f)     { m_iTimerIncreaseValue = f;      }	
																				
	float getMaxTimeBuffer() const		  { return  m_fMaxTimeBuffer;       }	//Getter and Setter for Getting the maximum time buffer
	void setMaxTimeBuffer(float f)        { m_fMaxTimeBuffer = f;           }	
																				
	cocos2d::Label* getTimerText() const  { return m_pTimerText;			}	//Getter and Setter for getting the timer text component
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t;				}	

	cocos2d::ProgressTimer* getTimerBar() const { return m_TimerBar;		 }
	void setTimerBar(cocos2d::ProgressTimer* t) { m_TimerBar = t; }
	
	float getCurrentTimeBuffer() const	  { return m_fCurrentTimeBuffer;	}	//Getter and Setter for getting the current timer buffer
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

