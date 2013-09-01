#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CAiMgr : public IAiMgr{
public:
	CAiMgr();
	~CAiMgr();
	virtual void DecorateObject( ITDObject* pObject );
	virtual bool Ini( const String& strPath );
	virtual IAi* GetAi( const String& strType );
	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pAis, Ais )
};
NAMESPACE_TD_END