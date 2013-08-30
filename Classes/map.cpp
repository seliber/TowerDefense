#include "map.h"

NAMESPACE_TD_BEGIN
template<> ITDMapMgr* CSingleton<ITDMapMgr>::m_psSingleton = NULL;

CTDMap::CTDMap(){
	_tileMap = NULL;
	_background = NULL;

	CCPointArray* pPath1 = new CCPointArray();
	pPath1->initWithCapacity( 5 );
	pPath1->addControlPoint( ccp(150,350) );
	pPath1->addControlPoint( ccp(250,300) );
	pPath1->addControlPoint( ccp(350,300) );
	pPath1->addControlPoint( ccp(350,90) );
	m_vecPath.push_back( pPath1 );


	CCPointArray* pPath2 = new CCPointArray();
	pPath2->initWithCapacity( 3 );
	pPath2->addControlPoint( ccp(350,370) );
	pPath2->addControlPoint( ccp(350,90) );
	m_vecPath.push_back( pPath2 );

	CCPointArray* pPath3 = new CCPointArray();
	pPath3->initWithCapacity( 5 );
	pPath3->addControlPoint( ccp(550,260) );
	pPath3->addControlPoint( ccp(470,300) );
	pPath3->addControlPoint( ccp(350,300) );
	pPath3->addControlPoint( ccp(350,90) );
	m_vecPath.push_back( pPath3 );
}

Path* CTDMap::GetPath( ID id /* = 0 */ )
{
	if ( m_vecPath.size() <= id )
	{
		return NULL;
	}
	return m_vecPath[id];
}

bool CTDMap::LoadMap(const String& strFile)
{
	return false;
}

bool CTDMap::DecorateLayer( ILayer* pLayer )
{
	do 
	{    
		if ( pLayer )
		{
			this->setTileMap(CCTMXTiledMap::create("jianyu.tmx"));
			this->setBackground(_tileMap->layerNamed("background"));
			pLayer->addChild(_tileMap, -1);
		}
		else{
			return false;
		}

	} while (0);
	return true;
}

bool CTDMap::IsVisiblePosition( const IPoint* pt )
{
	return true;
}
NAMESPACE_TD_END