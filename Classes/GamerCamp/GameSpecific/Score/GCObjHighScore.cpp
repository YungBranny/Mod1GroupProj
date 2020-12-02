



#include <string.h>
#include <fstream>



#include "GamerCamp/GameSpecific/Score/GCObjHighScore.h"
#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"



using namespace cocos2d;

CGCObjHighScore::CGCObjHighScore(CGCObjScore* m_score)
	: m_fHighScoreTextStartPositionX(200)
	, m_fHighScoreTextStartPositionY(1000)
	, m_fHighScoreTextSize(20.0f)
	, m_iHighScoreValue(0)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Super Mario Bros. 2.ttf", m_fHighScoreTextSize);
	CC_ASSERT(pLabel != nullptr);
	setHighScoreText(pLabel);

	getHighScoreText()->setString("High Score: " + std::to_string(getHighScoreValue()));

	getHighScoreText()->setPosition(Vec2(m_fHighScoreTextStartPositionX, m_fHighScoreTextStartPositionY));

	//HighScoreCheck(m_score);

	
	
}

CGCObjHighScore::~CGCObjHighScore()
{

};

void CGCObjHighScore::HighScoreCheckOpen(CGCObjScore* m_score)
{

	std::ifstream readFile;
	readFile.open("HighScore.txt");

	if (readFile.is_open())
	{
		readFile >> m_iHighScoreValue;
	}
	readFile.close();

};

void CGCObjHighScore::HighScoreCheckClose(CGCObjScore* m_score)
{

	std::ofstream writeFile;
	writeFile.open("HighScore.txt");
	
	if(writeFile.is_open())
	{
		
			m_iHighScoreValue = m_score->getScoreAmount();


			writeFile << m_iHighScoreValue;

		writeFile.close();
	}
		
		
}
	

//
//if (m_fCurrentScore > m_iHighScoreValue)
//{
//	std::ofstream writeFile("HighScore.txt");
//
//	if (writeFile.is_open())
//	{
//
//
//		m_iHighScoreValue = m_fCurrentScore;
//
//
//		writeFile << m_iHighScoreValue;
//
//	}
//	writeFile.close();
//}


void CGCObjHighScore::Update()
{
	getHighScoreText()->setString("High Score: " + std::to_string(m_iHighScoreValue));
};