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

	float m_fTotalTimerDuration; 
	float m_fCurrentTime;
	float m_fTimerDecreaseValue;
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
	float m_fTimerBarSpeedDecrease;
	float m_fTimerBarMidPoint;
	

	
	cocos2d::Label* m_pTimerText;

	cocos2d::ProgressTimer* m_TimerBar;

	cocos2d::Sprite* m_TimerBarSprite;

	cocos2d::Sprite* m_UI_TimerBorder;

public:
	
	CGCObjTimer();

   ~CGCObjTimer();
	
   ///////////////////////////////////////////////////////////////////////////////
	
	float getTotalTimerDuration() const	  { return m_fTotalTimerDuration;   } 	//Getter and Setter for getting the Total timer duration
	void  setTotalTimerDuration(float f)	  { m_fTotalTimerDuration = f;      }	
																				
	float getCurrentTime() const			  { return  m_fCurrentTime;         }	//Getter and Setter for getting the current time
	void  setCurrentTime(float f)           { m_fCurrentTime = f;             }	
																				
	float getTimerDecreaseValue() const     { return m_fTimerDecreaseValue;   }	//Getter and Setter for getting the timer decrease amount 
	void setTimerDercreaseValue(float f)    { m_fTimerDecreaseValue = f;      }	
																				
	int getTimerIncreaseValue() const     { return m_iTimerIncreaseValue;   }	//Getter and Setter for getting the timer increase amount
	void setTimerIncreaseValue(int f)     { m_iTimerIncreaseValue = f;      }	
																				
	float getMaxTimeBuffer() const		  { return  m_fMaxTimeBuffer;       }	//Getter and Setter for Getting the maximum time buffer
	void setMaxTimeBuffer(float f)        { m_fMaxTimeBuffer = f;           }	
																				
	cocos2d::Label* getTimerText() const  { return m_pTimerText;			}	//Getter and Setter for getting the timer text component
	void setTimerText(cocos2d::Label*  t) { m_pTimerText = t;				}	

	cocos2d::ProgressTimer* getTimerBar() const { return m_TimerBar;		}
	void setTimerBar(cocos2d::ProgressTimer* t) { m_TimerBar = t;			}

	cocos2d::Sprite* getTimerBarUI() const { return m_UI_TimerBorder;		}
	void setTimerBarUI(cocos2d::Sprite* t) { m_UI_TimerBorder = t;			}
	
	float getCurrentTimeBuffer() const	  { return m_fCurrentTimeBuffer;	}	//Getter and Setter for getting the current timer buffer
	void setCurrentTimeBuffer(float f)	  { m_fCurrentTimeBuffer = f;		}	

	//virtual void VOnResourceAcquire(void) override;

	///////////////////////////////////////////////////////////////////////////////
	
	void DecreaseTimer( f32 fTimeStep);
	
	void ResetTimer();

	void ClampTimer();

	virtual void VOnReset(void);
	
	///////////////////////////////////////////////////////////////////////////////
	

	void Update(f32 fTimeStep);
	
	
	
};
#endif // #ifndef _GCOBJTIMER_H_

