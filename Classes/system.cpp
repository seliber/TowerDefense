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
	IAiMgr::GetSingletonPtr()->Ini( strSourcePath );
	return false;
}

bool CSystem::Start( const String& strMap, CCLayer* pLayer )
{
	ITDMap* pMap = ITDMapMgr::GetSingletonPtr()->GetMap(0);
	if ( pMap )
	{
		pMap->DecorateLayer( pLayer );
		ITDLevel* pLevel = ITDLevelMgr::GetSingletonPtr()->GetLevel(0);
		if ( pLevel  )
		{
			return pLevel->Start( pLayer, pMap );
		}
	}
	return false;
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