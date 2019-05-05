#pragma once

#include <stdio.h>
#include <stdlib.h>

struct FScriptContainerElement
{

};

//The indirect allocation policy always allocates the elements indirectly.
class FHeapAllocator
{
public:

	enum class {NeedsElementType = false};
	enum class {RequireRangeCheck = true};

	class ForAnyElementType
	{
	public:
		//Default constructor:
		ForAnyElementType() :Data(nullptr)
		{

		}
		//The difference between free and delete;
		//free need to check ptr not be null.
		 inline void MoveToEmpty(ForAnyElementType& Other)
		{
			 if (Data)
			 {
				 free(Data);
			 }

			 Data = Other.Data;
			 Other.Data = nullptr;
		}

		 //Destructor
		 inline ~ForAnyElementType()
		 {
			 if (Data)
			 {
				 free(Data);
			 }
		 }

		 inline FScriptContainerElement* GetAllocation() const
		 {
			 return Data;
		 }

		 inline void ResizeAllocation(int PreviousNumElements, int NumElements, size_t NumBytesPerElement)
		 {
			 if (Data || NumElements)
			 {
				 Data = (FScriptContainerElement*)realloc(Data, NumElements*NumBytesPerElement);
			 }
		 }

		 size_t GetAllocatedSize(int NumAllocatedElements, size_t NumBytesPerElement) const
		 {
			 return NumAllocatedElements * NumBytesPerElement;
		 }

		 bool HasAllocation()
		 {
			 return !!Data;
		 }

	private:

		//Won't allow other to call move and copy;
		ForAnyElementType(const ForAnyElementType&);
		ForAnyElementType& operator=(const ForAnyElementType&);

		//A pointer to container's elements.
		FScriptContainerElement* Data;
	};

	template<typename ElementType>
	class ForElementType : public ForAnyElementType
	{
	public:

		//Default constructor.
		ForElementType()
		{

		}

		inline ElementType* GetAllocation() const
		{
			//Cast to ElementType
			return (ElementType*)ForAnyElementType::GetAllocation();
		}
	};

};