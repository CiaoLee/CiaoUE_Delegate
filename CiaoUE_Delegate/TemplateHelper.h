#pragma once

//TypeWrapper;
template<typename T>
struct TTypeWrapper;

template<typename T>
struct TUnwrapType
{
	typedef T Type;
};

template<typename T>
struct TUnwrapType<TTypeWrapper<T>>
{
	typedef  T  Type;
};

//TRemoveReference<type> will remove any references from a type.
template<typename T> struct TRemoveReference
{
	typedef T Type;
};

template<typename T> struct TRemoveReference<T& >
{
	typedef T Type;
};

template<typename T> struct TRemoveReference<T&& >
{
	typedef T Type;
};

//just like std::forward.

template<typename T>
inline T&& Forward(typename TRemoveReference<T>::Type InObj)
{
	return (T&&)InObj;
}

template<typename T>
inline T&& Forward(typename TRemoveReference<T>::Type&& InObj)
{
	return (T&&)InObj;
}
