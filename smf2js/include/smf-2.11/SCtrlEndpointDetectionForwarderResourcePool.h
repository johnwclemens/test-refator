#ifndef SCTRLENDPOINTDETECTIONFORWARDERRESOURCEPOOL_H_
#define SCTRLENDPOINTDETECTIONFORWARDERRESOURCEPOOL_H_

#include "Error.h"

class ClientResponseServiceResourcePool;

namespace smf
{
	class SCtrlEndpointDetectionForwarderResourcePool
	{
	public:
		virtual ~SCtrlEndpointDetectionForwarderResourcePool() {};

		class IncorrectTypeInDestorySCtrlEndpointDetectionForwarderResourcePool:
		public smf::Error
		{
		public:
			SCtrlEndpointDetectionForwarderResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestorySCtrlEndpointDetectionForwarderResourcePool(const char* expected, SCtrlEndpointDetectionForwarderResourcePool* received);

		};

		virtual ClientResponseServiceResourcePool* ResponseServiceResourcePool() = 0;

		virtual size_t UniqueKey() = 0;
	};
}

#endif
