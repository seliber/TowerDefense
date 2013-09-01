#pragma once
#include "interfacedef.h"

NAMESPACE_TD_BEGIN
class CAttackAi : public IAi
{
public:
	static const String strTypeActtack;
public:
	CAttackAi();
	void Update( float dt, ITDObject* pObject );

protected:
	bool DoAi( void* param );

	bool collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo);

	DEF_MEMBER( ITDObject*, m_pSourceObject, SourceObject )
};

NAMESPACE_TD_END