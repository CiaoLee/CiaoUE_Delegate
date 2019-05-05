#pragma once


//Helpers to remove reference;

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