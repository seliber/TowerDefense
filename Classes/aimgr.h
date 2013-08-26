#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class CAiMgr : public IAiMgr{
public:
	virtual void DecorateObject( ITDObject* pObject );
	virtual IAi* add( const String& key, const String& strType );
};
NAMESPACE_TD_END