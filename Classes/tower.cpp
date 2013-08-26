#include "tower.h"

NAMESPACE_TD_BEGIN

const String ITower::strTypeEnemy = "Enemy";
const String ITower::strTypeTower = "Tower";

ITower::ITower( TDObjectID id, const String& strType ) : ITDObject( id, strType ){

}

ITDObject* ITower::create( const String& strType, TDObjectID id, const char* pszFileName )
{
	ITower* pBody = new ITower( id, strType );
	pBody->initWithFile( pszFileName );
	pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, TDObjectID id, int nX, int nY, const char* pszFileName )
{
	ITDObject* pBody = ITower::create( strType, id, pszFileName );
	pBody->setPosition( ccp(nX, nY) );
	pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, TDObjectID id, int nX, int nY, CCTexture2D* pTextrue2D )
{
	ITDObject* pBody = new ITower( id, strType );
	pBody->initWithTexture( pTextrue2D );
	pBody->setPosition( ccp(nX, nY) );
	pBody->autorelease();
	return pBody;
}

void ITower::Update( float dt )
{
	if ( m_pAI != 0 )
	{
		m_pAI->Update( dt, this );
	}
}

NAMESPACE_TD_END