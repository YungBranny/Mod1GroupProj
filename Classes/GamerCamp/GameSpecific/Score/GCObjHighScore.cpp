



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
	, m_iHighScoreValue(m_score->getScoreAmount())
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Pixeled.ttf", m_fHighScoreTextSize);
	CC_ASSERT(pLabel != nullptr);
	setHighScoreText(pLabel);

	getHighScoreText()->setString("High Score: " + std::to_string(getHighScoreValue()));

	getHighScoreText()->setPosition(Vec2(m_fHighScoreTextStartPositionX, m_fHighScoreTextStartPositionY));

	HighScoreCheck(m_score);

	m_fCurrentScore = m_score->getScoreAmount();
}

CGCObjHighScore::~CGCObjHighScore()
{

};

void CGCObjHighScore::HighScoreCheck(CGCObjScore* m_score)
{
	/* std::ifstream input("HighScore.plist");
	if(!input.is_open())
	{
		CCLOG("Can't read text file");
		return;
	}

	 input >> m_iHighScoreValue;

	 std::ofstream output("HighScore.plist");
	 if (!output.is_open())
	 {
		 CCLOG("Can't read text file");
		 return;
	 }

	if(m_fCurrentScore > m_iHighScoreValue)
	{
		output << m_fCurrentScore;
	} else
	{
		output << m_iHighScoreValue;
	}*/



	
	
	//std::ifstream inFile;
	//inFile.open("HighScore.txt");

	//	 std::fstream readFile ("HighScore.xml",std::ios::in);
	//	 std::string line;
	//	 //readFile.open("GamerCamp/GameSpecific/Score/HighScore.txt");
	//
	// 	if(readFile.is_open())
	// 	{
	//		getline(readFile, line);
	// 		
	// 		while ( !readFile.eof())
	//			{
	//			readFile >> m_iHighScoreValue;
	//			}
	// 	}
	//
	//	readFile.close();
	//
	//	std::ofstream writeFile("Loose/HighScore.txt");
	//
	// 	if(writeFile.is_open())
	// 	{
	// 		if ( m_score->getScoreAmount() > m_iHighScoreValue)
	// 		{
	//			m_iHighScoreValue = m_score->getScoreAmount();
	// 		}
	//
	//		writeFile << m_iHighScoreValue;
	// 		
	// 	}
	//	writeFile.close();
	//

	//
	//UserDefault* default = UserDefault::getInstance();

	// auto HighScore = default->getIntegerForKey("HIGHSCORE", 0);

 //	if ( m_score->getScoreAmount() > HighScore)
 //	{
	//	HighScore = m_score->getScoreAmount();

	//	default->setIntegerForKey("HIGHSCORE", HighScore);
 //	}

	//default->flush();
	// 	
	//
 //   getHighScoreText()->setString("High Score: " + std::to_string(getHighScoreValue()));

};



void CGCObjHighScore::Update()
{
	
};