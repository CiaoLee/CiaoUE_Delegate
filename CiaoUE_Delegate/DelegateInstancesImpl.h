#pragma once

#include <tuple>
#include <type_traits>
#include "TemplateHelper.h"
#include "TupleUtility.h"
#include "IDelegateInstance.h"
#include "DelegateInstanceInterface.h"

class FDelegateBase;
class FDelegateHandle;


//The Payload which is a tuple, save the vars that pass in through constructor.

//Implements a delegate binding for C++ menber function;
template<bool bConst,class UserClass,typename FuncType,typename... VarTypes>
class TBaseRawMethodDelegateInstance;

template<bool bConst,class UserClass,typename WrappedRetValType, typename... ParamTypes, typename... VarTypes>
class TBaseRawMethodDelegateInstance<bConst, UserClass, WrappedRetValType(ParamTypes...), VarTypes...> : public IBaseDelegateInstance<typename TUnwrapType<WrappedRetValType>::Type (ParamTypes...)>
{
public:

	//Get the RetValType.
	typedef typename TUnwrapType<WrappedRetValType>::Type RetValType;

private:

	typedef IBaseDelegateInstance<RetValType(ParamTypes...)>                                          Super;

	typedef TBaseRawMethodDelegateInstance<bConst, UserClass, RetValType(ParamTypes...), VarTypes...> UnwrappedThisType;

public:
	//Typedef the function return 
	typedef typename TMemFunPtrType<bConst, UserClass, RetValType(ParamTypes..., VarTypes...)>::Type FMethodPtr;

	//Create and initilaize a new instance;
	TBaseRawMethodDelegateInstance(UserClass* InUserObject, FMethodPtr InMethodPtr, VarTypes... Vars)
		:UserObject(InUserObject)
		,MethodPtr(InMethodPtr)
		,Payload(Vars...)
		,Handle(FDelegateHandle::EGenerateNewHandleType::GenerateNewHandle)
	{
		//InUserObject and InMethodPtr could not be zero.
	}


	virtual void* GetTargetObject() const override final
	{
		return UserObject;
	}

	//Deprecated.
	virtual bool HasSomeObject(const void* InUserObject) const override final
	{
		return UserObject == InUserObject;
	}

	virtual bool IsSafeToExecute() const override final
	{
		//We never know whether or not it is safe to deference a C++ pointer,
		//But we have to trust the user in this case. Prefer using a shared-pointer
		//based delegate type instead.
		return true;
	}

public:
	virtual void CreateCopy(FDelegateBase& Base) override final
	{
		new (Base) UnwrappedThisType(*(UnwrappedThisType*)this);
	}

	virtual RetValType Execute(ParamTypes... Params) const override final
	{
		//Get the type without const;
		typedef typename std::remove_const<UserClass>::type MutableUserClass;

		//Safely remove const to work around a compiler issue with instantiating template
		//permutations for overloaded functions that take a function pointer typedef
		//as a member of a templated class. In all cases where this code is actually 
		//invoked ,the UserClass will already be a const pointer;
		//Use the type without const to get actually ptr to object without const.
		//We want to call the function that don't need to be const;
		auto MutableUserObject = const_cast<MutableUserClass*>(UserObject);
		//Call the member function with 
		return ApplyTupleToFunc(Payload, TMemberFunctionCaller(MutableUserObject, MethodPtr), Params...);
	}

	virtual FDelegateHandle GetHandle() const override final
	{
		return Handle;
	}

public:

	//Creates a new raw method delegate bingding for the given user object and function pointer.
	inline static void Create(FDelegateBase& Base, UserClass* InUserClass, FMethodPtr InFunc, VarTypes... Vars)
	{
		new (Base) UnwrappedThisType(InUserObject, InFunc, Vars...);
	}

protected:

	//Pointer to the user's class which contains a method we would like to call
	UserClass* UserObject;

	//C++ member function pointer.
	FMethodPtr MethodPtr;

	//Payload member variables(if any).
	std::tuple<VarTypes...> Payload;

	//The handle of this delegate
	FDelegateHandle Handle;

};

template<bool bConst,class UserClass,typename...ParamTypes, typename...VarTypes>
class TBaseRawMethodDelegateInstance<bConst, UserClass, void(ParamTypes...), VarTypes...> : public TBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...>
{

	typedef TBaseRawMethodDelegateInstance<bConst, UserClass, TTypeWrapper<void>(ParamTypes...), VarTypes...>   Super;

public:

	//Creates and initializes a new instance.
	TBaseRawMethodDelegateInstance(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, VarTypes... Vars)
		: Super(InUserObject, InMethodPtr, Vars...)
	{

	}

	virtual bool ExecuteIfSafe(ParamTypes... Params) const override final
	{
		//We never know whether or not it is safe to deference a C++ pointer, but we have to trust the user in the case.
		//Prefer using a shared-pointer based delegate type instead!
		Super::Execute(Params);

		return true;
	}

};


