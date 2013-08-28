#pragma once
#include "templclassdef.h"
#include "interfacedef.h"
#include "cocos2d.h"

NAMESPACE_TD_BEGIN
class CSystem : public CSingleton<CSystem>{
public:
	CSystem();
	bool Launch( const String& strMap, CCLayer* pLayer );
public:
	CCLayer* m_pLayer;
};
NAMESPACE_TD_END