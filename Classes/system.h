#pragma once
#include "templclassdef.h"
#include "interfacedef.h"
#include "cocos2d.h"

NAMESPACE_TD_BEGIN
class CSystem : public CSingleton<CSystem>{
public:
	CSystem();
	bool Launch( const String& strSourcePath );
	bool Start( const String& strLevel, CCLayer* pLayer );
	bool Pause();
	bool Resume();
	bool End();
public:
	CCLayer* m_pLayer;
};
NAMESPACE_TD_END