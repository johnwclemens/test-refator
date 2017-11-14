#pragma once

#include <stddef.h>

namespace smf2js
{
	class Lock
	{
	public:
		virtual ~Lock() {}


		virtual bool lock(intptr_t) = 0;
		virtual bool unlock(intptr_t) = 0;
	};
}
