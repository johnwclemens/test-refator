#ifndef REQUESTSERVICETRANSMITTER_H
#define REQUESTSERVICETRANSMITTER_H

#include "ConnectionIdentity.h"
#include "Error.h"
#include "ArsPayload.h"
#include "Types.h"
#include <string>

namespace smf {

    class RequestServiceReceiver;
    class ServiceChannel;
    class Logger;

	//! Use this class to send a respond after receiving a request through RequestServiceReceiver
    class RequestServiceTransmitter
    {
    public:
	    typedef ArsPayload Payload;

		//! \param sender			The identifier of the SMF client that was passed in RequestServiceReceiver::Request
		//!	\param receiverName		The receiver name (the application can have more than one receiver)
		//! \param payload			The response in vector<char>
		//! \post	SMF will call back smf::RequestServiceReceiver::ReportFailure if SMF can't send a reponse
	    virtual void Response(const ConnectionIdentity sender, const std::string& receiverName, 
							    const Payload &payload) = 0;

		//! \brief An application must register one or more receivers by name in order to receive requests
		//!			An application can register any name(s) it wants but it must be unique to the server
		//! \param receiver		Receiver name to be registered
		//! \param identifier	This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		//! \post	SMF will call back smf::RequestServiceReceiver::RegistrationSuccess or
		//!			smf::RequestServiceReceiver::RegistrationFailure
	    virtual void Register(const std::string &receiver, UnsignedInt identifier) = 0;
		//! \brief An application can use this to request information about the connection associated with this
		//!        ConnectionIdentity
		//! \param receiver		Receiver name (must already be registered)
		//! \param connection   The ConnectionIdentity of the connection to request information about. This is passed
		//!					    into the RequestServiceReceiver::Request function when your application receives a request.
		//! \param identifier	This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		virtual void RequestConnectionInfo(const std::string& receiver, const ConnectionIdentity connection, UnsignedInt identifier) = 0;

	    virtual ~RequestServiceTransmitter(){}

        // Exceptions
	    class ReceiverNameTooLong;
	    class ConnectionDropped;
	    class SizeLimitExceedsAllocationLimit;
	    class CouldNotGetBuffer;
	    class CouldNotHandleRequest;
	    class InvalidConnectionIdentity;
	    class NullConnectionIdentity;
	    class InvalidTransmitionHandler;
    };

    class RequestServiceTransmitter::ReceiverNameTooLong : public Error
	{
	public:
		explicit ReceiverNameTooLong(const char *message);
	};

    class RequestServiceTransmitter::ConnectionDropped : public Error
	{
	public:
		ConnectionDropped();
	};

	class RequestServiceTransmitter::SizeLimitExceedsAllocationLimit : public Error
	{
	public:
		explicit SizeLimitExceedsAllocationLimit(const char* error);
	};

	class RequestServiceTransmitter::CouldNotGetBuffer : public Error
	{
	public:
		explicit CouldNotGetBuffer(unsigned int size);
    };

	class RequestServiceTransmitter::CouldNotHandleRequest : public Error
	{
	public:
		CouldNotHandleRequest();
	};

	class RequestServiceTransmitter::InvalidConnectionIdentity : public Error
	{
	public:
		InvalidConnectionIdentity();
	};

	class RequestServiceTransmitter::NullConnectionIdentity : public Error
	{
	public:
		NullConnectionIdentity();
	};

	class RequestServiceTransmitter::InvalidTransmitionHandler : public Error
	{
	public:
		explicit InvalidTransmitionHandler(const char * where);
	};
}

#endif
