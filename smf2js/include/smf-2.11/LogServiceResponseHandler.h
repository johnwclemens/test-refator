#ifndef LOGSERVICERESPONSEHANDLER_H
#define LOGSERVICERESPONSEHANDLER_H

#include "ResponseStampedLogEntry.h"
#include "Types.h"

namespace smf{
	class LogServiceResponseHandler
	{
	public:
		// Note: A ResponseLogEntry is just a wrapper for a log entry.
		// It only holds a reference to the log entry - not an actual log entry
		// So do *not* keep copies of it
		typedef smf::ResponseStampedLogEntry ResponseLogEntry;
		virtual void Report(ResponseLogEntry &) = 0;
		virtual void ReportFailure(UnsignedInt id, UnsignedInt reason, const char* info) = 0;
		virtual void SubscriptionSuccessful(UnsignedInt id) = 0;
		virtual void SubscriptionFailed(UnsignedInt id, UnsignedInt reason) = 0;
		virtual void UnsubscribeSuccessful(UnsignedInt id) = 0;
		virtual void UnsubscribeFailed(UnsignedInt id, UnsignedInt reason) = 0;
		virtual ~LogServiceResponseHandler(){}
	};
}

#endif
