#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

namespace smf{
	class LogMessage
	{
	public:
		enum
		{
			FailureReasonSize = sizeof(unsigned short)
		};

		enum MessageType
		{
			Record,
			Subscribe,
			Unsubscribe,
			Report,
			ReportFailure,
			SubscriptionSuccessful,
			SubscriptionFailed,
			UnsubscribeSuccessful,
			UnsubscribeFailed,
			Dummy, //because in previous versions of the server there is a bug which
					// means that there is a problem if we receive a message type with id
					// == lat message type id - just ensure that if this message is ever 
					// sent to an old server it will nbot cause this problem to appear
			RecordWithoutNotifying,
			SubscribeWithFiltering,
					

			LastMessageType,
			
			FirstMessageType = Record, 
		};

		enum
		{
			NumberOfMessageTypes = LastMessageType - FirstMessageType
		};

		virtual ~LogMessage() {}

		enum FailureReason
		{
			Success,
			DuplicatedSubscription,	// for Subscribe
			TooManySubscriptions,	// for Subscribe
			SubscriberNotFound,	// for Unsubscribe
			UnclassifiedFailure,
			CodingError, //this means there is something wrong with the code
			MissedMessage, //this is originated at the client side 
			ServerOverloaded,
			SizeMismatch,
			UnsupportedMessageType,
			UnknownMessage,
			TotalMessageSizeTooBig
		};

		//so the proxy server doesn't need the logd/api lib to use the log internal service
		static unsigned int LogIdentifier()
		{
			return *(unsigned int*)"LOG\0";
		}

		static unsigned int Version();

		static unsigned int VersionWithSubscriptionFiltering();
	};
}
#endif
