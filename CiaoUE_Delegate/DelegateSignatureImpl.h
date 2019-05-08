#pragma once
#include "TemplateHelper.h"
#include "TypeCompatibleBytes.h"


class FDelegateBase;
class FDelegateHandle;
class IDelegateInstance;
template<typename FuncType> struct IBaseDelegateInstance;

//Unicast delegate base object

template<typename WrappedRetValType, typename... ParamTypes>
class TBaseDelegate : public FDelegateBase
{
public:

	//Todo:: figure out why we need Unwrap the WrappedRetValType here.
	//Type definition for return value type.
	typedef typename TUnwrapType<WrappedRetValType>::Type RetValType;
	typedef RetValType TFuncType(ParamTypes...);

	//type definition for the shared interface of delegate instance types compatible with this delegate class.
	typedef IBaseDelegateInstance<TFuncType> TDelegateInstanceInterface;

	//Here we can figure that UE only support up to 4 Var for user identify. 8 Param + 4 Var.
	/** Declare the user's C++ pointer-based delegate instance types. */
	template <typename UserClass                                                                            > struct TRawMethodDelegate : TBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > { typedef TBaseRawMethodDelegateInstance<false, UserClass, TFuncType                                        > Super; TRawMethodDelegate(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
	template <typename UserClass                                                                            > struct TRawMethodDelegate_Const : TBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType                                        > Super; TRawMethodDelegate_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr) : Super(InUserObject, InMethodPtr) {} };
	template <typename UserClass, typename Var1Type                                                         > struct TRawMethodDelegate_OneVar : TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > { typedef TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type                              > Super; TRawMethodDelegate_OneVar(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
	template <typename UserClass, typename Var1Type                                                         > struct TRawMethodDelegate_OneVar_Const : TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type                              > Super; TRawMethodDelegate_OneVar_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1) : Super(InUserObject, InMethodPtr, Var1) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct TRawMethodDelegate_TwoVars : TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type                    > Super; TRawMethodDelegate_TwoVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type                                      > struct TRawMethodDelegate_TwoVars_Const : TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type                    > Super; TRawMethodDelegate_TwoVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2) : Super(InUserObject, InMethodPtr, Var1, Var2) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct TRawMethodDelegate_ThreeVars : TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; TRawMethodDelegate_ThreeVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type                   > struct TRawMethodDelegate_ThreeVars_Const : TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type          > Super; TRawMethodDelegate_ThreeVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct TRawMethodDelegate_FourVars : TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef TBaseRawMethodDelegateInstance<false, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; TRawMethodDelegate_FourVars(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };
	template <typename UserClass, typename Var1Type, typename Var2Type, typename Var3Type, typename Var4Type> struct TRawMethodDelegate_FourVars_Const : TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> { typedef TBaseRawMethodDelegateInstance<true, UserClass, TFuncType, Var1Type, Var2Type, Var3Type, Var4Type> Super; TRawMethodDelegate_FourVars_Const(UserClass* InUserObject, typename Super::FMethodPtr InMethodPtr, Var1Type Var1, Var2Type Var2, Var3Type Var3, Var4Type Var4) : Super(InUserObject, InMethodPtr, Var1, Var2, Var3, Var4) {} };
};