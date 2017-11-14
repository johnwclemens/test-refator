#ifndef SCTRLAPPSTATUSRESOURCEPOOL_H_
#define SCTRLAPPSTATUSRESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class SCtrlAppStatusResourcePool
	{
	public:
		virtual ~SCtrlAppStatusResourcePool() {};

		class IncorrectTypeInDestorySCtrlAppStatusResourcePool:
		public smf::Error
		{
		public:
			SCtrlAppStatusResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestorySCtrlAppStatusResourcePool(const char* expected, SCtrlAppStatusResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
