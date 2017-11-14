#ifndef SERVICESTATUS_H
#define SERVICESTATUS_H

namespace smf{
	class ServiceStatus
	{
	public:
		enum MissedMessageReason{
			ServerTooBusy,
			ErrorInServerService,
			ServerServiceTooBusy,
			ClientServiceTooBusy,
			UnknownMessageType,
			MaxPayloadExceededResponse
		};

		virtual void Disconnect() = 0;
		virtual void Reconnect() = 0;

		virtual void MissedMessage(const char *serviceName, MissedMessageReason) = 0;
		virtual void ServiceUnknown(const char *serviceName) = 0;

		virtual ~ServiceStatus() {}
	};
}

#endif
