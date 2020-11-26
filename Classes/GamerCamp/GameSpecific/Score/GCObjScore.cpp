#include <string.h>

#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

using namespace cocos2d;

CGCObjScore::CGCObjScore()
	: m_fScoreTextStartPositionX(200)
	, m_fScoreTextStartPositionY(1020)
	, m_fScoreTextSize ( 20.0f)
	, m_iScoreAmount ( 0 )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Label* pLabel = Label::createWithTTF(" ", "fonts/Pixeled.ttf", m_fScoreTextSize);
	CC_ASSERT(pLabel != nullptr);
	setScoreText( pLabel );

	getScoreText()->setString("Score: " + std::to_string(getScoreAmount()));

	getScoreText()->setPosition(Vec2(m_fScoreTextStartPositionX, m_fScoreTextStartPositionY));
}

CGCObjScore::~CGCObjScore()
{

};

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

};