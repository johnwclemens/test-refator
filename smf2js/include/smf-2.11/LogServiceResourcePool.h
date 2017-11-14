#ifndef LOGSERVICERESOURCEPOOL_H_
#define LOGSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class LogServiceResourcePool
	{
	public:
		virtual ~LogServiceResourcePool() {};

		class IncorrectTypeInDestoryLogServiceResourcePool:
		public smf::Error
		{
		public:
			LogServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryLogServiceResourcePool(const char* expected, LogServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
