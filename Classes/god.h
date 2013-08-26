#pragma  once
#include "templclassdef.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDGod : public ITDGod{
public:
	static unsigned int CreateID(){
		static unsigned int wID = 0;
		return wID++;
	}
public:
	class CTowerFactory : public IContainer_Struct<unsigned int, ITDObject*>{
	public:	
		virtual ITDObject* add( const unsigned int& key, const string& strType );
		virtual void makeAi( ITDObject* ptr );
	};
	class CEnemyFactory : public IContainer_Struct<unsigned int, ITDObject*>{
	public:	
		virtual ITDObject* add( const unsigned int& key, const string& strType );
		virtual void makeAi( ITDObject* ptr );
	};
public:
	CTDGod();
	virtual ITDObject* Create( const String& strType, const String& strName );
	virtual void Remove( const String& strType, unsigned int id );
	virtual void Remove( TDObjectWeakPtr ptr );
	virtual bool Update(  float dt );
	virtual bool Traversal( const String& strType, CDelegateBase* pFun );
protected:
	virtual bool UpdateObject( void* ptr );
private:
	CTowerFactory* m_pTowerFactory;
	CEnemyFactory* m_pEnemyFactory;
};
NAMESPACE_TD_END