#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "templclassdef.h"

typedef CCNode INode;
typedef CCSprite ISprite;
typedef CCLayer ILayer;
typedef CCPoint IPoint;
typedef CCPointArray Path;
typedef unsigned int ID;

NAMESPACE_TD_BEGIN
class ITDObject;
class IAi;

class ITDObject : public ISprite{
	DEF_MEMBER( IAi*, m_pAI, AI )
	DEF_MEMBER( String, m_strType, Type)
public:
	ITDObject(const String& strType ) : m_pAI(0), m_strType( strType), m_strState("") {}
	virtual void ChangeState( const String& strState ) = 0;	
	int m_nHP;
protected:
	String m_strState;
};

typedef weak_ptr<ITDObject> TDObjectWeakPtr;
typedef shared_ptr<ITDObject> TDObjectSharePtr;
class ITDGod : public CSingleton<ITDGod>{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual TDObjectWeakPtr Create( const String& strType, const String& strName ) = 0;
	virtual void Remove( const String& strType, ID id ) = 0;
	virtual void Remove( TDObjectWeakPtr ptr ) = 0;
	virtual bool Traversal( const String& strType, CDelegateBase* pFun ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
	virtual bool GetObject( const String& strType, ID id, TDObjectWeakPtr& ptr ) = 0;
};

class ITDMap : public INode{
	DEF_MEMBER( CCLayer*, m_pLayer, Layer)
public:
	virtual Path* GetPath() = 0;
	virtual bool IsVisiblePosition( const IPoint* pt ) = 0;
protected:
	virtual bool LoadMap( const String& strFile) = 0;  
	friend class ITDMapMgr;
};

typedef weak_ptr<ITDMap> TDMapWeakPtr;
typedef shared_ptr<ITDMap> TDMapSharePtr;
class ITDMapMgr : public CSingleton<ITDMapMgr>,public IContainer_SharePtr<String,ITDMap>{
public:
	virtual bool Ini( const String& strPath ) = 0;
};


class IActionMgr : public CSingleton<IActionMgr>
{
public:
	virtual bool DoAction( const ITDObject* pTagObject, const String& strAction ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};


class ITDLevel : public INode{
public:
	virtual bool Start( ILayer* pLayer, Path* pPath ) = 0;
	virtual bool End() = 0;
protected:
	virtual bool LoadLevel( const String& strFile ) = 0;
	friend class ITDLevelMgr;
};

typedef weak_ptr<ITDLevel> TDLevelWeakPtr;
typedef shared_ptr<ITDLevel> TDLevelSharePtr;
class ITDLevelMgr : public CSingleton<ITDLevelMgr>, public IContainer_SharePtr<String,ITDLevel>
{
public:
	virtual bool Ini( const String& strPath ) = 0;
};

class IAi : public INode{
public:
	virtual void Update( float dt, ITDObject* pObject ) = 0;
};

typedef weak_ptr<IAi> IAiWeakPtr;
typedef shared_ptr<IAi> IAiSharePtr;
class IAiMgr : public IContainer_SharePtr<String,IAi>, public CSingleton<IAiMgr>{
public:
	virtual void DecorateObject( ITDObject* pObject ) = 0;
	virtual bool Ini( const String& strPath ) = 0;
};
NAMESPACE_TD_END