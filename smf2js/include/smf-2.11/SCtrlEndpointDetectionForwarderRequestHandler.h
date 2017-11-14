#ifndef SCTRL_ENDPOINT_DETECTION_FORWARDER_REQUEST_HANDLER_H
#define SCTRL_ENDPOINT_DETECTION_FORWARDER_REQUEST_HANDLER_H

#include "SCtrlEndpointDetectionHeartbeatContainer.h"
#include "Types.h"
#include "Error.h"

namespace smf
{
    
    class SCtrlEndpointDetectionForwarderRequestHandler
    {
    public:
        
		class SizeLimitExceedsAllocationLimit : public Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details) : Error(details)
			{
			}
		};

		class CouldNotGetBuffer : public Error
		{
		public:
			CouldNotGetBuffer(unsigned int size)
				: Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}
		};

		class CouldNotHandleRequest : public Error
		{
		public:
			CouldNotHandleRequest()
				: Error("SCtrlEndpointDetectionForwarderRequestHandler could not handle "
                    "request because the queue of the client service is full")
			{
				  
			}
		};

		class ConnectionDropped : public Error
		{
		public:
			ConnectionDropped() 
				: Error("The connection to the server has been closed or dropped")
			{
			}
		};

    public:
        SCtrlEndpointDetectionForwarderRequestHandler() { }
        virtual ~SCtrlEndpointDetectionForwarderRequestHandler() { }

        virtual void Forward(UnsignedInt identifier, const SCtrlEndpointDetectionHeartbeatContainer & heartbeat) = 0;
    };

};


#endif