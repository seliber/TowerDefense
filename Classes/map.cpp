#include "map.h"

NAMESPACE_TD_BEGIN
template<> ITDMapMgr* CSingleton<ITDMapMgr>::m_psSingleton = NULL;

CTDMap::CTDMap() : m_pPathes(NULL),m_pTileMap(NULL),m_pBackground(NULL){
	/*setPathes( CCArray::createWithCapacity(10) );*/
// 	CCPointArray* pPath1 = new CCPointArray();
// 	pPath1->initWithCapacity( 5 );
// 	pPath1->addControlPoint( ccp(150,350) );
// 	pPath1->addControlPoint( ccp(250,300) );
// 	pPath1->addControlPoint( ccp(350,300) );
// 	pPath1->addControlPoint( ccp(350,90) );
// 	m_pPathes->addObject( pPath1 );
// 
// 
// 	CCPointArray* pPath2 = new CCPointArray();
// 	pPath2->initWithCapacity( 3 );
// 	pPath2->addControlPoint( ccp(350,370) );
// 	pPath2->addControlPoint( ccp(350,90) );
// 	m_pPathes->addObject( pPath2 );
// 
// 	CCPointArray* pPath3 = new CCPointArray();
// 	pPath3->initWithCapacity( 5 );
// 	pPath3->addControlPoint( ccp(550,260) );
// 	pPath3->addControlPoint( ccp(470,300) );
// 	pPath3->addControlPoint( ccp(350,300) );
// 	pPath3->addControlPoint( ccp(350,90) );
// 	m_pPathes->addObject( pPath3 );
}

CTDMap::~CTDMap(){
	CC_SAFE_RELEASE_NULL( m_pPathes );
	CC_SAFE_RELEASE_NULL( m_pTileMap );
	CC_SAFE_RELEASE_NULL( m_pBackground );
}

Path* CTDMap::GetPath( ID id /* = 0 */ )
{
	if ( id > m_pPathes->count() )
	{
		return NULL;
	}
	return (Path*)m_pPathes->objectAtIndex( id );
}

bool CTDMap::LoadMap(const String& strFile)
{
	String strPath = strFile + "map.tmx";
	this->setTileMap(CCTMXTiledMap::create(strPath.c_str()));
	this->setBackground(m_pTileMap->layerNamed("background"));
	bool bRet = LoadPathes();
	return bRet;
}

bool CTDMap::LoadPathes()
{
	if ( m_pTileMap == NULL )
	{
		return false;
	}
	CCDictionary* pMapInfo = m_pBackground->getProperties();
	int nPathCount = ((CCString*)pMapInfo->objectForKey("pathcount"))->intValue();

	setPathes( CCArray::createWithCapacity(nPathCount+1) );

	for ( int i = 1; i <= nPathCount; i++ )
	{
		char szPathName[100] = {0};
		sprintf(szPathName, "path%d", i );
		if ( !LoadPath( szPathName) )
		{
			return false;
		}
	}
	return true;

}

bool CTDMap::LoadPath( const String& strPath )
{
	CCTMXObjectGroup* group = m_pTileMap->objectGroupNamed(strPath.c_str());
	CCArray* objects = group->getObjects();

	CCDictionary* dict = NULL;
	CCObject* pObj = NULL;

	CCPointArray* pPath = new CCPointArray();
	pPath->initWithCapacity( objects->count() + 1 );

	CCSize czWin = CCDirector::sharedDirector()->getWinSize();
	CCARRAY_FOREACH(objects, pObj)
	{
		dict = (CCDictionary*)pObj;
		int x = ((CCString*)dict->objectForKey("x"))->intValue();
		int y = ((CCString*)dict->objectForKey("y"))->intValue();
		pPath->addControlPoint( ccp(x,czWin.height - y) );
		if(!dict)
			break;
	}
	m_pPathes->addObject( pPath );
	return true;
}

bool CTDMap::DecorateLayer( ILayer* pLayer )
{
	do 
	{    
		if ( pLayer )
		{
			pLayer->addChild(m_pTileMap, -1);
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

CTDMapMgr::CTDMapMgr():m_pMaps(NULL){}
CTDMapMgr::~CTDMapMgr(){
	CC_SAFE_RELEASE_NULL(m_pMaps);
}

bool CTDMapMgr::Ini( const String& strPath )
{
	setMaps( CCArray::createWithCapacity( 10) );
	CTDMap* pMap = new CTDMap();
	pMap->LoadMap( strPath );
	pMap->autorelease();
	m_pMaps->addObject( pMap );
	return false;
}

ITDMap* CTDMapMgr::GetMap(unsigned int wIndex )
{
	if ( wIndex < m_pMaps->count() )
	{
		return (ITDMap*)m_pMaps->objectAtIndex( wIndex );
	}
	return NULL;
}
NAMESPACE_TD_END