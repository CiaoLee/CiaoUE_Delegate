#pragma once

#include <tuple>
#include "IDelegateInstance.h"

class FDelegateBase;
class FDelegateHandle;

//Implements a delegate binding for C++ menber function;
template<bool bConst,class UserClass,typename FuncType,typename... VarTypes>
class TBaseRawMethodDelegateInstance;

template<bool bConst,class UserClass,typename WrappedRetValType, typename... ParamTypes, typename... VarTypes>
class TBaseRawMethodDelegateInstance<bConst, UserClass, WrappedRetValType(ParamTypes...), VarTypes...>
{


};

