#ifndef	_GCOBJSCORE_H_
#define	_GCOBJSCORE_H_

#include "2d/CCLabel.h"
#include "GamerCamp/GameSpecific/Items/GCObjItem.h"
#include "../../GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "cocos2d/cocos/2d/CCSprite.h"

class CGCObjScore
	:CGCObjSprite
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
	void setScoreText(cocos2d::Label* t) { m_pScoreText = t; }

	void IncreaseScore();

	void ResetScore();

	void Update();

};
#endif // #ifndef _GCOBJSCORE_H_
