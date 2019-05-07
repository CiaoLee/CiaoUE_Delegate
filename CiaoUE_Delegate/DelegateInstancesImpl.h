#pragma once

#include <tuple>
#include "IDelegateInstance.h"
#include "DelegateInstanceInterface.h"

class FDelegateBase;
class FDelegateHandle;

//Implements a delegate binding for C++ menber function;
template<bool bConst,class UserClass,typename FuncType,typename... VarTypes>
class TBaseRawMethodDelegateInstance;

template<bool bConst,class UserClass,typename WrappedRetValType, typename... ParamTypes, typename... VarTypes>
class TBaseRawMethodDelegateInstance<bConst, UserClass, WrappedRetValType(ParamTypes...), VarTypes...> : public IBaseDelegateInstance<typename TUnwrapType<WrappedRetValType>::Type (ParamTypes..)>
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

	//Deprecated.
	virtual bool HasSomeObject(const void* InUserObject) const override final
	{
		return UserObject == InUserObject;
	}


protected:

	//Pointer to the user's class which contains a method we would like to call
	UserClass* UserObject;

	//C++ member function pointer.
	FMethodPtr MethodPtr;

	//Payload member variables(if any).
	std::tuple<VarTypes....> Payload;

	//The handle of this delegate
	FDelegateHandle Handle;
};


