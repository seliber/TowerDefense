#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "templclassdef.h"

NAMESPACE_TD_BEGIN
class ITDObject;
class IAi{
public:
	virtual void Update( float dt, ITDObject* pObject ) = 0;
};

class IAiMgr : public IContainer_Struct<String,IAi*>, public CSingleton<IAiMgr>{
public:
	virtual void DecorateObject( ITDObject* pObject ) = 0;
};


class ITDObject : public CCSprite{
	DEF_MEMBER( IAi*, m_pAI, AI )
	DEF_MEMBER( TDObjectID, m_dwID, ID )
	DEF_MEMBER( String, m_strType, Type)
public:
	ITDObject(TDObjectID id, const String& strType ) : m_pAI(0), m_dwID(id), m_strType( strType), m_strState("") {}
	virtual void ChangeState( const String& strState ) = 0;
	virtual void Update( float dt ) = 0;
	void End( CCNode* pObject ){

	}
protected:
	String m_strState;
};

typedef weak_ptr<ITDObject> TDObjectWeakPtr;
typedef shared_ptr<ITDObject> TDObjectSharePtr;
class ITDGod : public CSingleton<ITDGod>{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual ITDObject* Create( const String& strType, const String& strName ) = 0;
	virtual void Remove( const String& strType, unsigned int id ) = 0;
	virtual void Remove( TDObjectWeakPtr ptr ) = 0;
	virtual bool Update( float dt ) = 0;
	virtual bool Traversal( const String& strType, CDelegateBase* pFun ) = 0;
};

typedef CCPointArray Path;
class ITDMap : public CSingleton<ITDMap>{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual bool IniMap( const String& strFile, CCLayer* pLayer ) = 0;
	virtual Path* GetPath() = 0;
protected:
	virtual bool LoadMap( const String& strFile) = 0;  
};

class IActionMgr : public CSingleton<IActionMgr>
{
public:
	virtual bool DoAction( const ITDObject* pTagObject, const String& strAction ) = 0;
};
NAMESPACE_TD_END