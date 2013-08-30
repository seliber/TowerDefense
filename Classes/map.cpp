#include "map.h"

NAMESPACE_TD_BEGIN
template<> ITDMapMgr* CSingleton<ITDMapMgr>::m_psSingleton = NULL;

CTDMap::CTDMap(){
	_tileMap = NULL;
	_background = NULL;

	m_pPath = new CCPointArray();
	m_pPath->initWithCapacity( 30 );
	m_pPath->addControlPoint( ccp(50,50) );
	m_pPath->addControlPoint( ccp(300,50) );
	m_pPath->addControlPoint( ccp(300,300) );
	m_pPath->addControlPoint( ccp(50,300) );
	m_pPath->addControlPoint( ccp(50,50) );
}

Path* CTDMap::GetPath()
{
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

bool CTDMap::IsVisiblePosition( const IPoint* pt )
{
	return true;
}
NAMESPACE_TD_END