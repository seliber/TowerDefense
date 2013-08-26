#pragma once
#include "cocos2d.h"
#include "templclassdef.h"
USING_NS_CC;

NAMESPACE_TD_BEGIN
typedef weak_ptr<CCScene> SceneWeakPtr;
typedef shared_ptr<CCScene> SceneSharePtr;
class CSceneMgr : public IContainer_SharePtr<String,CCScene>, public CSingleton<CSceneMgr>{
public:
	virtual SceneWeakPtr add( const String& key, const String& strType );
};
NAMESPACE_TD_END