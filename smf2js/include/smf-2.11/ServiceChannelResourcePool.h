#ifndef SERVICECHANNELRESOURCEPOOL_H_
#define SERVICECHANNELRESOURCEPOOL_H_

#include "Error.h"

class ClientRequestServiceHandler;
class ClientReceiver;

namespace smf
{
	class ServiceChannelResourcePool
	{
	public:
		virtual ~ServiceChannelResourcePool() {}

		class IncorrectTypeInDestoryServiceChannelResourcePool:
		public smf::Error
		{
		public:
			ServiceChannelResourcePool  *received;
			const char* expected;
			IncorrectTypeInDestoryServiceChannelResourcePool(const char* expected, ServiceChannelResourcePool* received);

		};

		virtual unsigned int RequestKey() = 0;
		virtual ClientRequestServiceHandler* RequestServiceHandler(unsigned int key) = 0;
		virtual ClientReceiver* Receiver() = 0;
		virtual size_t UniqueKey() = 0;
	};
}

#endif
