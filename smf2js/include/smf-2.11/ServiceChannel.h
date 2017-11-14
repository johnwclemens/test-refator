
#ifndef SERVICECHANNEL_H
#define SERVICECHANNEL_H

#include "Error.h"

namespace smf{
	class ServiceStatus;
}
class ClientResponseService;
class ClientRequestService;

namespace smf{
	class ServiceChannel{

	public:
		class ConnectionFailure:
			public smf::Error
		{
		public:
			ConnectionFailure();
		};

		class IncorrectMessageFromServer:
			public smf::Error
		{
		public:
			IncorrectMessageFromServer();
		};

		class ExpectedProxyServerMessage:
			public smf::Error
		{
		public:
			ExpectedProxyServerMessage(unsigned int serviceId);
		};
		class ExpectedInitialisationMessage:
		public smf::Error
		{
		public:
			ExpectedInitialisationMessage(unsigned int type);

		};
		class IncompatibleClient:
		public smf::Error
		{
		public:
			IncompatibleClient();

		};
		class ExpectedCompatibilityMessage:
		public smf::Error
		{
		public:
			ExpectedCompatibilityMessage(unsigned int service);

		};
		class NoInitialisationFromServer:
		public smf::Error
		{
		public:
			NoInitialisationFromServer(const char* info);

		};

		class IncorrectTypeInDisconnectServiceChannel:
		public smf::Error
		{
		public:
			ServiceChannel  *received;
			const char* expected;
			IncorrectTypeInDisconnectServiceChannel(const char* expected, ServiceChannel* received);

		};
		
		class ServiceAlreadyExists:
		public smf::Error
		{
		public:
			ServiceAlreadyExists(const char*servicename);

		};

		virtual ~ServiceChannel() {}
		
		virtual const char* SmfServerVersion() = 0;
		virtual const char* SmfClientVersion() = 0;
		
		virtual ClientRequestService* RequestService() = 0;

		virtual void AddResponseService(ClientResponseService*, unsigned int) = 0;

		virtual void RemoveResponseService(ClientResponseService*) = 0;
		
		virtual void SetServiceStatus(ServiceStatus *serviceStatus) = 0;

		virtual void SetConnectionKeepaliveTimeout(unsigned int timeoutMsec) = 0;

		
		typedef std::pair<unsigned int,  std::string> ServiceVersionData;
		virtual bool IsSupported (const ServiceVersionData& version)  = 0;

		virtual size_t UniqueKey() = 0;
				
		virtual const char* ServerVersion() = 0;
		virtual const char* ClientVersion() = 0;
	};
}


#endif