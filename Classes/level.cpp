#include "level.h"
#include "god.h"
NAMESPACE_TD_BEGIN
template<> ITDLevelMgr* CSingleton<ITDLevelMgr>::m_psSingleton = NULL;

CLevel::CLevel():m_pLayer(0), m_pPath(0),m_wCurrentIndex(0),m_wEnemyCount(10),m_wTimeInterval(1){

}
void CLevel::update(float delta)
{
	static float dtTime = 0;
	dtTime+= delta;
	if ( dtTime < m_wTimeInterval || m_wCurrentIndex >= m_wEnemyCount )
	{
		return;
	}
	if ( m_pLayer == 0 || m_pPath == 0 )
	{
		return;
	}
	TDObjectWeakPtr ptr = ITDGod::GetSingletonPtr()->Create( "Enemy", "Enemy" );
	TDObjectSharePtr shptr = ptr.lock();
	if ( shptr )
	{
		do 
		{    
			m_pLayer->addChild( (ITDObject*)(shptr.get()) );
			shptr->setPosition( m_ptOrigin );
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
			CCCardinalSplineTo *action2 = CCCardinalSplineTo::create(5, m_pPath, 1 );
			CCCardinalSplineTo* reverse2 = (CCCardinalSplineTo*)action2->reverse();		
			//	CCSequence *seq2 = CCSequence::create(action2, reverse2, NULL);
			shptr->runAction(
				CCSequence::create(
				action,
				action2,
				//	reverse2,
//				CCCallFuncN::create( ptr, callfuncN_selector( ITDObject::End )),
				NULL));
			m_wCurrentIndex++;
		} while (0);
	}	
}

bool CLevel::Start( ILayer* pLayer, Path* pPath )
{
	if ( pLayer == 0 || pPath == 0 )
	{
		return false;
	}
	m_ptOrigin = pPath->getControlPointAtIndex( 0 );
	m_pLayer = pLayer;
	m_pLayer->addChild( this );
	m_pPath = pPath;
	this->scheduleUpdateWithPriority(1);
	return true;
}

bool CLevel::End()
{
	m_pLayer->removeChild( this, true );
	m_pLayer = 0;
	m_pPath = 0;
	m_wCurrentIndex = 0;
	m_wEnemyCount = 10;
	m_wTimeInterval = 1;
	this->unscheduleUpdate();
	return true;
}

NAMESPACE_TD_END