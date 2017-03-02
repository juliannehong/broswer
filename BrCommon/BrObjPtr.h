#pragma once

#include "BrInterface.h"

template<class T>
class CBrObjectPtr final
{
	T* pInterface;

public:

	CBrObjectPtr() : pInterface(nullptr) {}
	CBrObjectPtr(T* pInt, bool IsSoleOwner = false) : pInterface(pInt)
	{
		if(!IsSoleOwner)
		{
			AddRef();
		}
	}
	CBrObjectPtr(CBrObjectPtr<T> &other):pInterface(other.pInterface)
	{
		AddRef();
	}
	CBrObjectPtr(CBrObjectPtr<T> &&other): pInterface(other.pInterface)
	{
		other.pInterface = nullptr;
	}
	~CBrObjectPtr()
	{
		Release();
	}

	U32 AddRef()
	{
		if(pInterface)
		{
			return pInterface->AddRef();
		}
		return 0;
	}

	U32 Release()
	{
		U32 ret = 0;
		if(pInterface)
		{
			ret = pInterface->Release();
			pInterface = nullptr;
		}
		return ret;
	}

	T* operator->()
	{
		return pInterface;
	}

	CBrObjectPtr<T>& operator=(T* pOther)
	{
		Release();
		pInterface = pOther;
		AddRef();
		return *this;
	}

	CBrObjectPtr<T>& operator=(CBrObjectPtr<T> &pOther)
	{
		Release();
		pInterface = pOther.pInterface;
		AddRef();
		return *this;
	}

	CBrObjectPtr<T>& operator=(CBrObjectPtr<T> &&pOther)
	{
		Release();
		std::swap(pInterface,pOther.pInterface);
		return *this;
	}

};

