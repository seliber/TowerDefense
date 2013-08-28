#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "templclassdef.h"

NAMESPACE_TD_BEGIN
class ITDObject;
class IAi : public CCObject{
public:
	virtual void Update( float dt, ITDObject* pObject ) = 0;
};

typedef weak_ptr<IAi> IAiWeakPtr;
typedef shared_ptr<IAi> IAiSharePtr;
class IAiMgr : public IContainer_SharePtr<String,IAi>, public CSingleton<IAiMgr>, public CCObject{
public:
	virtual void DecorateObject( ITDObject* pObject ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};

class ITDObject : public CCSprite{
	DEF_MEMBER( IAi*, m_pAI, AI )
	DEF_MEMBER( String, m_strType, Type)
public:
	ITDObject(const String& strType ) : m_pAI(0), m_strType( strType), m_strState("") {}
	virtual void ChangeState( const String& strState ) = 0;	
protected:
	String m_strState;
};

typedef weak_ptr<ITDObject> TDObjectWeakPtr;
typedef shared_ptr<ITDObject> TDObjectSharePtr;
class ITDGod : public CSingleton<ITDGod>, public CCObject{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual TDObjectWeakPtr Create( const String& strType, const String& strName ) = 0;
	virtual void Remove( const String& strType, unsigned int id ) = 0;
	virtual void Remove( TDObjectWeakPtr ptr ) = 0;
	virtual bool Traversal( const String& strType, CDelegateBase* pFun ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};


typedef CCPointArray Path;
class ITDMap : public CCObject{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual Path* GetPath() = 0;
protected:
	virtual bool LoadMap( const String& strFile) = 0;  
	friend class ITDMapMgr;
};

typedef weak_ptr<ITDMap> TDMapWeakPtr;
typedef shared_ptr<ITDMap> TDMapSharePtr;
class ITDMapMgr : public CSingleton<ITDMapMgr>, public CCObject ,public IContainer_SharePtr<String,ITDMap>{
public:
	virtual ITDMap* GetMap( const String& strName ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};


class IActionMgr : public CSingleton<IActionMgr>, public CCObject
{
public:
	virtual bool DoAction( const ITDObject* pTagObject, const String& strAction ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};


class ITDLevel : public CCObject{
public:
protected:
	virtual bool LoadLevel( const String& strFile ) = 0;
	friend class ITDLevelMgr;
};

typedef weak_ptr<ITDLevel> TDLevelWeakPtr;
typedef shared_ptr<ITDLevel> TDLevelSharePtr;
class ITDLevelMgr : public CCObject, public CSingleton<ITDLevelMgr>, public IContainer_SharePtr<String,ITDLevel>
{
public:
	virtual ITDLevel* GetLevel( const String& strName ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};
NAMESPACE_TD_END