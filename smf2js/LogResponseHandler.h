#pragma once


#include "./include/smf-2.11/LogServiceResponseHandler.h"
#include "./include/smf-2.11/Logger.h"
#include "Log.h"

namespace smf2js
{
	class LogResponseHandler : public smf::LogServiceResponseHandler
	{
	public:
		LogResponseHandler(smf::Logger* logger);
		~LogResponseHandler();

		virtual void Report(ResponseLogEntry&);
		virtual void ReportFailure(UnsignedInt id, UnsignedInt reason, const char* info);
		virtual void SubscriptionSuccessful(UnsignedInt id);
		virtual void SubscriptionFailed(UnsignedInt id, UnsignedInt reason);
		virtual void UnsubscribeSuccessful(UnsignedInt id);
		virtual void UnsubscribeFailed(UnsignedInt id, UnsignedInt reason);

	private:
		std::string FormattedMessage(const ResponseLogEntry& entry);
		std::string FormattedDate(const smf::DateTimeEntry& date);
		std::string FormattedTime(const smf::DateTimeEntry& date);
		Log log;
	};
}

