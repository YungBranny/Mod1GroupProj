#ifndef	_GCOBJKEYS_H_
#define	_GCOBJKEYS_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////
// This 'GCObjKeys' Header File and Class File was created and was managed by Mehak Hussain.          //
// The purpose of this Class is to create the Key Collectables for the Player to collect one by one. //
// In this Class, I set the creation and collision of the Keys.                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "../../GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CGCObjKeys
	: public CGCObjSpritePhysics
{
private:
	unsigned short int		m_iCollisionBuffer;

	bool					m_bJustCollided;

	void					CollisionChecker();

	std::unique_ptr< CGCFactoryCreationParams > m_pCustomCreationParams;

public:
	CGCObjKeys ( void );
	virtual ~CGCObjKeys ();

	GCFACTORY_DECLARE_CREATABLECLASS	( CGCObjKeys );

	unsigned short int getCollisionBuffer ()	const	{	return m_iCollisionBuffer;	}
	void  setCollisionBuffer ( unsigned short int i )	{	m_iCollisionBuffer = i;	    }

	bool  getJustCollided ()			        const	{	return m_bJustCollided;	    }
	void  setJustCollided	 (		  bool i        )	{	  m_bJustCollided = i;	    }

	virtual void VOnResourceAcquire ( void );
	virtual void VOnUpdate			( f32 fTimestep );

	virtual void VHandleFactoryParams ( const CGCFactoryCreationParams& rCreationParams, cocos2d::Vec2 v2InitialPosition );
};
#endif