#ifndef REQUESTSERVICERESPONSEHANDLEREXT1_H
#define REQUESTSERVICERESPONSEHANDLEREXT1_H

#include "RequestServiceResponseHandler.h"
#include "ResponsePayload.h"
#include "Types.h"
#include <string>

namespace smf {

    //! You will need to implement your own version of RequestServiceResponseHandler
    class RequestServiceResponseHandlerExt1: public RequestServiceResponseHandler
    {
    public:
        class ConsolidatedCommandResponse;
        typedef ResponsePayload Payload;

        //! \brief This is how you receive any responses to your request
        //!        For sender: Callback function from 
		//!        smf::RequestServiceRequestHandlerExt1::Request(const std::string &, UnsignedInt , const Payload &). If you send a 
		//!        request, and the application receiving it sends back a 
		//!        response. The response will be reported back to you 
		//!        through this function.
        //! \param receiver     The targetted receiver passed in when calling 
		//!                     the RequestServiceRequestHandler::Request function
        //! \param id           The identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param payload      The response as supplied by the receiver
        //! \note   A response from Response instead of ReportFailure simply means the command is successfully sent to the designated receiver. 
        //!         It does not mean the command is succesful. Whether the request is successful or not should be parsed from the payload passed to your application. 
        virtual void Response(const std::string &receiver, UnsignedInt id, Payload &payload) = 0;
        
        //! \brief This is the callback function that you received for the 
        //!        responses to your command, from 
        //!        smf::RequestServiceRequestHandlerExt1::Request(const std::string &, UnsignedInt, const std::string &, 
		//!					 const Payload &, UnsignedInt ,UnsignedInt) and 
        //!        smf::RequestServiceRequestHandlerExt1::RequestToSubscribers.
        //!        If you send a command through above functions,
        //!        and the application receiving this command sends back a 
        //!        response, the repsonse will be reported back to you through
        //!        this function.
        //! \param receiver      The name of the receiver that responded the 
        //!                      command.
        //! \param id            The identifier supplied by you in the 
        //!                      smf::RequestServiceRequestHandlerExt1::Request
        //!                      function.
        //! \param command       The name of the command that requested.
        //! \param responseCode  The response code that the receiver responsed, this value should indicate whether the command
        //!                      is successfully executed or not.
        //! \param payload       The binary data response that the receiver
        //!                      responded.
        virtual void Response(const std::string &receiver, 
                              UnsignedInt id, 
                              const std::string & command, 
                              UnsignedInt responseCode, 
                              const Payload & payload) = 0;
        

        //! \brief Callback function from smf::RequestServiceRequestHandler::Request
        //! \param receiver     The targetted receiver passed in when calling the RequestServiceRequestHandler::Request function
        //!                     If RequestToSubscribers is called, this is the receiver name that the subscriber registered.
        //! \param id           The identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param reason       Reason of the failure showing why sending the RS command to the designated receiver has failed.
        //!                     Refer to ArsMessage.h for possible failure reasons
        //! \note   The function is thread safe.
        //!         This function will return immediately once the command has been queued internally.
        virtual void ReportFailure(const std::string &receiver, UnsignedInt id, UnsignedInt reason) = 0;

        //! \brief Callback function from smf::RequestServiceRequestHandlerExt1::RequestToSubscribers (UnsignedInt, const std::string &, 
		//!								 const Payload &, UnsignedInt, UnsignedInt)
        //! \param id           The identifier supplied in the RequestToSubscriber call
        //! \param result       Consolidated result of the repsonses from all subscribers.
        virtual void ConsolidateResponse(UnsignedInt id, 
                                         const ConsolidatedCommandResponse & result) = 0;
        
        //virtual void ReportMissingMessages(UnsignedInt count) = 0;

        virtual ~RequestServiceResponseHandlerExt1(){}
    };

    
    class RequestServiceResponseHandlerExt1::ConsolidatedCommandResponse
    {
    public:
	    class IndexOutOfBounds;
		class SubscriberResponseDetails;
				
		virtual ~ConsolidatedCommandResponse() {}
		
		//! \return true if all receivers subscribing this command 
        //!              respond with expected successful response code
		virtual bool IsOverallSuccess() const = 0;
		
		//! \return Total number of subscribers that SMF will forward this command.
	    virtual UnsignedInt SubscriberCount() const = 0;
		
		//! \param index zero based index for the receiver list.
		//! \return the detailed response of the specified receiver index
	    virtual const SubscriberResponseDetails & operator[] (UnsignedInt index) const = 0;
		
    };
	
	
	class RequestServiceResponseHandlerExt1::ConsolidatedCommandResponse::SubscriberResponseDetails
	{
	public:
        //! \brief State of the request
        enum RequestForwardState
        {
            ForwardSuccess, //!< Request is successfully forwarded to the receiver
            ForwardFailed   //!< Request cannot forward to the receiver
        };

	//! \brief State of the responses from individual receivers
		enum ResponseReceiveState
		{
			PositiveResponse, //!< Response code from the receiver matches the expected successful response code provided by the sender
			ResponseTimeout, //!< No response is received before the timeout provided by the sender
			NegativeResponse,	 //!< Response code from the receiver does not match the expected successful response code provided by the sender
            ReceiverDisconnected, //!< The receiver is disconnected after the command has been forwarded to the receiver
            NA //!< No response is expected for this client; or the command failed to forward to the receiver
		};
	
		virtual ~SubscriberResponseDetails() {}
		
        //! \return the state on SMF sending the comamnd to the receiver.
        virtual RequestForwardState ForwardState() const = 0;

		//! \return the interpreted state by SMF according to the 
		//!         response code from the receiver.
		virtual ResponseReceiveState ReceiveState() const = 0;
		
		//! \return the binary data response from the receiver
		virtual const ResponsePayload & Payload() const = 0;
		
		//! \return the name of the receiver.
		virtual const std::string & Receiver() const = 0;
		
		//! \return the response code from the receiver
		virtual UnsignedInt ResponseCode() const = 0;
    };

    class RequestServiceResponseHandlerExt1::ConsolidatedCommandResponse::IndexOutOfBounds : public Error
	{
	public:
		IndexOutOfBounds(UnsignedInt index, UnsignedInt max);
	};
    
}

#endif 
