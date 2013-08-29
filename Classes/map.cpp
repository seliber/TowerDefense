#include "map.h"

NAMESPACE_TD_BEGIN
template<> ITDMapMgr* CSingleton<ITDMapMgr>::m_psSingleton = NULL;

CTDMap::CTDMap(){
	_tileMap = NULL;
	_background = NULL;

	m_pPath = new CCPointArray();
	m_pPath->initWithCapacity( 30 );
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