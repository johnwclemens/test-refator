#ifndef SCTRLSERVICERESOURCEPOOL_H_
#define SCTRLSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class SCtrlServiceResourcePool
	{
	public:
		virtual ~SCtrlServiceResourcePool() {};

		class IncorrectTypeInDestorySCtrlServiceResourcePool:
		public smf::Error
		{
		public:
			SCtrlServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestorySCtrlServiceResourcePool(const char* expected, SCtrlServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
