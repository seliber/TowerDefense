#include "tower.h"

NAMESPACE_TD_BEGIN

const String ITower::strTypeEnemy = "Enemy";
const String ITower::strTypeTower = "Tower";

ITower::ITower( const String& strType ) : ITDObject( strType ){

}

ITDObject* ITower::create( const String& strType, const char* pszFileName )
{
	ITower* pBody = new ITower( strType );
	pBody->initWithFile( pszFileName );
	pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, int nX, int nY, const char* pszFileName )
{
	ITDObject* pBody = ITower::create( strType, pszFileName );
	pBody->setPosition( ccp(nX, nY) );
	pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, int nX, int nY, CCTexture2D* pTextrue2D )
{
	ITDObject* pBody = new ITower( strType );
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