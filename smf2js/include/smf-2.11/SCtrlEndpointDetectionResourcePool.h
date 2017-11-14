#ifndef SCTRLENDPOINTDETECTIONRESOURCEPOOL_H_
#define SCTRLENDPOINTDETECTIONRESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class SCtrlEndpointDetectionResourcePool
	{
	public:
		virtual ~SCtrlEndpointDetectionResourcePool() {};

		class IncorrectTypeInDestorySCtrlEndpointDetectionResourcePool:
		public smf::Error
		{
		public:
			SCtrlEndpointDetectionResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestorySCtrlEndpointDetectionResourcePool(const char* expected, SCtrlEndpointDetectionResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
