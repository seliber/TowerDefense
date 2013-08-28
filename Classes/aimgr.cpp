#include "aimgr.h"
#include "ai.h"
NAMESPACE_TD_BEGIN
void CAiMgr::DecorateObject( ITDObject* pObject )
{
	static IAi* pAi = new CAttackAi();
	pObject->setAI( pAi );
}

IAiWeakPtr CAiMgr::add( const String& key, const String& strType )
{
	IAi* pAi = new CAttackAi();
	IAiSharePtr ptr( pAi );
	m_mapData[key] = ptr;
	return IAiWeakPtr(ptr);
}
NAMESPACE_TD_END