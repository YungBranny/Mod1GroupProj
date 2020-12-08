#ifndef	_GCOBJHIGHSCORE_H_
#define	_GCOBJHIGHSCORE_H_

#include "2d/CCLabel.h"
#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

class CGCObjHighScore
{
private:
	float	m_fHighScoreTextSize;
	float	m_fHighScoreTextStartPositionY;
	float	m_fHighScoreTextStartPositionX;

	
	
	int	m_iHighScoreValue;

	float m_fCurrentScore;
	
	
	
	cocos2d::Label* m_pHighScoreText;

public:

	CGCObjHighScore(CGCObjScore* m_score);

	~CGCObjHighScore();
	
	void HighScoreReadFile(CGCObjScore* m_score);

	void HighScoreWriteFile(CGCObjScore* m_score);
	
	cocos2d::Label* getHighScoreText() const { return m_pHighScoreText; }
	void setHighScoreText(cocos2d::Label* i) { m_pHighScoreText = i; }

	int getHighScoreValue() const { return m_iHighScoreValue; }
	void setHighScoreValue(int i) { m_iHighScoreValue = i; }

	void ResetScore();

	void Update();

};
#endif // #ifndef _GCOBJSCORE_H_
