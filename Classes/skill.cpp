#include "skill.h"
#include "system.h"
NAMESPACE_TD_BEGIN

const String ISkill::strTypeSkill = "Skill";

template<> CSkillMgr* CSingleton<CSkillMgr>::m_psSingleton = NULL;

ISkill::ISkill( const String& strType ) : ITDObject( strType ){
	 m_ptSpeed = ccp(5,5);
}

ITDObject* ISkill::create( const String& strName, TDObjectWeakPtr source, TDObjectWeakPtr target )
{
	ISkill* pSkill = new ISkill( strName );
	pSkill->initWithFile( "skill.png" );
	pSkill->setTargetObject( target );
	pSkill->setSourceObject( source );
	return pSkill;
}


bool collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
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

float ISkill::calcAngle(CCPoint target) {
	float r = 0;
	CCPoint p2 = ccpSub(target, this->getPosition());
	r = ccpAngle(m_ptSpeed, p2); //计算夹角r是弧度值，不是角度值
	return r;
}

RotateDirection ISkill::calcDirection(CCPoint target) {
	CCPoint p2 = ccpSub(target, this->getPosition());
	if (ccpCross(m_ptSpeed, p2) > 0) {
		// 在opengl的右手坐标系中，向量叉乘大于0表示逆时针方向
		return COUNTERCLOCKWISE;
	} else if (ccpCross(m_ptSpeed, p2) < 0) {
		return CLOCKWISE;
	} else {
		return NO_ROTATE;
	}
}

void ISkill::move( CCPoint ptTarget ) {

	//step 1:确定角度
	//计算夹角r是弧度值，不是角度值
	float _rad = calcAngle(ptTarget); 
// 	if (_rad && _rad >= PI / 2) {
// 		//角度大于90的时候放弃，不追踪
// 		mTarget = NULL;
// 		break;
// 	}
	float _deg = CC_RADIANS_TO_DEGREES(_rad);

	float deltaR = _rad ;//< mDeltaRadians ? _rad : mDeltaRadians;
	//	float deltaD = _deg < mDeltaDegree ? _deg : mDeltaDegree;

	//step 2:确定方向
	switch (calcDirection( ptTarget )) {
	case COUNTERCLOCKWISE: {
		m_ptSpeed = ccpRotateByAngle(m_ptSpeed, ccp(0,0), deltaR);
	//	this->setRotation(this->getRotation() - deltaD);
		break;
						   }
	case CLOCKWISE: {
		m_ptSpeed = ccpRotateByAngle(m_ptSpeed, ccp(0,0), -deltaR);
	//	this->setRotation(this->getRotation() + deltaD);
		break;
					}
	default:
		break;
	}
		
	this->setPosition(ccpAdd(getPosition(), m_ptSpeed));
}

void ISkill::update( float dt )
{
	TDObjectSharePtr shptrSource = m_pSourceObject.lock();
	TDObjectSharePtr shptrTarget = m_pTargetObject.lock();
	if ( shptrTarget == 0 || shptrSource == 0 )
	{
		this->removeFromParentAndCleanup( true );
	//	CSkillMgr::GetSingletonPtr()->remove( m_uID );
		return;
	}

	move( shptrTarget->getPosition() );

	if ( collisionWithCircle( this->getPosition(), 10, shptrTarget->getPosition(), 10 ) )
	{
		this->removeFromParentAndCleanup( true );
		shptrTarget->ChangeState("");
		//CSkillMgr::GetSingletonPtr()->remove( m_uID );
// 		shptrTarget->m_nHP--;
// 		if ( shptrTarget->m_nHP == 0 )
// 		{
			shptrTarget->removeFromParentAndCleanup( true );
			ITDGod::GetSingletonPtr()->Remove( m_pTargetObject );
// 		}	
		return;
	}
	//this->stopAllActions();
	//this->runAction( CCMoveTo::create( 1/60, shptrTarget->getPosition() ) );
}



bool CSkillMgr::CreateSkill( const String& strName, TDObjectWeakPtr source, TDObjectWeakPtr target )
{
	SkillWeakPtr ptr = add( 0, strName );
	SkillSharePtr shptr = ptr.lock();
	TDObjectSharePtr objshptr = source.lock();
	if ( objshptr )
	{
		if ( shptr )
		{		
			shptr->setSourceObject( source ); 
			shptr->setTargetObject( target );	
			shptr->setPosition( objshptr->getPosition() );
			objshptr->getParent()->addChild( (INode*)shptr.get() );
			shptr->scheduleUpdate();
		}
	}

	return false;
}

SkillWeakPtr CSkillMgr::add( const unsigned int& key, const string& strType )
{
	ISkill* pSkill = new ISkill(strType);	
	pSkill->initWithFile( "skill.png" );
	SkillSharePtr ptr(pSkill);
	m_mapData[pSkill->m_uID] = ptr;
	return SkillWeakPtr(ptr);
}

NAMESPACE_TD_END