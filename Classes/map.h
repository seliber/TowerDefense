#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDMap : public ITDMap{
public:
	CTDMap();
	~CTDMap();
	virtual Path* GetPath( ID id = 0 );
	virtual bool IsVisiblePosition( const IPoint* pt );
	virtual bool LoadMap(const String& strFile);
	virtual bool DecorateLayer( ILayer* pLayer );
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, m_pTileMap, TileMap);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, m_pBackground, Background);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, m_pPathes, Pathes);
protected:
	bool LoadPathes();
	bool LoadPath( const String& strPath );
};

class CTDMapMgr : public ITDMapMgr{
public:
	CTDMapMgr();
	~CTDMapMgr();
	virtual bool Ini( const String& strPath );
	virtual ITDMap* GetMap(unsigned int wIndex );
	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pMaps, Maps )
};
NAMESPACE_TD_END