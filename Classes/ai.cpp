#include "ai.h"
#include "templclassdef.h"
#include "system.h"
#include "skill.h"

NAMESPACE_TD_BEGIN
const String CAttackAi::strTypeActtack = "Acttack";
CAttackAi::CAttackAi(){
	setType( strTypeActtack );
}

void CAttackAi::Update( float dt, ITDObject* pObject )
{
	if ( pObject == 0 )
	{
		return;
	}
	m_pSourceObject = pObject;
	ITDGod::GetSingletonPtr()->Traversal( &CDelegate<CAttackAi>(this, &CAttackAi::DoAi ),"Enemy" );
}

bool CAttackAi::DoAi( void* param )
{
	ITDObject* pTargetObject = (ITDObject*)param;
	if ( pTargetObject == 0 )
	{
		return false;
	}
	
	bool bCanAttack = collisionWithCircle( m_pSourceObject->getPosition(), 50, pTargetObject->getPosition(), 50 );
	if ( bCanAttack )
	{	
		CSkillMgr::GetSingletonPtr()->CreateSkill( "", m_pSourceObject, pTargetObject );	
		return true;
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