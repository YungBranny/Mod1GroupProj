#ifndef _GCLEVELLOADER_OGMO_H_
#define _GCLEVELLOADER_OGMO_H_

#include <vector>
#include <map>
#include <functional>

#ifndef HEADER_PUGIXML_HPP
	#include "..\pugixml-1.2\pugixml.hpp"
#endif

#ifndef _SGCFACTORYCREATIONPARAMS_H_
	#include "GamerCamp\GCCocosInterface\SGCFactoryCreationParams.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////
class CGCFactory_ObjSpritePhysics;


//////////////////////////////////////////////////////////////////////////
// N.B. this code was written by one of the GCPro 2012 students
// and adapted and back ported by Alex
// TBH the orginial code was a bit of a state and I didn't have time to 
// clean it up as much as I would have liked...
// 
// N.B. you will see pugi::xml_node passed by value all over the place
// it is a VERY lightweight class - just one pointer internally
// 
//////////////////////////////////////////////////////////////////////////
class CGCLevelLoader_Ogmo
{
	// the xml document (tree structure)
	pugi::xml_document	m_xmlOgmoLevelFile;

	// the level node of the xml document
	pugi::xml_node		m_nodeLevels;

	// level file has dimensions, need to use these to correctly position objects from level file
	// as ogmo's coords are top left 0,0 & cocos are bottom left 0,0
	b2Vec2				m_v2LevelDimensions;

	// vector of all unique parameter setups read from the level file
	// and used to create objects
	std::vector< const CGCFactoryCreationParams* >	m_vecFactoryCreationParams;
	enum
	{
	   EMAX_HANDLED_UNIQUE_CREATIONPARAMS = 256
	}; 

	// adds the creation params to internal store
	const	CGCFactoryCreationParams*	AddCreationParamsToInternalStore	( const CGCFactoryCreationParams* rtParamsToCheck );
	const	CGCFactoryCreationParams*	GetCreationParamsFromCache			( const char* pszClassName );

	// iterates the xml data and calls the class factory for each valid
	// instance of object data contained in it 
	u32								RecursiveIterateXMLNodeCreatingObjects	(	pugi::xml_node xnodeStart, 
																				CGCFactory_ObjSpritePhysics& rcClassFactory );
	// helper functions to validate data & extract required data from xml 
	inline bool								IsValidFactoryData						( pugi::xml_node xnodeToCheck );
	inline const char*						GetFactoryClassName						( pugi::xml_node xnodeData );
	inline const CGCFactoryCreationParams*	GetFactoryData							( pugi::xml_node xnodeData );
	inline b2Vec2							GetObjectPosition						( pugi::xml_node xnodePosition );
	inline b2BodyType						B2BodyTypeFromString					( const char* pszBodyType );

public:
	// Con/destruction
	CGCLevelLoader_Ogmo( void );
	~CGCLevelLoader_Ogmo( void );

	// load level file (level_x.oel)
	bool			LoadLevelFile( const char* pszOelFile );

	// create objects
	u32				CreateObjects( CGCFactory_ObjSpritePhysics& rcClassFactory );
};


#endif