#pragma once
#include "cocos2d.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
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

	DEF_MEMBER( TDObjectWeakPtr, m_pSourceObject, SourceObject )
	DEF_MEMBER( TDObjectWeakPtr, m_pTargetObject, TargetObject )
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