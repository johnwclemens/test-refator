#pragma once

#include "Lock.h"

#include <Winsock2.h>
#include <Windows.h>

namespace smf2js
{
	class SectionLock : public Lock
	{
	public:
		SectionLock();

		~SectionLock();

		bool lock(intptr_t id);
		bool unlock(intptr_t id);

	private:
		SectionLock(const SectionLock&);
		//SectionLock& operator= (const SectionLock&);

	private:
		CRITICAL_SECTION  thelock;
	};
}

