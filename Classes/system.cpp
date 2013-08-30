#include "system.h"
#include "map.h"
#include "god.h"
#include "actionmgr.h"
#include "aimgr.h"
#include "level.h"
#include "skill.h"
NAMESPACE_TD_BEGIN

template<> CSystem* CSingleton<CSystem>::m_psSingleton = 0;
template<> IAiMgr* CSingleton<IAiMgr>::m_psSingleton = 0;

CSystem::CSystem()
{
	if ( ITDGod::GetSingletonPtr() == 0 ){
		new CTDGod();
	}
	if ( ITDMapMgr::GetSingletonPtr() == 0 )
	{
		new CTDMapMgr();
	}
	if ( IActionMgr::GetSingletonPtr() == 0 )
	{
		new CActionMgr();
	}
	if ( IAiMgr::GetSingletonPtr() == 0 )
	{
		new CAiMgr();
	}
	if ( ITDLevelMgr::GetSingletonPtr() == 0 )
	{
		new CLevelMgr();
	}
	if ( CSkillMgr::GetSingletonPtr() == 0 )
	{
		new CSkillMgr();
	}
}

bool CSystem::Launch( const String& strSourcePath )
{
	ITDMapMgr::GetSingletonPtr()->Ini( strSourcePath );
	ITDLevelMgr::GetSingletonPtr()->Ini( strSourcePath );
	ITDGod::GetSingletonPtr()->Ini( strSourcePath );

	ITDMapMgr::GetSingletonPtr()->add("1","1");
	ITDLevelMgr::GetSingletonPtr()->add("1","1");
	return false;
}

bool CSystem::Start( const String& strMap, CCLayer* pLayer )
{
	m_pLayer = pLayer;
	TDMapWeakPtr tdmap;
	if ( !ITDMapMgr::GetSingletonPtr()->get( strMap, tdmap) )
	{
		return false;
	}
	TDMapSharePtr shtdmap = tdmap.lock();
	if ( !shtdmap )
	{
		return false;
	}
	shtdmap->DecorateLayer( pLayer );
	TDLevelWeakPtr level;
	if ( ITDLevelMgr::GetSingletonPtr()->get( strMap, level ) )
	{
		TDLevelSharePtr shLevel = level.lock();
		if ( shLevel )
 		{

			shLevel->Start( pLayer,tdmap );
		}
	}
	return true;
}

bool CSystem::Pause()
{
	CCDirector::sharedDirector()->pause();
	return true;
}

bool CSystem::Resume()
{
	CCDirector::sharedDirector()->resume();
	return true;
}

bool CSystem::End()
{
	return true;
}

NAMESPACE_TD_END