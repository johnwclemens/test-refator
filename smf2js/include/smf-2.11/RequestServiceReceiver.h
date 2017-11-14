
#ifndef REQUESTSERVICERECEIVERRESPONSEHANDLER_H
#define REQUESTSERVICERECEIVERRESPONSEHANDLER_H

#include "ConnectionIdentity.h"
#include "ResponsePayload.h"
#include "RequestServiceConnectionInfo.h"
#include "Types.h"
#include "SenderExpectation.h"

#include <string>

namespace smf {

	//! You will need to implement your own version of RequestServiceReceiver
	//! After you've registered using the RequestServiceTransmitter::Register you'll receive all requests through your implementation of this class
    class RequestServiceReceiver
    {
    public:
    	
	    typedef ResponsePayload Payload;
		typedef std::vector<RequestServiceConnectionInfo> ConnectionInformation;

		//! \brief Callback function from smf::RequestServiceTransmitter::Register
		//! \param receiver		The receiver
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
	    virtual void RegistrationSuccess(const std::string &receiver, UnsignedInt identifier) = 0;

		//! \brief Callback function from smf::RequestServiceTransmitter::Register
		//! \param receiver		The receiver
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param reason		Reason of the registration failure. Refer to ArsMessage.h for possible failure reasons
	    virtual void RegistrationFailure(	const std::string &receiver, 
										    UnsignedInt identifier,
										    UnsignedInt reason) = 0;
										

		//! \brief This is how you receive request from the sender application
		//! This is where you receive requests from any senders
		//! \param id	This identifies the sender.  if you wish to send a response, you'll need to pass this to RequestServiceTransmitter::Response
		//! \param receiver	This is the name of the receiver registered using RequestServiceTransmitter::Register
		//! \param payload	This is the request (it is arbitrary binary data)
	    virtual void Request(const ConnectionIdentity id, const std::string &receiver, Payload &payload) = 0;

		//! \brief Callback function from smf::RequestServiceTransmitter::Reponse
		//! Called if SMF can't send a response
		//! \param receiver		The receiver name
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param reason		Reason of failure.  Refer to ArsMessage.h for possible failure reasons
		virtual void ReportFailure(			const std::string &receiver, 
										    UnsignedInt identifier,
										    UnsignedInt reason) = 0;


		//! \brief Callback function from smf::RequestServiceTransmitter::RequestConnectionInfo
		//! \param receiver		The receiver name
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param ConnectionInfomation This is the connection information.
	    virtual void ReportConnectionInformation(
											const std::string &receiver, 
											UnsignedInt identifier,
											const ConnectionInformation&) = 0;

	    virtual ~RequestServiceReceiver(){}
    };
}

#endif
