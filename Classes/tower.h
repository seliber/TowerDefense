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
	ITower( TDObjectID id, const String& strType );

	virtual void ChangeState( const String& strState ){}

	virtual void Update(  float dt );

	static ITDObject* create( const String& strType, TDObjectID id, int nX, int nY, const char* pszFileName );

	static ITDObject* create( const String& strType, TDObjectID id, const char* pszFileName );

	static ITDObject* create( const String& strType, TDObjectID id, int nX, int nY, CCTexture2D* pTextrue2D );
};

class ISkill : public ITDObject{
public:

};
NAMESPACE_TD_END