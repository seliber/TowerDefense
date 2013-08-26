#include "aimgr.h"
#include "ai.h"
NAMESPACE_TD_BEGIN
void CAiMgr::DecorateObject( ITDObject* pObject )
{
	static IAi* pAi = new CAttackAi();
	pObject->setAI( pAi );
}

IAi* CAiMgr::add( const String& key, const String& strType )
{
	return 0;
}
NAMESPACE_TD_END