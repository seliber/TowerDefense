#include "level.h"
#include "god.h"
NAMESPACE_TD_BEGIN
template<> ITDLevelMgr* CSingleton<ITDLevelMgr>::m_psSingleton = NULL;

CLevel::CLevel():m_pLayer(0),m_wCurrentIndex(0),m_wEnemyCount(100),m_wTimeInterval(2){

}

void CLevel::update(float delta)
{
	static float dtTime = 0;
	dtTime+= delta;
	if ( dtTime < m_wTimeInterval || m_wCurrentIndex >= m_wEnemyCount )
	{
		return;
	}
	if ( m_pLayer == 0 )
	{
		return;
	}
	dtTime = 0;

	TDObjectWeakPtr ptr = ITDGod::GetSingletonPtr()->Create( "Enemy", "Enemy" );
	TDObjectSharePtr shptr = ptr.lock();
	TDMapSharePtr shptrTDMap = m_pMap.lock();
	if ( shptr && shptrTDMap )
	{
		do 
		{    
			m_pLayer->addChild( (ITDObject*)(shptr.get()) );
			
			CCAnimation* animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("2.png");
			animation->addSpriteFrameWithFileName("3.png");
			animation->addSpriteFrameWithFileName("2.png");
			animation->addSpriteFrameWithFileName("3.png");
	
			// should last 2.8 seconds. And there are 14 frames.
			animation->setDelayPerUnit(2.8f / 14.0f);
			animation->setRestoreOriginalFrame(true);

			CCAnimate* action = CCAnimate::create(animation);
			CCCardinalSplineTo *action2;

			int nTime = 5;
			if ( m_wCurrentIndex % 3 == 0 )
			{
				action2 = CCCardinalSplineTo::create(nTime, shptrTDMap->GetPath(), 1 );
				shptr->setPosition( shptrTDMap->GetPath()->getControlPointAtIndex(0) );
			}
			else if ( m_wCurrentIndex % 3 == 1 )
			{
				action2 = CCCardinalSplineTo::create(nTime, shptrTDMap->GetPath(1), 1 );
				shptr->setPosition(  shptrTDMap->GetPath(1)->getControlPointAtIndex(0) );
			}
			else
			{
				action2 = CCCardinalSplineTo::create(nTime, shptrTDMap->GetPath(2), 1 );
				shptr->setPosition( shptrTDMap->GetPath(2)->getControlPointAtIndex(0) );
			}
			
			CCCardinalSplineTo* reverse2 = (CCCardinalSplineTo*)action2->reverse();		
			//	CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
			shptr->runAction( CCSequence::create( action, 
				action2,
				// CCCallFuncN::create( this, callfuncN_selector(CLevel::ObjectFinished) ),
				NULL));
			m_wCurrentIndex++;
		} while (0);
	}	
}

bool CLevel::Start( ILayer* pLayer, TDMapWeakPtr pPath )
{
	if ( pLayer == 0 )
	{
		return false;
	}
	m_pLayer = pLayer;
	m_pLayer->addChild( this );
	m_pMap = pPath;
	this->scheduleUpdateWithPriority(1);
	return true;
}

bool CLevel::End()
{
	m_pLayer->removeChild( this, true );
	m_pLayer = 0;
	m_wCurrentIndex = 0;
	m_wEnemyCount = 10;
	m_wTimeInterval = 1;
	this->unscheduleUpdate();
	return true;
}

void CLevel::ObjectFinished( CCNode* pNode )
{
//	pNode->stopAllActions();
//	m_pLayer->removeChild( pNode, true );
//	pNode->removeFromParentAndCleanup( true );
//	ITDGod::GetSingletonPtr()->Remove( "Enemy", pNode->m_uID );
}

NAMESPACE_TD_END