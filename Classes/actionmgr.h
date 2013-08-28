#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class CActionMgr : public IActionMgr{
public:
	virtual bool DoAction( const ITDObject* pTagObject, const String& strAction );
	virtual bool Ini( const String& strPath ){return false;}
};
NAMESPACE_TD_END
