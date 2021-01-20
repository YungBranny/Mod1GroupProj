#ifndef	_GCOBJSCORE_H_
#define	_GCOBJSCORE_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjScore' Header File and Class File was created by Mehak Hussain.						//
// The purpose of this Class is to create the Score that keeps track of how many points the Player  //
// had accumulated.																				    //
// In this Class, I set the Scores text, position and setting how the score increases.              //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "2d/CCLabel.h"

class CGCObjScore
{
private:
	float	m_fScoreTextSize; // Mia: Float for Score text size
	float	m_fScoreTextStartPositionY; // Mia: Float for Score text Y start position
	float	m_fScoreTextStartPositionX; // Mia: Float for Score text X start position

	int		m_iScoreAmount; // Mia: Int for Score amount

	cocos2d::Label* m_pScoreText; // Mia: Variable for Score text

public:

	CGCObjScore();
	~CGCObjScore();

	cocos2d::Label* getScoreText() const { return m_pScoreText; }
	void setScoreText(cocos2d::Label* i) { m_pScoreText = i; }

	int getScoreAmount() const { return m_iScoreAmount; }
	void setScoreAmount(int i) { m_iScoreAmount = i; }

	void ScoreReadFile(CGCObjScore* m_score);
							
	void ScoreWriteFile(CGCObjScore* m_score);

	void ScoreClearFile(CGCObjScore* m_score);

	void IncreaseScore();

	void ResetScore();

	void Update();
};
#endif // _GCOBJSCORE_H_
