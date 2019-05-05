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
		if (IDelegateInstance* Ptr = GetDelegateInstanceProtected())
		{
			Ptr->~~IDelegateInstance();
			DelegateAllocator.ResizeAllocation(0, 0, sizeof(FAlignedInlineDelegateType));
			DelegateSize = 0;
		}
	}

	inline FDelegateHandle GetHandle() const
	{
		FDelegateHandle Result;
		if (IDelegateInstance* Ptr = GetDelegateInstanceProtected())
		{
			Result = Ptr->GetHandle();
		}

		return Result;
	}

protected:

	/** 
	*	Gets the delegate instance. Not intended for use by user code.
	*/

	inline IDelegateInstance*  GetDelegateInstanceProtected() const
	{
		return DelegateSize ? (IDelegateInstance*)DelegateAllocator.GetAllocatedSize() : nullptr;
	}

private:

	friend void* operator new(size_t Size, FDelegateBase& Base);

	void* Allocate(int Size)
	{
		if (IDelegateInstance* CurrentInstance = GetDelegateInstanceProtected())
		{

		}

		int SizeOfDelegate = (int)sizeof(FAlignedInlineDelegateType);


	}

	//Allocator to allocate delegate instance.
	FDelegateAllocatorType::ForElementType<FAlignedInlineDelegateType> DelegateAllocator;
	
	//The delegate size.
	int DelegateSize;
};