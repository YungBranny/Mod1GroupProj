#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include "GCLevelLoader_Ogmo.h"

#include "cocos2d.h"

#include "../../GameSpecific/GCGameLayerPlatformer.h"
#include "../IGCGameLayer.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GCCocosInterface/GCObjTileLayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjPlayer.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjGroupInvader.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Items/GCObjItem.h" 
#include "AppDelegate.h"

#include "GCLevelLoader_Ogmo.h"

using namespace std;
USING_NS_CC;



//////////////////////////////////////////////////////////////////////////
// constants defining the names of the xml expected attributes in the oel
// level file
//////////////////////////////////////////////////////////////////////////
static const char* k_pszXmlAttr_ClassName				= "class";
static const char* k_pszXmlAttr_PlistFile				= "PlistFile";
static const char* k_pszXmlAttr_PhysicsShape			= "shape";
static const char* k_pszXmlAttr_B2D_BodyType			= "B2DBodyType";
static const char* k_pszXmlAttr_B2D_HasFixedRotation	= "HasFixedRotation";
static const char* k_pszXmlAttr_StartPos_X				= "x";
static const char* k_pszXmlAttr_StartPos_Y				= "y";



// strings for b2BodyType enum
static const char* k_pszB2BodyType_Dynamic		= "b2_dynamicBody";
static const char* k_pszB2BodyType_Static		= "b2_staticBody";
static const char* k_pszB2BodyType_Kinematic	= "b2_kinematicBody";


//////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////
CGCLevelLoader_Ogmo::CGCLevelLoader_Ogmo( void )
: m_v2LevelDimensions( b2Vec2_zero )
{
	m_vecFactoryCreationParams.reserve( EMAX_HANDLED_UNIQUE_CREATIONPARAMS );
}

//////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////
CGCLevelLoader_Ogmo::~CGCLevelLoader_Ogmo( void )
{	
	for( u32 u = 0; u < m_vecFactoryCreationParams.size(); ++u )
	{
		delete m_vecFactoryCreationParams[ u ];
	}
}

//////////////////////////////////////////////////////////////////////////
// This function just loads the level file.
// CreateObjects() must be called to create them
//////////////////////////////////////////////////////////////////////////
bool CGCLevelLoader_Ogmo::LoadLevelFile( const char* pszOelFile )
{
	//=== 1. XML-file

	// Load and parse the xml-file
	pugi::xml_parse_result sParseResult = m_xmlOgmoLevelFile.load_file( pszOelFile );

	// print errors if they occurred during the loading
	if( !sParseResult ) 
	{		
		cerr << " CGCLevelLoader_Ogmo: Error during parsing of xml-file!" << endl;

		// Print details about the error / Print the "parsing status"
		cerr << " xml-file [" << pszOelFile << "] was parsed with errors, attr value: [" << m_xmlOgmoLevelFile.child( "node" ).attribute( "attr" ).value() << "]\n";
		cerr << " Error description: " << sParseResult.description() << "\n";
		cerr << " Error offset: " << sParseResult.offset << " (error at [..." << ( pszOelFile + sParseResult.offset ) << "]\n\n";

		CCAssert( false, " CGCLevelLoader_Ogmo: Failed to load xml-file!" );

	}

	// Get the level node and store the width / height of the level (needed to crrect position setting...)
	m_nodeLevels = m_xmlOgmoLevelFile.child( "level" );
	m_v2LevelDimensions = b2Vec2( m_nodeLevels.attribute("width").as_float(), m_nodeLevels.attribute("height").as_float() );

	// successful
	return true;
}


//////////////////////////////////////////////////////////////////////////
// recursively iterates he xml nodes in the loaded level document
// for each one it checks if it is a valid chunk of class factory data
// and if so uses it to create an object via the class factory
//////////////////////////////////////////////////////////////////////////
u32	CGCLevelLoader_Ogmo::CreateObjects( CGCFactory_ObjSpritePhysics& rcClassFactory )
{
	return RecursiveIterateXMLNodeCreatingObjects( m_nodeLevels, rcClassFactory );
}

//////////////////////////////////////////////////////////////////////////
// recursively iterates he xml nodes in the loaded level document
// for each one it checks if it is a valid chunk of class factory data
// and if so uses it to create an object via the class factory
// 
// N.B. depth first recursion
// 
//////////////////////////////////////////////////////////////////////////
// private
u32 CGCLevelLoader_Ogmo::RecursiveIterateXMLNodeCreatingObjects( pugi::xml_node xnodeStart, CGCFactory_ObjSpritePhysics& rcClassFactory )
{ 
	pugi::xml_node	xnodeCurrent	= xnodeStart;
	u32				uNumCreated		= 0;

	for( ; xnodeCurrent; xnodeCurrent = xnodeCurrent.next_sibling() ) 
	{
		if( IsValidFactoryData( xnodeCurrent ) )
		{
			// check to see if we already have factory data for this class
			const CGCFactoryCreationParams* pParams = GetCreationParamsFromCache( GetFactoryClassName( xnodeCurrent ) );

			// if not found create it and add to the store
			if( nullptr == pParams )
			{
				pParams = AddCreationParamsToInternalStore( GetFactoryData( xnodeCurrent ) );
			}

			CCAssert( ( nullptr != pParams ), "Error creating creation params from xml!" );

			// CreateInstance takes CGCFactoryCreationParams& 
			CGCObjSpritePhysics* pObject = rcClassFactory.CreateInstance( (*pParams), GetObjectPosition( xnodeCurrent ) );
			uNumCreated++;
		}

		pugi::xml_node xnodeChild = xnodeCurrent.first_child();
		if( xnodeChild )
		{
			uNumCreated += RecursiveIterateXMLNodeCreatingObjects( xnodeChild, rcClassFactory );
		}
	}

	return uNumCreated; 
}

