#include <string.h>
#include <fstream>

#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

using namespace cocos2d;

CGCObjScore::CGCObjScore()
	: m_fScoreTextStartPositionX(200) //Sets the X position for the text
	, m_fScoreTextStartPositionY(1040) //Sets the Y position for the text
	, m_fScoreTextSize (20.0f)
	, m_iScoreAmount ( 0 )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Super Mario Bros. 2.ttf", m_fScoreTextSize);
	CC_ASSERT(pLabel != nullptr);
	setScoreText( pLabel );

	getScoreText()->setString("Score: " + std::to_string(getScoreAmount()));

	getScoreText()->setPosition(Vec2(m_fScoreTextStartPositionX, m_fScoreTextStartPositionY));
}

CGCObjScore::~CGCObjScore()
{

};

void CGCObjScore::ScoreReadFile(CGCObjScore* m_score)
{
	std::ifstream readFile;
	readFile.open("Score.txt");

	if (readFile.is_open())
	{
		readFile >> m_iScoreAmount;
	}
	readFile.close();
  
}

void CGCObjScore::ScoreWriteFile(CGCObjScore* m_score)
{


	std::ofstream writeFile;
	writeFile.open("Score.txt");

	if (writeFile.is_open())
	{

		writeFile << m_iScoreAmount;

		writeFile.close();
	}



}


void CGCObjScore::ScoreClearFile(CGCObjScore* m_score)
{


	std::ofstream writeFile;
	writeFile.open("Score.txt");

	if (writeFile.is_open())
	{

		writeFile << 0;

		writeFile.close();
	}

}

void CGCObjScore::IncreaseScore()
{
	m_iScoreAmount += 100;
	getScoreText()->setString("Score: " + std::to_string(getScoreAmount()));
};

void CGCObjScore::ResetScore()
{
	m_iScoreAmount = 0;
};

void CGCObjScore::Update()
{
	getScoreText()->setString("Score: " + std::to_string(m_iScoreAmount));
};