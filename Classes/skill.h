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
	static const String strTypeSkill;

	virtual void ChangeState( const String& strState ){}

	virtual void update(  float dt );

//	static ITDObject* create( const String& strName, TDObjectWeakPtr source );

	static ITDObject* create( const String& strName, TDObjectWeakPtr source, TDObjectWeakPtr target );

//	static ITDObject* create( const String& strName, TDObjectWeakPtr source, CCPoint pt );

protected:
	RotateDirection calcDirection(CCPoint target);
	float calcAngle(CCPoint target);
	void move( CCPoint ptTarget );
	DEF_MEMBER( TDObjectWeakPtr, m_pSourceObject, SourceObject )
	DEF_MEMBER( TDObjectWeakPtr, m_pTargetObject, TargetObject )
	DEF_MEMBER( IPoint, m_ptSpeed, Speed)
	friend class CSkillMgr;
};


typedef weak_ptr<ISkill> SkillWeakPtr;
typedef shared_ptr<ISkill> SkillSharePtr;
class CSkillMgr : public IContainer_SharePtr<unsigned int ,ISkill>, public CSingleton<CSkillMgr>
{
public:
	bool CreateSkill( const String& strName, TDObjectWeakPtr source, TDObjectWeakPtr target );
	SkillWeakPtr add( const unsigned int& key, const string& strType );
};
NAMESPACE_TD_END