#ifndef REQUESTSERVICERESPONSEHANDLER_H
#define REQUESTSERVICERESPONSEHANDLER_H

#include "ResponsePayload.h"
#include "Types.h"
#include <string>

namespace smf {

	//! You will need to implement your own version of RequestServiceResponseHandler
    class RequestServiceResponseHandler
    {
    public:
	    typedef ResponsePayload Payload;

	    //! \brief This is how you receive any responses to your request
		//! For sender: Callback function from smf::RequestServiceRequestHandler::Request.  
		//! If you send a request, and the application receiving it sends back a response. 
		//! The response will be reported back to you through this function.
		//! \param receiver		The targetted receiver passed in when calling the RequestServiceRequestHandler::Request function
		//! \param id			The identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param payload		The response as supplied by the receiver
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
		//!	\note	Note: A response from Response instead of ReportFailure simply means the command is successfully sent to the designated receiver. 
		//!			It does not mean the command is succesful. Whether the command is successful or not should be parsed from the payload passed to your application. 
	    virtual void Response(const std::string &receiver, UnsignedInt id, Payload &payload) = 0;

		//! \brief Callback function from smf::RequestServiceRequestHandler::Request
		//! \param receiver		The targetted receiver passed in when calling the RequestServiceRequestHandler::Request function
		//! \param id			The identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param reason		Reason of the failure showing why sending the RS command to the designated receiver has failed.
		//!						Refer to ArsMessage.h for possible failure reasons
		//! \note	The function is thread safe.
		//!			This function will return immediately once the command has been queued internally.
	    virtual void ReportFailure(const std::string &receiver, UnsignedInt id, UnsignedInt reason) = 0;
		
	    //virtual void ReportMissingMessages(unsigned int count) = 0;

	    virtual ~RequestServiceResponseHandler(){}
    };
}

#endif
