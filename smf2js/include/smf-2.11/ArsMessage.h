#ifndef ARSMESSAGE_H
#define ARSMESSAGE_H

namespace smf{

    class ArsMessage
    {
    public:
	    enum
	    {
		    FailureReasonSize = sizeof(unsigned short)
	    };

	    enum MessageType
	    {
		    Request,
		    Register,
		    Response,
		    ReportFailure,
		    RegistrationSuccess,
		    RegistrationFailure,
			ConnectionInfoRequest,
			ConnectionInfoResponse,

            RegisterWithCommandAPI,

            SubscribeCommand,
            SubscribeCommandSuccess,
            SubscribeCommandFailure,
            UnsubscribeCommand,
            UnsubscribeCommandSuccess,
            UnsubscribeCommandFailure,

            RequestCommand,
            ResponseCommand,
            ConsolidateResponseCommand,

		    LastMessageType,
    		
		    FirstMessageType = Request 
	    };

        enum
        {
            NumberOfMessageTypes = LastMessageType - FirstMessageType
        };

	    virtual ~ArsMessage() {}

	    enum FailureReason
	    {
		    Success,
		    UnclassifiedFailure,
		    UnknownReceiver,
		    ReceiverConnectionFailure,
		    SenderConnectionFailure,
		    DuplicatedRegistration,
		    InvalidSenderId,
		    CodingError, //!< this means there is something wrong with the code
		    MissedMessage, //!< this is originated at the client side 
		    ServerOverloaded,
		    SizeMismatch,
		    UnsupportedMessageType,
		    UnknownMessage,
		    TotalMessageSizeTooBig,
            CommandOustanding,
            UnknownCommand,
            MaxSubscriptionClientReached,
            MaxOutstandingCommandsReached,
            ReceiverNotSupportCommand
	    };

	    unsigned int static ArsIdentifier(){
		    return *(unsigned int*)"ARS\0";
	    }
	    static unsigned int Version()
	    {
		    return *(unsigned int *)"0001";
	    }
        static unsigned int VersionWithCommandSubscription()
        {
            return *(unsigned int *)"0002";
        }
        
        
    };
}

#endif
