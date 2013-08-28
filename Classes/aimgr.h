#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class CAiMgr : public IAiMgr{
public:
	virtual void DecorateObject( ITDObject* pObject );
	virtual IAiWeakPtr add( const String& key, const String& strType );
	virtual bool Ini( const String& strPath ){return false;}
};
NAMESPACE_TD_END