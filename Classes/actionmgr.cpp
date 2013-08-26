#include "actionmgr.h"
NAMESPACE_TD_BEGIN

template<> IActionMgr* CSingleton<IActionMgr>::m_psSingleton = 0;

bool CActionMgr::DoAction( const ITDObject* pTagObject, const String& strAction )
{
	return false;
}
NAMESPACE_TD_END