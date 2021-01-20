#include "GCMainMenu.h"

#include <algorithm>
#include <stdlib.h>

#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "AppDelegate.h"

CGCMainMenu::CGCMainMenu ()
	: IGCGameLayer ( GetGCTypeIDOf ( CGCMainMenu ) )
	, m_pcGCSprBackGround ( nullptr )
{

}

CGCMainMenu::~CGCMainMenu ()
{

}

void CGCMainMenu::onEnter ()
{
	IGCGameLayer::onEnter ();
}

void CGCMainMenu::VOnCreate ()
{
	cocos2d::Size visibleSize = cocos2d::Director::getInstance ()->getVisibleSize ();
	cocos2d::Point origin = cocos2d::Director::getInstance ()->getVisibleOrigin ();

	IGCGameLayer::VOnCreate ();

	cocos2d::MenuItemImage* pResetItem
		= cocos2d::MenuItemImage::create ("TexturePacker/Sprites/MainMenu/Buttons/play_normal.png",
			"TexturePacker/Sprites/MainMenu/Buttons/play_pressed.png",
			CC_CALLBACK_1 (CGCMainMenu::LoadLevel, this));

	pResetItem->setPosition (cocos2d::Vec2 (( ( visibleSize.width * 0.60f)),
	( ( visibleSize.height - ( pResetItem->getContentSize ().height * 5.5f ) ) )));

	cocos2d::MenuItemImage* pQuitItem
		= cocos2d::MenuItemImage::create ("TexturePacker/Sprites/MainMenu/Buttons/exit_normal.png",
			"TexturePacker/Sprites/MainMenu/Buttons/exit_pressed",
		CC_CALLBACK_1 (CGCMainMenu::QuitGame, this));

	pQuitItem->setPosition (cocos2d::Vec2 (( ( visibleSize.width * 0.60f ) ),
		( ( ( pQuitItem->getContentSize ().height * 2.0f ) + origin.y + 0.0f ) )));

	cocos2d::Menu* pMenu = cocos2d::Menu::create (pResetItem, pQuitItem, nullptr);
	pMenu->setPosition (cocos2d::Vec2::ZERO);
	this->addChild (pMenu, 1);

	cocos2d::Label* pLabel1 = cocos2d::Label::createWithTTF("Team 2: Mia, Brandon, Daniel, Puia and Johnny", "fonts/Super Mario Bros. 2.ttf", 10);

	pLabel1->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 1000));

	this->addChild(pLabel1, 1);

	const char* pszPlist_background = "TexturePacker/Sprites/MainMenu/Background/main_menu.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite ();
		m_pcGCSprBackGround->CreateSprite (pszPlist_background);
		m_pcGCSprBackGround->SetResetPosition (cocos2d::Vec2 (visibleSize.width / 2, visibleSize.height / 2));
		playMenuBackgroundMusic();
		m_pcGCSprBackGround->SetParent (IGCGameLayer::ActiveInstance ());
	}

	B2dGetWorld ()->SetContactListener (this);

	cocos2d::Vec2	v2ScreenCentre_Pixels (( origin.x + ( visibleSize.width * 0.5f ) ), ( origin.y + ( visibleSize.height * 0.5f ) ));
	cocos2d::Vec2	v2ScreenCentre_B2d = B2dPixelsToWorld (v2ScreenCentre_Pixels);

	f32 fScreenWidthB2d = B2dPixelsToWorld (visibleSize.width);
	f32 fHalfScreenWidthB2d = ( fScreenWidthB2d / 2.0f );

	f32 fScreenHeightB2d = B2dPixelsToWorld (visibleSize.height);
	f32 fHalfScreenHeightB2d = ( fScreenHeightB2d / 2.0f );

	new CGCObjScreenBound (CGCObjScreenBound::EScreenBoundType::Bottom, ( v2ScreenCentre_B2d + cocos2d::Vec2 (0.0f, -fHalfScreenHeightB2d) ), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound (CGCObjScreenBound::EScreenBoundType::Top, ( v2ScreenCentre_B2d + cocos2d::Vec2 (0.0f, fHalfScreenHeightB2d) ), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound (CGCObjScreenBound::EScreenBoundType::Left, ( v2ScreenCentre_B2d + cocos2d::Vec2 (-fHalfScreenWidthB2d, 0.0f) ), 0.5f, fScreenHeightB2d, 0.0f);
	new CGCObjScreenBound (CGCObjScreenBound::EScreenBoundType::Right, ( v2ScreenCentre_B2d + cocos2d::Vec2 (fHalfScreenWidthB2d, 0.0f) ), 0.5f, fScreenHeightB2d, 0.0f);
}

void CGCMainMenu::VOnDestroy ()
{
	IGCGameLayer::VOnDestroy ();
}

void CGCMainMenu::playMenuBackgroundMusic()
{
	m_pcGCMenuBackgroundAudio = CocosDenshion::SimpleAudioEngine::getInstance();
}

void CGCMainMenu::QuitGame (Ref* pSender)
{
	CCDirector::getInstance()->end ();
}

void CGCMainMenu::LoadLevel (Ref* pSender)
{
	Director::getInstance()->replaceScene (TransitionMoveInR::create (0.1f, TGCGameLayerSceneCreator< CGCGameLayerPlatformer >::CreateScene ()));
}