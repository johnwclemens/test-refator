#ifndef LOGSERVICEREQUESTHANDLEREXT1_H
#define LOGSERVICEREQUESTHANDLEREXT1_H

#include "LogServiceRequestHandler.h"

namespace smf{

	class LogServiceRequestHandlerExt1
		: public LogServiceRequestHandler
	{
	public:

		virtual void Subscribe(UnsignedInt id) = 0;
		virtual void Unsubscribe(UnsignedInt id) = 0;
		virtual void Record(UnsignedInt id, const PredefinedLogEntry &predefinedLogEntry) = 0;
		virtual void Record(UnsignedInt id, const FreeFormatLogEntry &freeFormatLogEntry) = 0;
		virtual void Record(UnsignedInt id, const LogEntry &) = 0;
		virtual void Record(UnsignedInt id, const UnstampedLogEntry &unstampedLogEntry) = 0;

		class LogSubscriptionWithFilteringNotSupported: public smf::Error
		{
		public:
			LogSubscriptionWithFilteringNotSupported()
				:smf::Error("The server does not support log subscription with filtering.")
			{
			}
		};

		class LogSubscriptionFilter
		{
		public:
			LogSubscriptionFilter(bool normalLogMessage, bool echoLogMessage, const LogEntry::Messages& parameters)
				: normalLogMessage(normalLogMessage), echoLogMessage(echoLogMessage), parameters(parameters)
			{}
			virtual ~LogSubscriptionFilter() {}

		public:	// access methods
			bool SubscribeNormalLogMessage() const { return normalLogMessage; };
			bool SubscribeEchoLogMessage() const { return echoLogMessage; };
			const LogEntry::Messages& FilterParameters() const { return parameters; };

		private: // prevention
			LogSubscriptionFilter();

		private:
			bool normalLogMessage;
			bool echoLogMessage;
			LogEntry::Messages parameters;
		};

		virtual void Subscribe(const LogSubscriptionFilter& subscriptionFilter, bool replayHistorialLog, UnsignedInt id) = 0;

		virtual ~LogServiceRequestHandlerExt1() {};
	};

}

#endif