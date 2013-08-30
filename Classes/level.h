#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CLevel : public ITDLevel{
public:
	CLevel();
	virtual void update(float delta);
	virtual bool Start( ILayer* pLayer, TDMapWeakPtr pPath );
	virtual bool End();
	virtual void ObjectFinished( CCNode* pNode );
	DEF_MEMBER( unsigned int, m_wEnemyCount, EnemyCount)
	DEF_MEMBER( unsigned int, m_wCurrentIndex, CurrentIndex)
	DEF_MEMBER( unsigned int, m_wTimeInterval, TimeInterval)
	DEF_MEMBER( TDMapWeakPtr, m_pMap, Map )
protected:
	virtual bool LoadLevel( const String& strFile ){ return false;}
private:
	CCLayer* m_pLayer;
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