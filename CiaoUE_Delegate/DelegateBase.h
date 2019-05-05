#pragma once

#include "TypeCompatibleBytes.h"
#include "HeapAllocator.h"
#include "DelegateInstanceInterface.h"

//Typedef  Alignedbytes and Allocator for delegates.
typedef TAlignedBytes<16, 8> FAlignedInlineDelegateType;
typedef FHeapAllocator FDelegateAllocatorType;

//Add MulticalstDelegateBase here.

//Base class for unicast delegates.
class FDelegateBase
{
public:

	//Create and initializes a new instance.
	explicit FDelegateBase() : DelegateSize(0)
	{

	}

	~FDelegateBase()
	{
		
	}

	//Move  constructor.
	FDelegateBase(FDelegateBase&& Other)
	{
		//Copy the data from other. and free original data.
		DelegateAllocator.MoveToEmpty(Other.DelegateAllocator);
		DelegateSize = Other.DelegateSize;
		Other.DelegateSize = 0;
	}

	//Move assignment
	FDelegateBase& operator=(FDelegateBase&& Other)
	{
		Unbind();
		DelegateAllocator.MoveToEmpty(Other.DelegateAllocator);
		DelegateSize = Other.DelegateSize;
		Other.DelegateSize = 0;
		return *this;
	}

	inline void Unbind()
	{

	}

private:
	//Allocator to allocate delegate instance.
	FDelegateAllocatorType::ForElementType<FAlignedInlineDelegateType> DelegateAllocator;
	
	//The delegate size.
	int DelegateSize;
};