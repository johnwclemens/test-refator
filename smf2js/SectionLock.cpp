#include "SectionLock.h"

smf2js::SectionLock::SectionLock()
{
	::InitializeCriticalSection(&thelock);
}

smf2js::SectionLock::~SectionLock()
{
	::DeleteCriticalSection(&thelock);
}

bool smf2js::SectionLock::lock(intptr_t id)
{
	::EnterCriticalSection(&thelock);
	return true;
}

bool smf2js::SectionLock::unlock(intptr_t id)
{
	::LeaveCriticalSection(&thelock);
	return true;
}
