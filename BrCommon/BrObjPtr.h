#pragma once

#include "BrInterface.h"

template<class T>
class CObjectPtr final
{
	T* pInterface;

public:

	CObjectPtr() : pInterface(nullptr) {}
	CObjectPtr(T* pInt, bool IsSoleOwner = false) : pInterface(pInt)
	{
		if(!IsSoleOwner)
		{
			AddRef();
		}
	}
	CObjectPtr(CObjectPtr<T> &other):pInterface(other.pInterface)
	{
		AddRef();
	}
	CObjectPtr(CObjectPtr<T> &&other): pInterface(other.pInterface)
	{
		other.pInterface = nullptr;
	}

	template <typename Q,
		typename = std::enable_if_t<std::is_base_of<T, Q>::value>,
		char>
		CObjectPtr(CObjectPtr<Q> const& other)
	{
		//upcast - static casting is legal here.
		pInterface = (T*)other.pInterface;
		AddRef();
	}

	template <typename Q,
		typename = std::enable_if_t<std::is_base_of<Q, T>::value>,
		U32>
		CObjectPtr(CObjectPtr<Q> const& other)
	{
		//Downcast - use QueryInterface.
		pInterface->QueryInterface(GET_UUID(Q), (void**)&pInterface);
	}

	~CObjectPtr()
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

	T* GetInterface()
	{
		return pInterface;
	}

	CObjectPtr<T>& operator=(T* pOther)
	{
		Release();
		pInterface = pOther;
		AddRef();
		return *this;
	}

	CObjectPtr<T>& operator=(CObjectPtr<T> &pOther)
	{
		Release();
		pInterface = pOther.pInterface;
		AddRef();
		return *this;
	}

	CObjectPtr<T>& operator=(CObjectPtr<T> &&pOther)
	{
		Release();
		std::swap(pInterface,pOther.pInterface);
		return *this;
	}

	

};

