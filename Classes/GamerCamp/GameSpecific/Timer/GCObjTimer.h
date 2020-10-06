#ifndef	_GCOBJTIMER_H_
#define	_GCOBJTIMER_H_

#ifndef	_GCOBJECTGROUP_H_
#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif
#include "2d/CCLabel.h"


///////////////////////////////////////////////////////////////////////////
// Forward Declare
class CGCObjSprite;



class CGCObjTimer
	: public CGCObjectGroup
{
private:

	float m_fTotalTimerDuration;
	float m_fCurrentTime;
	float m_fTimerDecreaseValue;

	
	cocos2d::Label* pTimerText;
	
	
	

public:

	
	float getTotalTimerDuration()        { return m_fTotalTimerDuration;   };
	void  setTotalTimerDuration(float f) { m_fTotalTimerDuration = f;      };

	float getCurrentTime()               { return  m_fCurrentTime;         };
	void  setCurrentTime(float f)        { m_fCurrentTime = f;             };

	/*cocos2d::Label* getTimerText()       { return pTimerText; }
	void setTimerText(cocos2d::Label*  t) { pTimerText = t; };*/


	
	CGCObjTimer();

	   ~CGCObjTimer();
	
//
////////////////////////////////////////////////////////////////////////////
//// overrides for CGCObjectGroup public interface
//
//
//	// must return the typeid of the CGCObjectGroup derived class
//	virtual GCTypeID	VGetTypeId() override;
//
//	virtual void		VOnGroupResourceAcquire() override;
//	virtual void		VOnGroupResourceAcquire_PostObject() override;
//	virtual void		VOnGroupReset() override;
//	virtual void		VOnObjectReset() override;
//	virtual void		VOnGroupUpdate(f32 fTimeStep) override;
//	virtual void		VOnGroupResourceRelease() override;
//	// CGCObjectGroup public interface
////////////////////////////////////////////////////////////////////////////

	
};
#endif // #ifndef _GCOBJTIMER_H_

