#include "templclassdef.h"
NAMESPACE_TD_BEGIN
CDelegateBase::CDelegateBase(void* pObject, void* pFn) 
{
	m_pObject = pObject;
	m_pFn = pFn; 
}

CDelegateBase::CDelegateBase(const CDelegateBase& rhs) 
{
	m_pObject = rhs.m_pObject;
	m_pFn = rhs.m_pFn; 
}

CDelegateBase::~CDelegateBase()
{

}

bool CDelegateBase::Equals(const CDelegateBase& rhs) const 
{
	return m_pObject == rhs.m_pObject && m_pFn == rhs.m_pFn; 
}

bool CDelegateBase::operator() (void* param) 
{
	return Invoke(param); 
}

void* CDelegateBase::GetFn() 
{
	return m_pFn; 
}

NAMESPACE_TD_END