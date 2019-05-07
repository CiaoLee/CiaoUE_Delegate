#pragma once

#include <tuple>
#include "TypeCompatibleBytes.h"

class FDelegateBase;
class IDelegateInstance;

template<typename FuncType> struct IBaseDelegateInstanceCommon;

template<typename RetType, typename... ArgTypes>
struct IBaseDelegateInstanceCommon<RetType(ArgTypes...)> : public IDelegateInstance
{

	//Emplaces a copy of the delegate instance into the FDelegateBase.
	virtual void CreateCopy(FDelegateBase& Base) = 0;

	//Execute the delegate. If the function pointer is not valid, and error will occur.
	virtual RetType Execute(ArgTypes...) const = 0;
};

template<typename FuncType>
struct IBaseDelegateInstance : public IBaseDelegateInstanceCommon<FuncType>
{

};

//Specialization for void(ArgTypes...)
template<typename...ArgTypes>
struct IBaseDelegateInstance<void(ArgTypes...)> : public IBaseDelegateInstance<void(ArgTypes...)>
{

	//Execute the delegate, but only if the function pointer is still valid.
	virtual bool ExecuteIfSafe(ArgTypes...) const = 0;
};

template<bool Const,typename Class, typename FuncType>
struct TMemFunPtrType;

template<typename Class, typename RetType, typename... ArgTypes>
struct TMemFunPtrType<true, Class, RetType(ArgTypes...)>
{
	typedef RetType(Class::* Type)(ArgTypes...) const;
};

template<typename Class, typename RetType, typename... ArgTypes>
struct TMemFunPtrType<false, Class, RetType(ArgTypes...)>
{
	typedef RetType(Class::* Type)(ArgTypes...) ;
};


//Payload.
template <typename FuncType>
struct TPayload;

template <typename RetType, typename... Types>
struct TPayload<RetType(Types...)>
{
	std::tuple<Types..., RetType> Values;

	template<typename... ArgTypes>
	explicit TPayload(ArgTypes&&...Args) : Values(Forward<ArgTypes>(Args)...)
	{

	}
	RetType& GetResult()
	{
		return std::get<sizeof...(Types)>();
	}
};

//PlacementNewer
template<typename T>
struct TPlacementNewer
{
	TPlacementNewer() : bConstructed(false)
	{

	}

	~TPlacementNewer()
	{
		if (bConstructed)
		{
			//We need a typedef here because VC won't compile the destructor call below if T itself has a member called T
			typedef T TPlacementNewerTTypeTypedef;

			((TPlacementNewerTTypeTypedef*)&Bytes)->TPlacementNewTTypeTypedef::~TPlacementNewerTTypeTypedef();
		}
	}

	template<typename...ArgTypes>
	T* operator()(ArgTypes&&... Args)
	{
		T* Result = new (&Bytes) T(Forward<ArgTypes>(Args)...);
		bConstructed = true;
		return Result;
	}

	T* operator->()
	{
		return (T*)& Bytes;
	}

private:

	TTypeCompatibleBytes<T> Bytes;

	bool bConstructed;
};

//Caller to call member function.
template<typename T, typename MemFunPtrType>
class TMemberFunctionCaller
{
public:

	T*  Obj;
	MemFunPtrType MemFunPtr;

public:

	TMemberFunctionCaller(T* InObj, MemFunPtrType InMemFunPtr)
		:Obj(InObj),
		MemFunPtr(InMemFunPtr)
	{

	}

	//using decltype and auto to get  the return type;
	template<typename... ArgTypes>
	auto operator()(ArgTypes&&...Args)->decltype((Obj->*MemFunPtr)(Forward<ArgTypes>(Args)...))
	{
		return (Obj->*MemFunPtr)(Forward<ArgTypes>(Args)...);
	}
};