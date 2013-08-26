#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class CTDMap : public ITDMap{
public:
	CTDMap();
	virtual bool IniMap( const String& strFile, CCLayer* pLayer ); 
	virtual Path* GetPath();
	virtual bool LoadMap(const String& strFile);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _background, Background);
protected:
	Path* m_pPath;
};
NAMESPACE_TD_END