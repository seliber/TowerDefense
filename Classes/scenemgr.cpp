#include "scenemgr.h"
#include "beginscene.h"
#include "FinishSes.h"
#include "HelloWorldScene.h"

NAMESPACE_TD_BEGIN
template<> CSceneMgr* CSingleton<CSceneMgr>::m_psSingleton = NULL;
SceneWeakPtr CSceneMgr::add( const String& key, const String& strType )
{
	CCScene* pScene = 0;
	if ( strType == "Begin" )
	{
		pScene = CBegin::scene();
	}
	else if ( strType == "Finish" )
	{
		pScene = CFinish::scene();
	}
	else
	{
		pScene = HelloWorld::scene();
	}
	SceneSharePtr ptr(pScene);
	m_mapData[key] = ptr;
	return SceneWeakPtr(ptr);
}
NAMESPACE_TD_END