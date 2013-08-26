#include "map.h"

NAMESPACE_TD_BEGIN
template<> ITDMap* CSingleton<ITDMap>::m_psSingleton = NULL;

CTDMap::CTDMap(){


	_tileMap = NULL;
	_background = NULL;
}

Path* CTDMap::GetPath()
{
	m_pPath = CCPointArray::create( 30 );
	m_pPath->addControlPoint( ccp(20,20) );
	m_pPath->addControlPoint( ccp(50,50) );
	m_pPath->addControlPoint( ccp(100,50) );
	m_pPath->addControlPoint( ccp(150,50) );
	m_pPath->addControlPoint( ccp(200,50) );
	m_pPath->addControlPoint( ccp(250,50) );
	m_pPath->addControlPoint( ccp(300,50) );
	m_pPath->addControlPoint( ccp(350,50) );
	m_pPath->addControlPoint( ccp(400,50) );
	m_pPath->addControlPoint( ccp(400,100) );

	m_pPath->addControlPoint( ccp(400,150) );
	m_pPath->addControlPoint( ccp(400,200) );
	m_pPath->addControlPoint( ccp(400,250) );
	m_pPath->addControlPoint( ccp(400,300) );


	return m_pPath;
}

bool CTDMap::IniMap( const String& strFile, CCLayer* pLayer )
{
	do 
	{    
		if ( pLayer )
		{
			this->setTileMap(CCTMXTiledMap::create("map.tmx"));
			this->setBackground(_tileMap->layerNamed("Background"));
			pLayer->addChild(_tileMap, -1);
		}
		else{
			return false;
		}

	} while (0);
	return true;
}

bool CTDMap::LoadMap(const String& strFile)
{
	return false;
}
NAMESPACE_TD_END