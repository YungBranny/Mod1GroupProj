//#include "GCMovingEnemies.h"
//
//using namespace cocos2d;
//
//CGCMovingEnemies::CGCMovingEnemies ()
//	: m_eMoveDirection (EMoveDirection::Right)
//	, m_bMovingLeftAndRight (true)
//	, m_fEndDestination1	(100,0)
//	, m_fEndDesitnation2	(400,0)
//{
//}
//
//cocos2d::Vec2	MovingEnemyRight = cocos2d::Vec2 (5.0f, 0.0f);
//cocos2d::Vec2	MovingEnemyLeft	= ( -MovingEnemyRight );
//
//cocos2d::Vec2	MovingEnemyUp = cocos2d::Vec2 (0.0f, -6.0f);
//cocos2d::Vec2	MovingEnemyDown = ( -MovingEnemyDown );
//
//
//void CGCMovingEnemies::VOnUpdate (f32 fTimeStep)
//{
//	if (m_bMovingLeftAndRight == true) 
//	{
//		switch (m_eMoveDirection)
//		
//	
//		{
//		case EMoveDirection::Right:
//			if(GetSpritePosition().x == m_fEndDestination1.x)
//			{
//				m_eMoveDirection = EMoveDirection::Left;
//			}
//			break;
//		
//		
//		case EMoveDirection::Left:
//				
//			if (GetSpritePosition ().x == m_fEndDesitnation2.x)
//			{
//				m_eMoveDirection = EMoveDirection::Right;
//			}
//			break;
//	
//		}
//
//		if (m_bMovingLeftAndRight == false)
//		{
//			switch (m_eMoveDirection)
//			{
//			case EMoveDirection::Up:
//				if (GetSpritePosition ().x == m_fEndDestination1.y)
//				{
//					m_eMoveDirection = EMoveDirection::Down;
//				}
//				break;
//
//
//			case EMoveDirection::Down:
//
//				if (GetSpritePosition ().x == m_fEndDesitnation2.y)
//				{
//					m_eMoveDirection = EMoveDirection::Up;
//				}
//				break;
//			}
//		}
//	
//	}
//};