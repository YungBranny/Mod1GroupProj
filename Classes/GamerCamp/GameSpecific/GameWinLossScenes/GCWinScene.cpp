#include "GCWinScene.h"

#include <algorithm>
#include <stdlib.h> 


#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"
#include "MenuScene.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"

#include "AppDelegate.h"




CGCWinScene::CGCWinScene()
	: IGCGameLayer(GetGCTypeIDOf(CGCWinScene))
	, m_pcGCSprBackGround(nullptr)
{

}


CGCWinScene::~CGCWinScene()
{

}


void CGCWinScene::onEnter()
{
	IGCGameLayer::onEnter();
}


void CGCWinScene::VOnCreate()
{
	///////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	///////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	///////////////////////////////////////////////////////////////////////////
	// default object group
	///////////////////////////////////////////////////////////////////////////

	// create the default object group
	IGCGameLayer::VOnCreate();


	///////////////////////////////////////////////////////////////////////////
	// custom object groups
	//
	// N.B. Cannot do this in CGCObjectGroup internally on construction, 
	// because ObjectGroupRegister calls a virtual function 
	// in the CGCObjectManager interface to check the 
	// types of objects that the group handles
	///////////////////////////////////////////////////////////////////////////

	// create and register the object group for the platform objects


	// create and register the object group for the item objects


	// create and register the object group for the invader objects
	//m_pcGCGroupInvader = new CGCObjGroupInvader( 64 );
	//CGCObjectManager::ObjectGroupRegister( m_pcGCGroupInvader );

	// create and register the object group for the player projectile objects






	///////////////////////////////////////////////////////////////////////////
	// add menu
	///////////////////////////////////////////////////////////////////////////

	// add a "close" icon to exit the progress. it's an autorelease object
	cocos2d::MenuItemImage* pResetItem
		= cocos2d::MenuItemImage::create("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1(CGCWinScene::Callback_OnResetButton, this));

	pResetItem->setPosition(cocos2d::Vec2(((visibleSize.width - (pResetItem->getContentSize().width * 0.5f)) + origin.x),
		(((pResetItem->getContentSize().height * 0.5f) + origin.y))));

	cocos2d::MenuItemImage* pQuitItem
		= cocos2d::MenuItemImage::create("Loose/CloseNormal.png",
			"Loose/CloseSelected.png",
			CC_CALLBACK_1(CGCWinScene::Callback_OnQuitButton, this));

	pQuitItem->setPosition(cocos2d::Vec2(((visibleSize.width - (pQuitItem->getContentSize().width * 0.5f)) + origin.x),
		((visibleSize.height - (pQuitItem->getContentSize().height * 0.5f)) + origin.y)));

	// create menu, it's an autorelease object
	cocos2d::Menu* pMenu = cocos2d::Menu::create(pResetItem, pQuitItem, nullptr);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 1);

	//////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// add label
	///////////////////////////////////////////////////////////////////////////

	// create and initialize a label
	cocos2d::Label* pLabel = cocos2d::Label::createWithTTF("Winner!", "fonts/arial.ttf", 100);

	// position the label on the center of the screen
	pLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height - 50));
	
	pLabel->setColor(Color3B::MAGENTA);
	
	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	const char* pszPlist_background = "TexturePacker/Backgrounds/Placeholder/background.plist";
	{
		m_pcGCSprBackGround = new CGCObjSprite();
		m_pcGCSprBackGround->CreateSprite(pszPlist_background);
		m_pcGCSprBackGround->SetResetPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
		m_pcGCSprBackGround->SetParent(IGCGameLayer::ActiveInstance());

	}


	///////////////////////////////////////////////////////////////////////////
	// set up physics 
	///////////////////////////////////////////////////////////////////////////

	// set "self" as contact listener
	B2dGetWorld()->SetContactListener(this);

	// load the physics shapes from the plist created with PhysicsEditor
	B2dLoadShapesFromPlist("PhysicsEditor/GameShapes.plist");


	///////////////////////////////////////////////////////////////////////////
	// add screen bounds - note these are now derived from CGCObjSpritePhysics
	// this is to allow callback based collision handling with them etc.
	///////////////////////////////////////////////////////////////////////////
	cocos2d::Vec2	v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));
	cocos2d::Vec2	v2ScreenCentre_B2d = B2dPixelsToWorld(v2ScreenCentre_Pixels);

	f32 fScreenWidthB2d = B2dPixelsToWorld(visibleSize.width);
	f32 fHalfScreenWidthB2d = (fScreenWidthB2d / 2.0f);

	f32 fScreenHeightB2d = B2dPixelsToWorld(visibleSize.height);
	f32 fHalfScreenHeightB2d = (fScreenHeightB2d / 2.0f);

	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Bottom, (v2ScreenCentre_B2d + cocos2d::Vec2(0.0f, -fHalfScreenHeightB2d)), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Top, (v2ScreenCentre_B2d + cocos2d::Vec2(0.0f, fHalfScreenHeightB2d)), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Left, (v2ScreenCentre_B2d + cocos2d::Vec2(-fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Right, (v2ScreenCentre_B2d + cocos2d::Vec2(fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);


}// void CGCGameLayerPlatformer::VOnCreate() { ...


//////////////////////////////////////////////////////////////////////////
// on update
//////////////////////////////////////////////////////////////////////////
//virtual

void CGCWinScene::VOnUpdate(f32 fTimeStep)
{
	IGCGameLayer::VOnUpdate(fTimeStep);

	// this shows how to iterate and respond to the box2d collision info


	if (ResetWasRequested())
	{
		VOnReset();
		ResetRequestWasHandled();
	}
}


void CGCWinScene::VOnDestroy()
{
	///////////////////////////////////////////////////////////////////////////
	// clean up anything we allocated in opposite order to creation

	IGCGameLayer::VOnDestroy();
}


///////////////////////////////////////////////////////////////////////////////
// on quit button
///////////////////////////////////////////////////////////////////////////////
void CGCWinScene::Callback_OnQuitButton(Ref* pSender)
{
	ReplaceScene(TransitionRotoZoom::create(1.0f, CMenuLayer::scene()));
}



///////////////////////////////////////////////////////////////////////////////
// on reset button
///////////////////////////////////////////////////////////////////////////////
void CGCWinScene::Callback_OnResetButton(Ref* pSender)
{
	
	Director::getInstance()->replaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CGCGameLayerPlatformer >::CreateScene()));
}


///////////////////////////////////////////////////////////////////////////////
// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCWinScene::BeginContact(b2Contact* pB2Contact)
{
}


///////////////////////////////////////////////////////////////////////////////
// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CGCWinScene::EndContact(b2Contact* pB2Contact)
{
}