#include <string.h>

#include "GamerCamp/GameSpecific/Score/GCObjScore.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"

using namespace cocos2d;

CGCObjScore::CGCObjScore()
	:CGCObjSprite(GetGCTypeIDOf(CGCObjScore))
	, m_fScoreTextStartPositionX(425)
	, m_fScoreTextStartPositionY(1000)
	, m_fScoreTextSize(30.0f)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	setScoreText(Label::createWithTTF(" ", "fonts/Pixeled.ttf", m_fScoreTextSize));

	getScoreText()->setString("Score ");

	getScoreText()->setPosition(Vec2(m_fScoreTextStartPositionX, m_fScoreTextStartPositionY));
}

CGCObjScore::~CGCObjScore()
{

};

void CGCObjScore::IncreaseScore()
{

};

void CGCObjScore::ResetScore()
{

};

void CGCObjScore::Update()
{

};