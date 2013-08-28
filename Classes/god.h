#pragma  once
#include "templclassdef.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDGod : public ITDGod{
public:
	class CTowerFactory : public IContainer_SharePtr<unsigned int, ITDObject>{
	public:	
		virtual TDObjectWeakPtr add( const unsigned int& key, const string& strType );
	protected:
		virtual void makeAi( ITDObject* ptr );
	};
	class CEnemyFactory : public IContainer_SharePtr<unsigned int, ITDObject>{
	public:	
		virtual TDObjectWeakPtr add( const unsigned int& key, const string& strType );
	protected:
		virtual void makeAi( ITDObject* ptr );
	};
public:
	CTDGod();
	virtual bool Ini( const String& strPath ){return false;}
	virtual TDObjectWeakPtr Create( const String& strType, const String& strName );
	virtual void Remove( const String& strType, unsigned int id );
	virtual void Remove( TDObjectWeakPtr ptr );
	virtual void update(float dt);
	virtual bool Traversal( const String& strType, CDelegateBase* pFun );
protected:
	virtual bool UpdateObject( void* ptr );
private:
	CTowerFactory* m_pTowerFactory;
	CEnemyFactory* m_pEnemyFactory;
};
NAMESPACE_TD_END