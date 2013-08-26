#include "ai.h"
#include "templclassdef.h"
#include "system.h"

NAMESPACE_TD_BEGIN
void CAttackAi::Update( float dt, ITDObject* pObject )
{
	m_pSourceObject = pObject;
	ITDGod::GetSingletonPtr()->Traversal( "Enemy",&CDelegate<CAttackAi>(this, &CAttackAi::DoAi ) );
}

bool CAttackAi::DoAi( void* param )
{
	ITDObject* pObject = (ITDObject*)param;
	bool bCanAttack = collisionWithCircle( m_pSourceObject->getPosition(), 0, pObject->getPosition(), 0 );
	if ( bCanAttack )
	{
		ITDGod::GetSingletonPtr()->Remove( pObject->getType(), pObject->getID() );
		CSystem::GetSingletonPtr()->RemoveObject( pObject );	
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