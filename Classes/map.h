#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDMap : public ITDMap{
public:
	CTDMap();
	virtual bool IniMap( const String& strFile, CCLayer* pLayer ); 
	virtual Path* GetPath();
	virtual bool IsVisiblePosition( const IPoint* pt );
	virtual bool LoadMap(const String& strFile);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _background, Background);
protected:
	Path* m_pPath;
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