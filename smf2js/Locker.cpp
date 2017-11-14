#include "Locker.h"

smf2js::Locker::Locker()
{
	plock = NULL;
	bOwnLock = false;
}

smf2js::Locker::Locker(Lock* lock)
{
	if (!Acquire(lock))
		throw FailedToLock();
}

smf2js::Locker::~Locker()
{
	Release();
}

bool smf2js::Locker::Acquire(Lock* lock)
{
	if (!lock)
		return false;

	plock = lock;

	if (!plock->lock((intptr_t) this))
	{
		return false;
	}

	bOwnLock = true;
	return true;
}

void smf2js::Locker::Release()
{
	if (!plock)
		return;
	if (!bOwnLock)
		return;

	if (!plock->unlock((intptr_t) this))
	{
		throw FailedToUnlock();
	}
	bOwnLock = false;
}
