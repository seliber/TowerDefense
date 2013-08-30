#include "ai.h"
#include "templclassdef.h"
#include "system.h"
#include "skill.h"

NAMESPACE_TD_BEGIN
void CAttackAi::Update( float dt, ITDObject* pObject )
{
	if ( pObject == 0 )
	{
		return;
	}
	m_pSourceObject = pObject;
	ITDGod::GetSingletonPtr()->Traversal( "Enemy",&CDelegate<CAttackAi>(this, &CAttackAi::DoAi ) );
}

bool CAttackAi::DoAi( void* param )
{
	TDObjectWeakPtr* pObject = (TDObjectWeakPtr*)param;

	if ( pObject == 0 )
	{
		return false;
	}
	TDObjectSharePtr shptrTarget = pObject->lock();

	if ( shptrTarget == 0 )
	{
		return false;
	}
	
	bool bCanAttack = collisionWithCircle( m_pSourceObject->getPosition(), 50, shptrTarget->getPosition(), 50 );
	if ( bCanAttack )
	{
		TDObjectWeakPtr weakptr;
		bool bRet = ITDGod::GetSingletonPtr()->GetObject( m_pSourceObject->getType(), m_pSourceObject->m_uID, weakptr );
		if ( bRet )
		{
			CSkillMgr::GetSingletonPtr()->CreateSkill( "", weakptr, *pObject );
		}
		return false;
	}
	return true;
}

bool CAttackAi::collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
{	
	float xdif = circlePoint.x - circlePointTwo.x;
	float ydif = circlePoint.y - circlePointTwo.y;

	float distance = sqrt(xdif * xdif + ydif * ydif);

	if(distance <= radius + radiusTwo) 
	{
		return true;
	}
	return false;	
}
NAMESPACE_TD_END