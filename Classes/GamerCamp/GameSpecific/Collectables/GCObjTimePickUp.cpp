//#include "../../GCCocosInterface/GB2ShapeCache-x.h"
//
//#include "GamerCamp/GameSpecific/Collectables/GCObjTimePickUp.h"
//
//GCFACTORY_IMPLEMENT_CREATEABLECLASS(CGCObjTimePickUp);
//
//CGCObjTimePickUp::CGCObjTimePickUp ( void )
//	: CGCObjSpritePhysics ( GetGCTypeIDOf(CGCObjTimePickUp) ) // We are inheriting from CGCObjSpritePhysics, so we can use physics on the Timer PickUp
//	, m_bJustCollided		(	false	)
//	, m_iCollisionBuffer	(	 60		)
//{
//
//}
//
//CGCObjTimePickUp::~CGCObjTimePickUp()
//{
//
//}
//
//// Create the Timer PickUp Sprite, give it a physics body and then set fixed rotation to 'True'
////IN_CPP_CREATION_PARAMS_DECLARE(CGCObjTimePickUp, "TexturePacker/Sprites/TimerPickUp/TimerPickUp.plist", "TimerPickUp", b2_staticBody, true);
//void CGCObjTimePickUp::VOnResourceAcquire ( void )
//{
//	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CGCObjTimePickUp);
//
//	CGCObjSpritePhysics::VOnResourceAcquire();
//}
//
//void CGCObjTimePickUp::CollisionChecker()
//{
//	// Default Collision is false until collided with, this stops collision being called multiple times
//	if( m_bJustCollided == true )
//	{
//		if( m_iCollisionBuffer >= 0 )
//		{
//			m_iCollisionBuffer--;
//		}
//
//		if( m_iCollisionBuffer <= 0 )
//		{
//			m_bJustCollided = false;
//			m_iCollisionBuffer = 60;
//		}
//	}
//}
//
//void CGCObjTimePickUp::VOnUpdate(f32 fTimestep)
//{
//	SetSpriteRotation(GetSpriteRotation() + 0.1f); // Setting the rotation for the Timer PickUp, so they spin and look appealing to the Player
//	CollisionChecker(); // Updates CollisionChecker
//}