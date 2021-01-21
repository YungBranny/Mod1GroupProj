#include <string.h>
#include <fstream>

#include "GamerCamp/GameSpecific/GCLevel1.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "GCObjScore.h"

using namespace cocos2d;

CGCObjScore::CGCObjScore()
	: m_fScoreTextStartPositionX	( 200   ) // Mia: Sets the X position for the text
	, m_fScoreTextStartPositionY	( 1040  ) // Mia: Sets the Y position for the text
	, m_fScoreTextSize				( 20.0f ) // Mia: Sets the text size
	, m_iScoreAmount				( 0 )	  // Mia: Default Score amount is set to 0
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Super Mario Bros. 2.ttf", m_fScoreTextSize); // Mia: Sets font and calls text size
	CC_ASSERT(pLabel != nullptr);
	setScoreText( pLabel );

	getScoreText()->setString("Score: " + std::to_string(getScoreAmount())); // Mia: Creates string that shows Score amount, currently at default

	getScoreText()->setPosition(Vec2(m_fScoreTextStartPositionX, m_fScoreTextStartPositionY)); // Mia: Calls Score start positions to place it
}

CGCObjScore::~CGCObjScore()
{

};

void CGCObjScore::ScoreReadFile()
{
	std::ifstream readFile;
	readFile.open("Score.txt");

	if (readFile.is_open())
	{
  		readFile >> m_iScoreAmount;
		
	}
	readFile.close();
  
}

void CGCObjScore::ScoreWriteFile()
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
	m_iScoreAmount += 100; // Mia: Sets how much to increase Score by
	getScoreText()->setString("Score: " + std::to_string(getScoreAmount())); // Mia: Creates string that shows Score amount
};

void CGCObjScore::ResetScore()
{
	m_iScoreAmount = 0; // Mia: Resets Score back to 0 when called
};

void CGCObjScore::Update()
{
	getScoreText()->setString("Score: " + std::to_string(m_iScoreAmount)); // Mia: Keeps Score updated
};