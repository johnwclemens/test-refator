#ifndef SENDERSERVICESTATUS_H
#define SENDERSERVICESTATUS_H

#include <iostream>
#include "smf-2.11/ServiceStatus.h"
#include "ErrorReason.h"

namespace smf2js
{
	class SenderServiceStatus : public smf::ServiceStatus
	{
	public:
		SenderServiceStatus()
			:numMissedMessages(0)
		{
			char* failures[] = {
				"ServerTooBusy",
				"ErrorInServerService",
				"ServerServiceTooBusy",
				"ClientServiceTooBusy",
				"UnknownMessageType",
				"MaxPayloadExceededResponse",
				0
			};
			m_ErrorReason.Set(failures);
		}

		virtual void Disconnect()
		{
			std::cout << "The connection with the server is broken\n";
		}

		virtual void Reconnect()
		{
			std::cout << "Reconnected to the server\n";
		}

		virtual void MissedMessage(const char *serviceName, MissedMessageReason reason)
		{
			std::cout << "Service: " << serviceName << " - "
				<< m_ErrorReason.ReasonToString(reason).c_str() << "\n";
			numMissedMessages++;
		}

		virtual void ServiceUnknown(const char *serviceName)
		{
			std::cout << "The service " << serviceName << " is unknown\n";
		}

		unsigned int NumMissedMessages() const
		{
			return numMissedMessages;
		}

	private:
		ErrorReason m_ErrorReason;
		unsigned int numMissedMessages;
	};
}

#endif
