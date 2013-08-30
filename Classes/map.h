#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDMap : public ITDMap{
public:
	CTDMap();
	virtual Path* GetPath( ID id = 0 );
	virtual bool IsVisiblePosition( const IPoint* pt );
	virtual bool LoadMap(const String& strFile);
	virtual bool DecorateLayer( ILayer* pLayer );
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _background, Background);
protected:
	typedef vector<Path*> PathContainer;
	PathContainer m_vecPath;
};

class CTDMapMgr : public ITDMapMgr{
public:
	virtual bool Ini( const String& strPath ){return false;}
	virtual TDMapWeakPtr add( const String& key, const string& strType ){
		ITDMap* pMap = new CTDMap();	
		TDMapSharePtr ptr(pMap);
		m_mapData[key] = ptr;
		return TDMapWeakPtr(ptr);
	}
};
NAMESPACE_TD_END