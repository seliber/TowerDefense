#include "aimgr.h"
#include "ai.h"
NAMESPACE_TD_BEGIN

CAiMgr::CAiMgr(){
	m_pAis = NULL;
}
CAiMgr::~CAiMgr(){
	CC_SAFE_RELEASE_NULL( m_pAis );
}
void CAiMgr::DecorateObject( ITDObject* pObject )
{
	static IAi* pAi = (IAi*)m_pAis->objectAtIndex(0);
	pObject->setAI( pAi );
}

IAi* CAiMgr::GetAi( const String& strType )
{
	IObject* pObject = NULL;
	CCARRAY_FOREACH(m_pAis, pObject)
	{
		IAi* pAi = dynamic_cast<IAi*>( pObject );
		if ( pAi && pAi->getType() == strType )
		{
			return pAi;
		}
	}
	return NULL;
}

bool CAiMgr::Ini( const String& strPath ){
	setAis( CCArray::createWithCapacity(10) );
	IAi* pAi = new CAttackAi();
	pAi->autorelease();
	m_pAis->addObject( pAi );
	return false;
}

NAMESPACE_TD_END