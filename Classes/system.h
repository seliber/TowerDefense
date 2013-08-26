#pragma once
#include "templclassdef.h"
#include "interfacedef.h"
#include "cocos2d.h"

NAMESPACE_TD_BEGIN
class CSystem : public CSingleton<CSystem>{
public:
	CSystem();
	bool Launch( const String& strMap, CCLayer* pLayer );
	bool Update( CCLayer* pLayer, float dt );
	void RemoveObject( ITDObject* pObject );
public:
	CCLayer* m_pLayer;
};

class IBoss : public CSingleton<IBoss>{
public:
	bool Update( CCLayer* pLayer, float dt );
};
NAMESPACE_TD_END