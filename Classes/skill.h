#pragma once
#include "cocos2d.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

typedef enum emRotateDirection{
		COUNTERCLOCKWISE,
		CLOCKWISE,
		NO_ROTATE
}RotateDirection;
class ISkill : public ITDObject
{
	ISkill( const String& strType );
public:
	~ISkill();
	static const String strTypeSkill;

	virtual void ChangeState( const String& strState ){}

	virtual void update(  float dt );

	static ISkill* create( const String& strName, ITDObject* source, ITDObject* target );

	virtual void End();

protected:
	RotateDirection calcDirection(CCPoint target);
	float calcAngle(CCPoint target);
	void move( CCPoint ptTarget );
	CC_SYNTHESIZE_RETAIN( ITDObject*, m_pSourceObject, SourceObject )
	CC_SYNTHESIZE_RETAIN( ITDObject*, m_pTargetObject, TargetObject )
	CC_SYNTHESIZE( IPoint, m_ptSpeed, Speed)
	friend class CSkillMgr;
};


class CSkillMgr : public CSingleton<CSkillMgr>
{
public:
	CSkillMgr();
	~CSkillMgr();
	ISkill* CreateSkill( const String& strName, ITDObject* source, ITDObject* target );
	ISkill* GetSkill( const unsigned int& key );

	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pSkills, Skills )
};
NAMESPACE_TD_END