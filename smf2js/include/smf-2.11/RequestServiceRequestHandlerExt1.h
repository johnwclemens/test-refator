#ifndef REQUESTSERVICEREQUESTHANDLEREXT1_H
#define REQUESTSERVICEREQUESTHANDLEREXT1_H

#include "Error.h"
#include "ArsPayload.h"
#include "Types.h"
#include <string>
#include "RequestServiceRequestHandler.h"

namespace smf {

    class Logger;
    class ServiceChannel;
    class RequestServiceResponseHandler;
    class RequestServiceRequestHandler;

    //! Use this to send a request/command to a receiver
    class RequestServiceRequestHandlerExt1 : public RequestServiceRequestHandler
    {
    public:
	    typedef ArsPayload Payload;        
        virtual ~RequestServiceRequestHandlerExt1() {}

		//! \brief Send a request to a receiver 
		//! \param receiver		The registered receiver name to receive the command
		//! \param id			This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		//! \param payload		The command in vector<char> to be sent to the receiver. (it is arbitrary binary data)
		//! \post	The response will be reported back through your implementation of the 
		//!			smf::RequestServiceResponseHandler::Response(const std::string&, UnsignedInt, Payload &) 
		//! \note	Function is thread-safe and will return immediately
	    virtual void Request(const std::string &receiver, UnsignedInt id, const Payload &payload) = 0;

		
		//! \brief Send a command to a receiver. Use this function if you expect
        //!        the receiver will respond to your command.
		//! \param receiver		The registered receiver name to receive the command
		//! \param id			This is an identifier defined by the application.
		//!						SMf will pass this back to you in the callback function.
		//!	\param command		The command name to be sent to the receiver.
		//! \param payload 		The arbitrary binary data for the command in vector<char> 
		//!						to be sent to the receiver. 
		//!	\param expectedSuccessResponseCode	The response code that is expected to be replied
		//!									    from the receiver when the command is successfully
		//!									    executed. This response code will be passed to the receiver.
		//!	\param timeoutInMsec The expected timeout value for the receiver to respond. This timeout value will be passed to the receiver.
        //! \post   The response will be reported back through your implementation of the 
        //!			smf::RequestServiceResponseHandlerExt1::Response(const std::string&, UnsignedInt, const std::string&, UnsignedInt, Payload &)
		//! \note	Function is thread-safe and will return immediately
		virtual void Request(const std::string &receiver,
							 UnsignedInt id, 
							 const std::string &command, 
							 const Payload &payload, 
							 UnsignedInt expectedSuccessResponseCode,
							 UnsignedInt timeoutInMsec) = 0;
	 
        //! \brief Send a command to a receiver. Use this function if you do not expect
        //!        the receiver will respond to your command.
		//! \param receiver		The registered receiver name to receive the command
		//! \param id			This is an identifier defined by the application.
		//!						SMf will pass this back to you in the callback function.
		//!	\param command		The command name to be sent to the receiver.
		//! \param payload 		The arbitrary binary data for the command in vector<char> 
		//!						to be sent to the receiver. 
        //! \post   In case the receiver still send out a response, the response will 
        //!         be reported back through your implementation of the 
        //!			smf::RequestServiceResponseHandlerExt1::Response(const std::string&, UnsignedInt, const std::string&, UnsignedInt, Payload &)
		//! \note	Function is thread-safe and will return immediately
		virtual void Request(const std::string &receiver,
							 UnsignedInt id, 
							 const std::string &command, 
							 const Payload &payload) = 0;
	 
				
        //! \brief Send a command to all receivers that subscribing this command. 
        //!        Use this function if you expect the receivers will respond to your command.
		//! \param id			This is an identifier defined by the application.
		//!						SMf will pass this back to you in the callback function.
		//!	\param command		The command name to be sent to the receivers.
		//! \param payload 		The arbitrary binary data for the command in vector<char> 
		//!						to be sent to the receivers. 
        //! \param isSuccessIfNoSubscriber Set this to true if you want SMF consider the overall result to be success when 
        //!                                no subscriber subscribed this command. Otherwise ,false.
		//!	\param expectedSuccessResponseCode	The response code that is expected to be replied
		//!									    from the receivers when the command is successfully
		//!									    executed. This response code will be passed to the receivers.
		//!	\param timeoutInMsec The expected timeout value for the receivers to respond. This timeout value will be passed to the receivers.
        //! \post   The responses will be reported back through your implementation of the 
        //!			smf::RequestServiceResponseHandlerExt1::Response(const std::string&, UnsignedInt, const std::string&, UnsignedInt, Payload &)
        //!         In addition, SMF will consolidate the responses from all receivers within the timeout 
        //!         and report this consolidated response through your imeplementation of the 
        //!         smf::RequestServiceResponseHandlerExt1::ConsolidatedResponse.
		//! \note	Function is thread-safe and will return immediately		
		virtual void RequestToSubscribers(UnsignedInt id, 
										 const std::string &command, 
										 const Payload &payload, 
										 UnsignedInt expectedSuccessResponseCode,
										 UnsignedInt timeoutInMsec,
                                         bool isSuccessIfNoSubscriber) = 0;

        //! \brief Send a command to all receivers that subscribing this command. 
        //!        Use this function if you do not expect the receivers will respond to your command.
		//! \param id			This is an identifier defined by the application.
		//!						SMf will pass this back to you in the callback function.
		//!	\param command		The command name to be sent to the receivers.
		//! \param payload 		The arbitrary binary data for the command in vector<char> 
		//!						to be sent to the receivers. 
        //! \param isSuccessIfNoSubscriber Set this to true if you want SMF consider the overall result to be success when 
        //!                                no subscriber subscribed this command. Otherwise ,false.
        //! \post   In case the receiver(s) still send out response(s), the response(s) will be reported back through your implementation of the 
        //!			smf::RequestServiceResponseHandlerExt1::Response(const std::string&, UnsignedInt, const std::string&, UnsignedInt, Payload &)
        //!         In addition, SMF will report the request state of the all subscribers through your imeplementation of the 
        //!         smf::RequestServiceResponseHandlerExt1::ConsolidatedResponse.
		//! \note	Function is thread-safe and will return immediately											 
		virtual void RequestToSubscribers(UnsignedInt id, 
										 const std::string &command, 
										 const Payload &payload,
                                         bool isSuccessIfNoSubscriber) = 0;

        class ServerNotSupportSubscription;
        class CommandNameEmpty;
        class ReceiverNameEmpty;
        class InvalidTimeoutConfiguration;
  
    };


    class RequestServiceRequestHandlerExt1::ServerNotSupportSubscription : public smf::Error
    {
    public:
        ServerNotSupportSubscription() : smf::Error("SMF server does not support command subscription API.") {}
        ~ServerNotSupportSubscription() {}
    };
    
    class RequestServiceRequestHandlerExt1::CommandNameEmpty : public smf::Error
    {
    public:
        CommandNameEmpty() : smf::Error("Command name is empty.") {}
        ~CommandNameEmpty() {}
    };

    class RequestServiceRequestHandlerExt1::ReceiverNameEmpty : public smf::Error
    {
    public:
        ReceiverNameEmpty() : smf::Error("Receiver name is empty.") {}
        ~ReceiverNameEmpty() {}
    };
    class RequestServiceRequestHandlerExt1::InvalidTimeoutConfiguration : public smf::Error
    {
    public:
        InvalidTimeoutConfiguration() : smf::Error("Invalid timeout configuration, positive integer expected.") {}
        ~InvalidTimeoutConfiguration() {}
    };
}

#endif
