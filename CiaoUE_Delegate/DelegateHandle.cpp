#include "IDelegateInstance.h"

namespace Delegates_Private
{
	//TODO: use  atomic GNextID.
	unsigned int GNextID = 1;
}

unsigned int FDelegateHandle::GenerateNewID()
{
	unsigned int Result = ++Delegates_Private::GNextID;

	if (Result == 0)
	{
		//Increment it again - it might not be zero, so don't just assign it to 1.
		Result = ++Delegates_Private::GNextID;
	}

	return Result;
}


