#pragma once
#include "cocos2d.h"
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class ITower : public ITDObject
{
public:
	static const String strTypeTower;
	static const String strTypeEnemy;
public:
	ITower( const String& strType );

	virtual void ChangeState( const String& strState ){}

	virtual void update(  float dt );

	static ITDObject* create( const String& strType, int nX, int nY, const char* pszFileName );

	static ITDObject* create( const String& strType, const char* pszFileName );

	static ITDObject* create( const String& strType, int nX, int nY, CCTexture2D* pTextrue2D );
};
NAMESPACE_TD_END