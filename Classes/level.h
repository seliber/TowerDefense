#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CLevel : public ITDLevel{
public:
	CLevel();
	~CLevel();
	virtual void update(float delta);
	virtual bool Start( ILayer* pLayer, ITDMap* pMap );
	virtual bool End();
	CC_SYNTHESIZE( unsigned int, m_wEnemyCount, EnemyCount)
	CC_SYNTHESIZE( unsigned int, m_wCurrentIndex, CurrentIndex)
	CC_SYNTHESIZE( unsigned int, m_wTimeInterval, TimeInterval)

	CC_SYNTHESIZE_RETAIN( ITDMap*, m_pMap, Map )
	CC_SYNTHESIZE_RETAIN( ILayer*, m_pLayer, Layer)
protected:
	virtual bool LoadLevel( const String& strFile ){ return false;}
};

class CLevelMgr : public ITDLevelMgr{
public:
	CLevelMgr();
	~CLevelMgr();
	virtual bool Ini( const String& strPath );
	virtual ITDLevel* GetLevel( unsigned int wIndex );
	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pLevels, Levels )
};
NAMESPACE_TD_END