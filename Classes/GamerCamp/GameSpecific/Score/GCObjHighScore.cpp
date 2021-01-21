



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
	//gets the screen width and height
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//creating a label so the high score can be displayed
	Label* pLabel = Label::createWithTTF(" ", "fonts/Super Mario Bros. 2.ttf", m_fHighScoreTextSize);
	CC_ASSERT(pLabel != nullptr);
	setHighScoreText(pLabel);

	getHighScoreText()->setString("High Score: " + std::to_string(getHighScoreValue()));

	getHighScoreText()->setPosition(Vec2(m_fHighScoreTextStartPositionX, m_fHighScoreTextStartPositionY));


}

CGCObjHighScore::~CGCObjHighScore()
{

};

void CGCObjHighScore::HighScoreReadFile(CGCObjScore* m_score)
{

	std::ifstream readFile;
	//Opens the file
	readFile.open("HighScore.txt");

	if (readFile.is_open())
	{
		//inputs the value
		readFile >> m_iHighScoreValue;
	}
	readFile.close();

};

void CGCObjHighScore::HighScoreWriteFile(CGCObjScore* m_score)
{

	std::ofstream writeFile;
	//opens the file
	writeFile.open("HighScore.txt");
	
	if(writeFile.is_open())
	{
		//Making the highscore the current score
			m_iHighScoreValue = m_score->getScoreAmount();

			//inputs the value
			writeFile << m_iHighScoreValue;

		writeFile.close();
	}
		
		
}
	

void CGCObjHighScore::Update()
{
	//Pushing the highscore to the screen using to_string
	getHighScoreText()->setString("High Score: " + std::to_string(m_iHighScoreValue));
};