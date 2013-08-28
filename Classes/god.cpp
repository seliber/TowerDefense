#include "god.h"
#include "tower.h"

NAMESPACE_TD_BEGIN

template<> ITDGod* CSingleton<ITDGod>::m_psSingleton = NULL;
CTDGod::CTDGod(){
	m_pTowerFactory = new CTowerFactory();
	m_pEnemyFactory = new CEnemyFactory();
}

TDObjectWeakPtr CTDGod::Create( const String& strType, const String& strName ){
	if ( strType == ITower::strTypeEnemy )
	{
		return m_pEnemyFactory->add( 0, strName );
	}
	return m_pTowerFactory->add( 0, strName );
}

void CTDGod::Remove(const String& strType, unsigned int id )
{
	if ( strType == ITower::strTypeTower )
	{
		m_pTowerFactory->remove( id );
	}
	else
	{
		m_pEnemyFactory->remove( id );
	}
}
void CTDGod::Remove( TDObjectWeakPtr ptr ){

}

void CTDGod::update( float dt ){
	//m_pEnemyFactory->Traversal( &CDelegate<CTDGod>(this, &CTDGod::UpdateObject ) );
	m_pTowerFactory->Traversal( &CDelegate<CTDGod>(this, &CTDGod::UpdateObject ) );
}

bool CTDGod::UpdateObject( void* ptr )
{
// 	ITDObject* pObject = (ITDObject*)(ptr);
// 	if ( pObject )
// 	{
// 		pObject->Update(0);
// 	}
	return false;
}

bool CTDGod::Traversal( const String& strType, CDelegateBase* pFun )
{
	if ( strType == "Tower" ){
		m_pTowerFactory->Traversal( pFun );
	}
	else{
		m_pEnemyFactory->Traversal( pFun );
	}
	return false;
}

TDObjectWeakPtr CTDGod::CTowerFactory::add( const unsigned int& key, const string& strType )
{
	ITDObject* pObject = 0;
	if ( strType == "Tower" )
	{
		pObject = ITower::create( "Tower", "2.png" );
	}
	else
	{
		pObject = ITower::create( "Tower", "2.png" );
	}
	makeAi( pObject );
	TDObjectSharePtr ptr( pObject );
	m_mapData[pObject->m_uID] = ptr;
	return TDObjectWeakPtr(ptr);
}

void CTDGod::CTowerFactory::makeAi( ITDObject* ptr )
{
	IAiMgr::GetSingletonPtr()->DecorateObject( ptr );
}

TDObjectWeakPtr CTDGod::CEnemyFactory::add( const unsigned int& key, const string& strType )
{
	ITDObject* pObject = 0;
	if ( strType == "Enemy" )
	{
		pObject = ITower::create( "Enemy", "player.png" );
	}
	else
	{
		pObject = ITower::create( "Enemy", "player.png" );
	}
	makeAi( pObject );
	TDObjectSharePtr ptr( pObject );
	m_mapData[pObject->m_uID] = ptr;
	return TDObjectWeakPtr(ptr);
}

void CTDGod::CEnemyFactory::makeAi( ITDObject* ptr )
{
	//IAiMgr::GetSingletonPtr()->DecorateObject( ptr );
}
NAMESPACE_TD_END