#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CLevel : public ITDLevel{
public:
	CLevel();
	virtual void update(float delta);
	virtual bool Start( ILayer* pLayer, Path* pPath );
	virtual bool End();
	DEF_MEMBER( unsigned int, m_wEnemyCount, EnemyCount)
	DEF_MEMBER( unsigned int, m_wCurrentIndex, CurrentIndex)
	DEF_MEMBER( unsigned int, m_wTimeInterval, TimeInterval)
	DEF_MEMBER( IPoint, m_ptOrigin, Origin )
protected:
	virtual bool LoadLevel( const String& strFile ){ return false;}
private:
	CCLayer* m_pLayer;
	Path* m_pPath;
};

class CLevelMgr : public ITDLevelMgr{
public:
	virtual bool Ini( const String& strPath ){return false;}
	virtual TDLevelWeakPtr add( const String& key, const string& strType ){
		ITDLevel* pLevel = new CLevel();	
		TDLevelSharePtr ptr(pLevel);
		m_mapData[key] = ptr;
		return TDLevelWeakPtr(ptr);
	}
};
NAMESPACE_TD_END