//////////////////////////////////////////////////////////////////////////
// validates an xml node as data that can be used to create an instance
// via the class factory
//////////////////////////////////////////////////////////////////////////
// private
inline bool CGCLevelLoader_Ogmo::IsValidFactoryData( pugi::xml_node xnodeToCheck )
{
	return(		xnodeToCheck.attribute( k_pszXmlAttr_ClassName ) 
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_PlistFile )
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_PhysicsShape )
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_B2D_BodyType )
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_B2D_HasFixedRotation )
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_StartPos_X )
			&& 	xnodeToCheck.attribute( k_pszXmlAttr_StartPos_Y )
		);
}

//////////////////////////////////////////////////////////////////////////
// private inline 
const char* CGCLevelLoader_Ogmo::GetFactoryClassName( pugi::xml_node xnodeData )
{
	return xnodeData.attribute( k_pszXmlAttr_ClassName ).value();
}

//////////////////////////////////////////////////////////////////////////
// creates the corresponding factory creation params for a valid xml node
//////////////////////////////////////////////////////////////////////////
// private
inline const CGCFactoryCreationParams* CGCLevelLoader_Ogmo::GetFactoryData( pugi::xml_node xnodeData )
{
	return( new CGCFactoryCreationParams(	xnodeData.attribute( k_pszXmlAttr_ClassName ).value(),
											xnodeData.attribute( k_pszXmlAttr_PlistFile ).value(),
											xnodeData.attribute( k_pszXmlAttr_PhysicsShape ).value(),
											B2BodyTypeFromString( xnodeData.attribute( k_pszXmlAttr_B2D_BodyType ).value() ),
											xnodeData.attribute( k_pszXmlAttr_B2D_HasFixedRotation ).as_bool() ) );
}

//////////////////////////////////////////////////////////////////////////
// extracts the x, y 2d vector from a valid xml node 
// N.B. corrects for the coordinate diference between cocos2d and ogmo
// (cocos2d 0,0 : left,bottom & ogmo 0,0 : left, top)
//////////////////////////////////////////////////////////////////////////
// private
inline b2Vec2 CGCLevelLoader_Ogmo::GetObjectPosition( pugi::xml_node xnodePosition )
{
	return( b2Vec2( xnodePosition.attribute( k_pszXmlAttr_StartPos_X ).as_float(), 
					( m_v2LevelDimensions.y - xnodePosition.attribute( k_pszXmlAttr_StartPos_Y ).as_float() ) ) );
}

//////////////////////////////////////////////////////////////////////////
// converts the xml string version of the box 2d body type to the enum
// value expected by box 2d
//////////////////////////////////////////////////////////////////////////
// private
inline b2BodyType CGCLevelLoader_Ogmo::B2BodyTypeFromString( const char* pszBodyType )
{
	b2BodyType eReturnType = b2_dynamicBody;

	// N.B. can't use a switch because of strings 
	if( !strcmp( pszBodyType, k_pszB2BodyType_Static ) )
	{
		eReturnType = b2_staticBody;

	}
	else if( !strcmp( pszBodyType, k_pszB2BodyType_Kinematic ) )
	{
		eReturnType = b2_kinematicBody;
	}

	return eReturnType;
}


//////////////////////////////////////////////////////////////////////////
// private
const CGCFactoryCreationParams* CGCLevelLoader_Ogmo::GetCreationParamsFromCache( const char* pszClassName )
{
	const CGCFactoryCreationParams* pcReturn = nullptr;

	size_t uNumElements = m_vecFactoryCreationParams.size();
	for( size_t u = 0; u < uNumElements; ++u )
	{
		if( m_vecFactoryCreationParams[ u ]->NameIs( pszClassName ) )
		{
			pcReturn = m_vecFactoryCreationParams[ u ]; 
			break;
		}
	}

	return pcReturn;
}


//////////////////////////////////////////////////////////////////////////
// this class used to store cache creation params by value, but has been 
// changed so that they're stored as pointers so that the data can be 
// extended
//////////////////////////////////////////////////////////////////////////
// private
const CGCFactoryCreationParams* CGCLevelLoader_Ogmo::AddCreationParamsToInternalStore( const CGCFactoryCreationParams* ptParams )
{
	CCAssert(	( m_vecFactoryCreationParams.size() < EMAX_HANDLED_UNIQUE_CREATIONPARAMS ), 
				"You need to reserve more space in CGCLevelLoader_Ogmo::m_vecFactoryCreationParams! Make CGCLevelLoader_Ogmo::EMAX_HANDLED_UNIQUE_CREATIONPARAMS bigger!" );

	m_vecFactoryCreationParams.push_back( ptParams );
	return m_vecFactoryCreationParams.back();
}


