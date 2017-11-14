#ifndef REQUESTSERVICEREQUESTHANDLER_H
#define REQUESTSERVICEREQUESTHANDLER_H

#include "Error.h"
#include "ArsPayload.h"
#include "Types.h"
#include <string>

namespace smf {

    class Logger;
    class ServiceChannel;
    class RequestServiceResponseHandler;
    class RequestServiceRequestHandler;

    
    //! Use this to send a request to a receiver
    class RequestServiceRequestHandler
    {
    public:
	    typedef ArsPayload Payload;

		//! \brief Send a request to a receiver 
		//! \param receiver		The registered receiver name to receive the command
		//! \param id			This is an identifier defined by the application. 
		//!						SMF will pass this back to you in the callback function.
		//! \param payload		The command in vector<char> to be sent to the receiver. (it is arbitrary binary data)
		//! \post	The response will be reported back through your implementation of the 
		//!			smf::RequestServiceResponseHandler::Response or smf::RequestServiceResponseHandler::ReportFailure
		//! \note	Function is protected and will return immediately
	    virtual void Request(const std::string &receiver, UnsignedInt id, const Payload &payload) = 0;
        virtual ~RequestServiceRequestHandler() {}

        // Exceptions
	    class ReceiverNameTooLong;
	    class CouldNotQueueItem;
	    class CouldNotGetBuffer;
	    class ConnectionDropped;
	    class SizeLimitExceedsAllocationLimit;
    };

    class RequestServiceRequestHandler::ReceiverNameTooLong : public Error
	{
	public:
		explicit ReceiverNameTooLong(const char *message);
	};

    class RequestServiceRequestHandler::CouldNotQueueItem : public Error
	{
	public:
		CouldNotQueueItem();
	};

    class RequestServiceRequestHandler::CouldNotGetBuffer : public Error
	{
	public:
		explicit CouldNotGetBuffer(unsigned int size);
	};

    class RequestServiceRequestHandler::ConnectionDropped : public Error
	{
	public:
		ConnectionDropped();
	};

    class RequestServiceRequestHandler::SizeLimitExceedsAllocationLimit : public Error
	{
	public:
		SizeLimitExceedsAllocationLimit(const char* details);
	};
}

#endif
