#ifndef REQUESTSERVICERESOURCEPOOL_H_
#define REQUESTSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class RequestServiceResourcePool
	{
	public:
		virtual ~RequestServiceResourcePool() {};

		class IncorrectTypeInDestoryRequestServiceResourcePool:
		public smf::Error
		{
		public:
			RequestServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryRequestServiceResourcePool(const char* expected, RequestServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
