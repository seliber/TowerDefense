#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
using namespace std;

typedef string String;
typedef unsigned int TDObjectID;

#define NAMESPACE_TD_BEGIN namespace TD{
#define NAMESPACE_TD_END }
#define US_TD using namespace TD;

#define DEF_MEMBER( type, name, funcname) \
	protected: type name;\
	public: virtual type get##funcname(){return name;} \
	public: virtual void set##funcname(type var){ name = var; }

NAMESPACE_TD_BEGIN
class CDelegateBase    
{
public:
	CDelegateBase(void* pObject, void* pFn);
	CDelegateBase(const CDelegateBase& rhs);
	virtual ~CDelegateBase();
	bool Equals(const CDelegateBase& rhs) const;
	bool operator() (void* param);
	virtual CDelegateBase* Copy() const = 0; //

protected:
	void* GetFn();
	void* GetObject() {
		return m_pObject; 
	}
	virtual bool Invoke(void* param) = 0;

private:
	void* m_pObject;
	void* m_pFn;
};

class CDelegateStatic: public CDelegateBase
{
	typedef bool (*Fn)(void*);
public:
	CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) { } 
	CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { } 
	virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
	virtual bool Invoke(void* param){
		Fn pFn = (Fn)GetFn();
		return (*pFn)(param); 
	}
};

template <class T>
class CDelegate : public CDelegateBase
{
	typedef bool (T::* Fn)(void*);
public:
	CDelegate(T* pObj, Fn pFn) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
	CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; } 
	virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
	virtual bool Invoke(void* param)	{
		T* pObject = (T*) GetObject();
		return (pObject->*m_pFn)(param); 
	}  

private:
	Fn m_pFn;
};


template<class Key,class Data,class Type = string> class IContainer_SharePtr
{
protected:
	typedef map<Key,shared_ptr<Data> > Container;
	Container m_mapData;
public:
	virtual weak_ptr<Data> add( const Key& key, const Type& strType ) = 0;
	virtual ~IContainer_SharePtr(){}

	virtual bool get(const Key& key, weak_ptr<Data>& result){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() )
		{
			result = itr->second;
			return true;
		}
		return false;
	}

	virtual bool remove( const Key& key ){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() )
		{
			itr->second.reset();
			cout << itr->second.use_count() << endl;
			m_mapData.erase( itr );
			return true;
		}
		return false;
	}

	virtual void removeall(){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() )
		{
			itr->second.reset();	
			itr++;
		}
		m_mapData.clear();
	}
	unsigned int count(){
		return m_mapData.size();
	}

	virtual void traversal( CDelegateBase* pFun ){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() ){
			weak_ptr<Data> ptr( itr->second );
			if ( (*pFun)((void*)(&ptr)) == false ){
				return;
			}
			itr++;
		}
	} 
};

template<class Key,class Data> class IContainer_Struct
{
protected:
	typedef map<Key,Data> Container;
	Container m_mapData;
public:
	virtual ~IContainer_Struct(){}
	virtual void add( const Key& key, const Data& data ){
		m_mapData[key] = data;
	}

	virtual bool get(const Key& key, Data& data){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() )
		{
			data = itr->second;
			return true;
		}
		return false; 
	}

	virtual bool remove( const Key& key ){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() )
		{
			m_mapData.erase( itr );
			return true;
		}
		return false;
	}

	virtual void removeall(){
		m_mapData.clear();
	}
	unsigned int count(){
		return m_mapData.size();
	}

	virtual void traversal( CDelegateBase* pFun ){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() ){
			if ( (*pFun)( (void*)(itr->second) ) == false ){
				return;
			}
			itr++;
		}
	} 
};

template<typename T> class CSingleton
{
protected:
	static T* m_psSingleton;

public:
	CSingleton(){
		m_psSingleton = static_cast<T*>(this);
	}

	virtual ~CSingleton(){
		m_psSingleton = 0;
	}

	// 获取指针和对象
	static T& GetSingleton(){ return *m_psSingleton; }

	static T* GetSingletonPtr(){ return m_psSingleton; }
};
NAMESPACE_TD_END