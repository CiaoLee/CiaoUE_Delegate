#pragma once


//define GCC_ALIGN and  MS_ALIGN as empty.
#ifndef  GCC_ALIGN
#define GCC_ALIGN(n) 
#endif

#ifndef  MS_ALIGN
#define MS_ALIGN(n)
#endif 

#if defined(__clang__)
//With -fms_extensions. Clang will accept either alignment attribute.
#if defined(_MSC_VER)
#define MS_ALIGN(n) __declspec(align(n))
#endif
#endif
#else
#define MS_ALIGN(n) __declspec(align(n))
#endif

#if  !defined(__clang__)
#define MSVC_PRAGMA( Pragma) __pragma(Pragma)
#endif

/**
 *  Used to declare an untyped array of data with compile-time alignment.
 *  It needs to use template specialization as the MS_ALIGN and GCC_ALIGN macros require literal parameters.
 */
template<int Size,unsigned int Alignment>
struct TAlignedBytes;// this intentionally won't compile, weDon't support the requested alignment

//Unaligned storage
template<int Size>
struct TAlignedBytes<Bytes, 1>
{
	unsigned char Pad[Size];
};

#define IMPLEMENT_ALIGNED_STORAGE(Align)	\
template<int Size>	\
struct TAlignedBytes<Size,Align>	\
{	\
	//Define structure TPadding.
	struct TPadding	\ MS_ALIGN(Align)
	{	\
		unsigned char Pad[Size]; \
	};  GCC_ALIGN(Align)\

	TPadding Padding; \
};



//An untyped array of data with compile-time alignment and size derived from another type.
template<typename ElementType>
struct TTypeCompatibleBytes : public TAlignedBytes<sizeof(ElementType), alignof(ElementType)>
{

};