#include "skill.h"
#include "system.h"
NAMESPACE_TD_BEGIN

const String ISkill::strTypeSkill = "Skill";

template<> CSkillMgr* CSingleton<CSkillMgr>::m_psSingleton = NULL;

ISkill::ISkill( const String& strType ) : ITDObject( strType ){

}

ITDObject* ISkill::create( const String& strName, TDObjectWeakPtr source, TDObjectWeakPtr target )
{
	ISkill* pSkill = new ISkill( strName );
	pSkill->initWithFile( "skill.png" );
	pSkill->setTargetObject( target );
	pSkill->setSourceObject( source );
	return pSkill;
}

IPoint speed = ccp( 10,10);
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

float calcAngle(IPoint ptSource, IPoint ptTarget) {
	float r = 0;
	CCPoint p2 = ccpSub( ptTarget ,ptSource );
	r = ccpAngle( ccp(10,10), p2); //计算夹角r是弧度值，不是角度值
	return r;
}

int calcDirection(IPoint ptSource, IPoint ptTarget) {
	CCPoint p2 = ccpSub(ptTarget, ptSource);
	if (ccpCross(speed, p2) > 0) {
		// 在opengl的右手坐标系中，向量叉乘大于0表示逆时针方向
		return 0;
	} else if (ccpCross(speed, p2) < 0) {
		return 1;
	} else {
		return 2;
	}
}

void move(IPoint ptSource, IPoint mTarget)
{
	do {
		if (mTarget) {
			//step 1:确定角度
			//计算夹角r是弧度值，不是角度值
			float _rad = calcAngle( ptSource, mTarget ); 
		
			float _deg = CC_RADIANS_TO_DEGREES(_rad);

			float deltaR = _rad;
			float deltaD = _deg;

			//step 2:确定方向
			switch (calcDirection( ptSource, mTarget )) {
			case 0: {
				speed = ccpRotateByAngle(speed, ccp(0,0), deltaR);
				/*this->setRotation(this->getRotation() - deltaD);*/
				break;
								   }
			case 1: {
				speed = ccpRotateByAngle(speed, ccp(0,0), -deltaR);
				//this->setRotation(this->getRotation() + deltaD);
				break;
							}
			default:
				break;
			}

		} else {
			//seekEnemy();
		}
	} while (0);
//	this->setPosition(ccpAdd( ptSource, speed));
}


void ISkill::update( float dt )
{
	static float time = 0;
	time += dt;
	if ( time < 2 )
	{
		return;
	}
	time = 0;
	TDObjectSharePtr shptrSource = m_pSourceObject.lock();
	TDObjectSharePtr shptrTarget = m_pTargetObject.lock();
	if ( shptrTarget == 0 || shptrSource == 0 )
	{
		this->removeFromParentAndCleanup( true );
		return;
	}
	if ( collisionWithCircle( this->getPosition(), 10, shptrTarget->getPosition(), 10 ) )
	{
		this->removeFromParentAndCleanup( true );
		shptrTarget->removeFromParentAndCleanup( true );
		ITDGod::GetSingletonPtr()->Remove( m_pTargetObject );
		return;
	}
	this->stopAllActions();
	this->runAction( CCMoveTo::create( 3, shptrTarget->getPosition() ) );
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
			objshptr->getParent()->addChild( (INode*)shptr.get() );
			shptr->scheduleUpdateWithPriority( 4 );
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