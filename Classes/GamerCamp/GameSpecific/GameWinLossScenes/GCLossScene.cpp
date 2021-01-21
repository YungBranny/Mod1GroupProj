#include "GCLossScene.h"

#include <algorithm>
#include <stdlib.h> 


#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"
#include "MenuScene.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCLevel1.h"


#include "AppDelegate.h"
#include "GamerCamp/GameSpecific/MainMenu/GCMainMenu.h"



CGCLossScene::CGCLossScene()
	: IGCGameLayer(GetGCTypeIDOf(CGCLossScene))
	, m_pcGCSprBackGround(nullptr) //Background Sprite
{

}


CGCLossScene::~CGCLossScene()
{

}


void CGCLossScene::onEnter()
{
	IGCGameLayer::onEnter();
}


void CGCLossScene::VOnCreate()
{
	//Get current screen size and origin
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// create the default object group
	IGCGameLayer::VOnCreate();

	
	//creating button so that the player can restart the game when they die
	cocos2d::MenuItemImage* pResetButton
		= cocos2d::MenuItemImage::create("TexturePacker/Sprites/MainMenu/Buttons/play_normal.png",
			"TexturePacker/Sprites/MainMenu/Buttons/play_pressed.png",
			CC_CALLBACK_1(CGCLossScene::Callback_OnResetButton, this));

	//setting position of the button on the menu
	pResetButton->setPosition(cocos2d::Vec2(((visibleSize.width * 0.25f)),
		((visibleSize.height - (pResetButton->getContentSize().height * 9.1f))))); // fix pressed button position


	//creating button so that the player can quit the game when they die
	cocos2d::MenuItemImage* pQuitItem
		= cocos2d::MenuItemImage::create("TexturePacker/Sprites/MainMenu/Buttons/exit_normal.png",
			"TexturePacker/Sprites/MainMenu/Buttons/exit_pressed",
			CC_CALLBACK_1(CGCLossScene::Callback_OnQuitButton, this));

	//setting position of the button on the menu
	pQuitItem->setPosition(cocos2d::Vec2(((visibleSize.width * 0.75f)),
		(((pQuitItem->getContentSize().height * 1.5) + origin.y + 0.0f))));

	// grouping the button and creating a menu, it's an autorelease object
	cocos2d::Menu* pMenu = cocos2d::Menu::create(pResetButton, pQuitItem, nullptr);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 1);




	// Making the background image, in the centre of the screen
	const char* pszPlist_background = "TexturePacker/Sprites/GameOver/game_over.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite();
		m_pcGCSprBackGround->CreateSprite(pszPlist_background);
		m_pcGCSprBackGround->SetResetPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
		m_pcGCSprBackGround->SetParent(IGCGameLayer::ActiveInstance());

	}
}



void CGCLossScene::VOnUpdate(f32 fTimeStep)
{
	IGCGameLayer::VOnUpdate(fTimeStep);

	if (ResetWasRequested())
	{
		VOnReset();
		ResetRequestWasHandled();
	}
}


void CGCLossScene::VOnDestroy()
{
	///////////////////////////////////////////////////////////////////////////
	// clean up anything we allocated in opposite order to creation

	IGCGameLayer::VOnDestroy();
}


///////////////////////////////////////////////////////////////////////////////
// on quit button
///////////////////////////////////////////////////////////////////////////////
void CGCLossScene::Callback_OnQuitButton(Ref* pSender)
{
	//Closes the game
	CCDirector::getInstance()->end();
}



///////////////////////////////////////////////////////////////////////////////
// on reset button
///////////////////////////////////////////////////////////////////////////////
void CGCLossScene::Callback_OnResetButton(Ref* pSender)
{
	//Replaces the scene with the first level again
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.1f, TGCGameLayerSceneCreator< CGCLevel1 >::CreateScene()));
}


///////////////////////////////////////////////////////////////////////////////
// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCLossScene::BeginContact(b2Contact* pB2Contact)
{
}


///////////////////////////////////////////////////////////////////////////////
// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCLossScene::EndContact(b2Contact* pB2Contact)
{
}