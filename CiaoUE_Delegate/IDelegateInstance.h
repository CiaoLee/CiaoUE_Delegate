#pragma once

#include <unordered_map>

//Class representing an handle to a delegate
class FDelegateHandle
{
public:
	enum class EGenerateNewHandleType
	{
		GenerateNewHandle
	};

	FDelegateHandle() : ID(0)
	{

	}

	explicit FDelegateHandle(EGenerateNewHandleType)
		: ID(GenerateNewID())
	{

	}

	bool IsValid() const
	{
		return ID != 0;
	}

	void Reset()
	{
		ID = 0;
	}

	unsigned int GetRawID() const
	{
		return ID;
	}

private:

	friend bool operator ==(const FDelegateHandle& Lhs, const FDelegateHandle& Rhs)
	{
		return Lhs.ID == Rhs.ID;
	}

	friend bool operator!=(const FDelegateHandle& Lhs, const FDelegateHandle& Rhs)
	{
		return Lhs.ID != Rhs.ID;
	}

	//Ignore GetTypeHash, cause GetTypeHash is used for TMap.

	static unsigned int GenerateNewID();

	unsigned int ID;
};

//Create the hasher FDelegateHandle use for unorderedMap;
namespace std
{
	template<>
	struct hash<FDelegateHandle>
	{
		typedef size_t result_type;
		typedef FDelegateHandle argument_type;

		result_type operator() (argument_type const  & InFDelegateHandle) const noexcept
		{
			return 	InFDelegateHandle.GetRawID();
		}
	};
}


/**
* Interface for delegate instances.
*/
class IDelegateInstance
{
public:

	//Returns the UObject that this delegate instance is bound to.
	virtual void* GetTargetObject() const = 0;

	//Returns true if the delegate is bound to the specified UserObject.
	virtual bool HasSameObject(const void* InUserObject) const = 0;

	virtual bool IsCompactable() const
	{
		return !IsSafeToExecute();
	}

	virtual bool IsSafeToExecute() const = 0;

	virtual FDelegateHandle GetHandle() const = 0;

public:

	virtual ~IDelegateInstance() {};
};