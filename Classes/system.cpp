#include "system.h"
#include "map.h"
#include "god.h"
#include "actionmgr.h"
#include "aimgr.h"
NAMESPACE_TD_BEGIN

template<> CSystem* CSingleton<CSystem>::m_psSingleton = 0;
template<> IAiMgr* CSingleton<IAiMgr>::m_psSingleton = 0;
template<> IBoss* CSingleton<IBoss>::m_psSingleton = 0;
CSystem::CSystem()
{
	if ( ITDGod::GetSingletonPtr() == 0 ){
		new CTDGod();
	}
	if ( ITDMap::GetSingletonPtr() == 0 )
	{
		new CTDMap();
	}
	if ( IActionMgr::GetSingletonPtr() == 0 )
	{
		new CActionMgr();
	}
	if ( IAiMgr::GetSingletonPtr() == 0 )
	{
		new CAiMgr();
	}
	if ( IBoss::GetSingletonPtr() == 0 )
	{
		new IBoss();
	}
}

bool CSystem::Launch( const String& strMap, CCLayer* pLayer )
{
	CTDMap::GetSingletonPtr()->IniMap( strMap, pLayer );
	ITDGod::GetSingletonPtr()->setLayer( pLayer );
	m_pLayer = pLayer;
	return true;
}

bool CSystem::Update( CCLayer* pLayer, float dt )
{
	IBoss::GetSingletonPtr()->Update( pLayer, dt );
	ITDGod::GetSingletonPtr()->Update( dt );
	return true;
}

bool IBoss::Update( CCLayer* pLayer, float dt )
{
	ITDObject* ptr = ITDGod::GetSingletonPtr()->Create( "Enemy", "Enemy" );
	if ( ptr )
	{
		do 
		{    
			if ( pLayer )
			{
				pLayer->addChild(ptr);
				ptr->setPosition( ccp( 20,20 ) );
				CCAnimation* animation = CCAnimation::create();
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				animation->addSpriteFrameWithFileName("2.png");
				animation->addSpriteFrameWithFileName("3.png");
				
				// should last 2.8 seconds. And there are 14 frames.
				animation->setDelayPerUnit(2.8f / 14.0f);
				animation->setRestoreOriginalFrame(true);

				CCAnimate* action = CCAnimate::create(animation);
				CCCardinalSplineTo *action2 = CCCardinalSplineTo::create(5, ITDMap::GetSingletonPtr()->GetPath(), 1 );
				CCCardinalSplineTo* reverse2 = (CCCardinalSplineTo*)action2->reverse();		
			//	CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
				ptr->runAction(
					CCSequence::create(
					action,
					action2,
				//	reverse2,
					 CCCallFuncN::create( ptr, callfuncN_selector( ITDObject::End )),
					NULL));
			}
			else{
				return false;
			}

		} while (0);
	}
	return true;
}

void CSystem::RemoveObject( ITDObject* pObject )
{
	m_pLayer->removeChild( pObject );
}
NAMESPACE_TD_END