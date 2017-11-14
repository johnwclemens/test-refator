#pragma once

#include "Lock.h"
#include "./include/smf-2.11/Error.h"

namespace smf2js
{
	class Locker
	{
	public:
		class FailedToLock : public smf::Error
		{
		public:
			FailedToLock() : smf::Error("Locker failed to lock a lock")
			{ }
		};

		class FailedToUnlock : public smf::Error
		{
		public:
			FailedToUnlock() : smf::Error("Locker failed to unlock a lock it believes it owns")
			{ }
		};

		Locker();
		Locker(Lock* lock);

		~Locker();

		bool Acquire(Lock* lock);
		void Release();

	private:
		Lock*   plock;
		bool    bOwnLock;

	};
}

