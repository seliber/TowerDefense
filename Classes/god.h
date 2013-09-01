#pragma  once
#include "templclassdef.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN

class CTDGod : public ITDGod{
public:
	CTDGod();
	~CTDGod();
	virtual ITDObject* Create( const String& strName, INode* pNode, const String& strType = "Enemy" );
	virtual void Remove( ID id, const String& strType = "" );
	virtual void Remove( ITDObject* pObject );
	virtual bool Traversal( CDelegateBase* pFun, const String& strType = "" );
	virtual bool Ini( const String& strPath );
	virtual ITDObject* GetObject( ID id, const String& strType = "" );

protected:
	virtual bool RemoveFromArray( cocos2d::CCArray* pArray, ID id );
	virtual bool TraversalFromArray( cocos2d::CCArray* pArray, CDelegateBase* pFun );
	virtual ITDObject* GetObjecFromArray( cocos2d::CCArray* pArray, ID id );
	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pTower, Towers );	
	CC_SYNTHESIZE_RETAIN( cocos2d::CCDictionary*, m_pSpriteBatchNode, SpriteBatchNode );	
	CC_SYNTHESIZE_RETAIN( cocos2d::CCArray*, m_pEnemy, Enemys );	
};
NAMESPACE_TD_END