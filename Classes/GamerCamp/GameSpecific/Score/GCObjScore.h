#ifndef	_GCOBJSCORE_H_
#define	_GCOBJSCORE_H_

#include "2d/CCLabel.h"

class CGCObjScore
{
private:
	float m_fScoreTextSize;
	float m_fScoreTextStartPositionY;
	float m_fScoreTextStartPositionX;

	cocos2d::Label* m_pScoreText;

public:

	CGCObjScore();

	~CGCObjScore();

	cocos2d::Label* getScoreText() const { return m_pScoreText; }
	void setScoreText(cocos2d::Label* i) { m_pScoreText = i; }

	void IncreaseScore();

	void ResetScore();

	void Update();

};
#endif // #ifndef _GCOBJSCORE_H_
