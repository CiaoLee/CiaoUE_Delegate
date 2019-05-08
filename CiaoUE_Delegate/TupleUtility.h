#pragma once

#include <tuple>
#include <utility>
#include <type_traits>

template< std::size_t... Indices, typename FuncType, typename...VarTypes, typename...ParamTypes>
auto ApplyTupleToFuncImpl(std::tuple<VarTypes...>& InTuple, FuncType&& InFunc, std::index_sequence<Indices...>, ParamTypes&&... InParam)
-> decltype(InFunc(std::forward<ParamTypes>(InParam)..., std::get<Indices>(InTuple)...))
{
	return  InFunc(std::forward<ParamTypes>(InParam)..., std::get<Indices>(InTuple)...);
}

template<typename FuncType, typename... VarTypes, typename... ParamTypes>
auto  ApplyTupleToFunc(std::tuple<VarTypes...>& InTuple, FuncType&& InFunc, ParamTypes&&... InParam)
-> decltype(ApplyTupleToFuncImpl(InTuple, InFunc, std::index_sequence_for<VarTypes...>(), InParam ...))
{
	return ApplyTupleToFuncImpl(InTuple, InFunc, std::index_sequence_for<VarTypes...>(), InParam ...);
}

//Transform tuple with recursion.
template<std::size_t Index = 0, typename FuncType, typename... VarTypes>
inline typename std::enable_if<Index == sizeof...(VarTypes), void>::type
TransformTuple(std::tuple<VarTypes...>& InTuple, FuncType&& InFunc)
{
	//default;
}

template<std::size_t Index = 0, typename FuncType, typename... VarTypes>
inline typename std::enable_if < Index < sizeof...(VarTypes), void>::type
	TransformTuple(std::tuple<VarTypes...>& InTuple, FuncType&& InFunc)
{
	InFunc(std::get<Index>(InTuple));
	TransformTuple<Index + 1>(InTuple, InFunc);
}