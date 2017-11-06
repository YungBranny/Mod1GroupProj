////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SGCFACTORYCREATIONPARAMS_H_
#define _SGCFACTORYCREATIONPARAMS_H_

#ifndef _GCTYPES_H_
#include "../Core/GCTypes.h"
#endif

#ifndef BOX2D_H
	#include "box2d/Box2D.h"
#endif


//////////////////////////////////////////////////////////////////////////
// class used to pass data to the factory in order to create an object
// createable classes must have a constructor that takes a reference to 
// an instance of this class as its single parameter
// 
// If you need to extend this system, the best way is probably to:
//
// 1) add the ability for classes to register custom xml parsing functions 
//	  with CGCLevelLoader_Ogmo. CGCLevelLoader_Ogmo would need to associate 
//	  the custom parser functions with the class name to call the right one
//	  
// 2) ...these custom parsers would take the xml data for the class and 
//	  return a reference to CGCFactoryCreationParams...
//	  
// 3) ...to make your life easy and code more robust the class deriving from 
//	  CGCObjSpritePhysics which uses the custom parser would need to derive 
//	  a class from CGCFactoryCreationParams so CGCLevelLoader_Ogmo can fill 
//	  out the standard data in CGCFactoryCreationParams automatically and
//	  the custom parse can just read the rest of it and return it from the 
//	  function as a CGCFactoryCreationParams&...
//    
// 4) ...and your CGCObjSpritePhysics derived class can override the base
//    VHandleFactoryParams() and static_cast the CGCFactoryCreationParams 
//	  argument back to the expected derived type to get at the extra data. 
//	  Job done, you're welcome :)
//////////////////////////////////////////////////////////////////////////
class CGCFactoryCreationParams
{
public:
	std::string strClassName;			// name of the CGCFactory_ObjSpritePhysics derived class to create
	std::string strPlistFile;			// path of the .plist file needed to load the object's sprite
	std::string strPhysicsShape;		// name of the physics shape used
	b2BodyType	eB2dBody_BodyType;		// body type of the physics body
	bool		bB2dBody_FixedRotation;	// determines whether the rotation of the object is fixed


	//////////////////////////////////////////////////////////////////////////
	// default initialising constructor
	//////////////////////////////////////////////////////////////////////////
	CGCFactoryCreationParams( void )
	: eB2dBody_BodyType		( b2_dynamicBody )
	, bB2dBody_FixedRotation( false )
	{}


	//////////////////////////////////////////////////////////////////////////
	// explicit initialising constructor
	//////////////////////////////////////////////////////////////////////////
	CGCFactoryCreationParams(	const char* pszClassName, 
								const char* pszPlistFile, 
								const char*	pszPhysicsShape,
								b2BodyType	eb2BodyType, 
								bool		bRotationIsFixed )
	: strClassName			( pszClassName )
	, strPlistFile			( pszPlistFile )
	, strPhysicsShape		( pszPhysicsShape )
	, eB2dBody_BodyType		( eb2BodyType )
	, bB2dBody_FixedRotation( bRotationIsFixed )
	{}


	//////////////////////////////////////////////////////////////////////////
	// overloaded operator ==
	// N.B. compare least complex types first as an 'early-out'
	//////////////////////////////////////////////////////////////////////////
	bool operator==( const CGCFactoryCreationParams& rtRhs ) const
	{
		return(		( eB2dBody_BodyType			== rtRhs.eB2dBody_BodyType )
				&&	( bB2dBody_FixedRotation	== rtRhs.bB2dBody_FixedRotation )
				&&	( strClassName				== rtRhs.strClassName ) 
				&&	( strPlistFile				== rtRhs.strPlistFile )
				&&	( strPhysicsShape			== rtRhs.strPhysicsShape ) );
	}

	//////////////////////////////////////////////////////////////////////////
	// virtual destructor so it can be extended later and continue 
	// being used in CGCLevelLoader_Ogmo with the minimum of fuss
	virtual ~CGCFactoryCreationParams( void )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	bool NameIs( const char* pszNameToTest ) const
	{
		return !( strClassName.compare( pszNameToTest ) );
	}
};

#endif // #ifndef _SCGFACTORYCREATIONPARAMS_H_ ...