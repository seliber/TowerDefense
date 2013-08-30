#include "tower.h"

NAMESPACE_TD_BEGIN

const String ITower::strTypeEnemy = "Enemy";
const String ITower::strTypeTower = "Tower";

ITower::ITower( const String& strType ) : ITDObject( strType ){
	m_nHP = 10;
}

ITDObject* ITower::create( const String& strType, const char* pszFileName )
{
	ITower* pBody = new ITower( strType );
	pBody->initWithFile( pszFileName );
	//pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, int nX, int nY, const char* pszFileName )
{
	ITDObject* pBody = ITower::create( strType, pszFileName );
	pBody->setPosition( ccp(nX, nY) );
	//pBody->autorelease();
	return pBody;
}

ITDObject* ITower::create( const String& strType, int nX, int nY, CCTexture2D* pTextrue2D )
{
	ITDObject* pBody = new ITower( strType );
	pBody->initWithTexture( pTextrue2D );
	pBody->setPosition( ccp(nX, nY) );
	//pBody->autorelease();
	return pBody;
}

void ITower::ChangeState( const String& strState )
{
	CCActionInterval*  action1 = CCTintTo::create(0.3, 255, 0, 255);
	CCActionInterval*  action2 = CCTintBy::create(0.3, -127, -255, -127);
	CCActionInterval*  action2Back = action2->reverse();

	runAction( action1);
	runAction( CCSequence::create( action2, action2Back, NULL));

}

void ITower::update( float dt )
{
// 	static float time = 0;
// 	time+= dt;
// 	if ( time < 1 )
// 	{
// 		return;
// 	}
// 	time = 0;
	if ( m_pAI != 0 )
	{
		m_pAI->Update( dt, this );
	}
}

void ITower::End()
{
	
}

NAMESPACE_TD_END