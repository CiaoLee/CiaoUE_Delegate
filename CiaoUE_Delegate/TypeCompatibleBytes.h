#pragma once

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

//Ignore padding and alignment implementation.

//End Ignore;


//An untyped array of data with compile-time alignment and size derived from another type.
template<typename ElementType>
struct TTypeCompatibleBytes : public TAlignedBytes<sizeof(ElementType), alignof(ElementType)>
{

};