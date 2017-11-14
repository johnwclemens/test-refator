#ifndef PARAMETERSERVICERESOURCEPOOL_H_
#define PARAMETERSERVICERESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class ParameterServiceResourcePool
	{
	public:
		virtual ~ParameterServiceResourcePool() {};

		class IncorrectTypeInDestoryParameterServiceResourcePool:
		public smf::Error
		{
		public:
			ParameterServiceResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryParameterServiceResourcePool(const char* expected, ParameterServiceResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
