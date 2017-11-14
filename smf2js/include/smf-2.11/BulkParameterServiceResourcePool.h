#ifndef BULKPARAMETERSERVICERESOURCEPOOL_H_
#define BULKPARAMETERSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class BulkParameterServiceResourcePool
	{
	public:
		virtual ~BulkParameterServiceResourcePool() {};

		class IncorrectTypeInDestoryBulkParameterServiceResourcePool:
		public smf::Error
		{
		public:
			BulkParameterServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryBulkParameterServiceResourcePool(const char* expected, BulkParameterServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
