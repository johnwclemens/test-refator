#ifndef SCTRL_ENDPOINT_DETECTION_FORWARDER_RESPONSE_HANDLER_H
#define SCTRL_ENDPOINT_DETECTION_FORWARDER_RESPONSE_HANDLER_H

#include "Types.h"

namespace smf
{
    
    class SCtrlEndpointDetectionForwarderResponseHandler
    {
    public:
        SCtrlEndpointDetectionForwarderResponseHandler() { }
        virtual ~SCtrlEndpointDetectionForwarderResponseHandler() { }

        virtual void ReportFailure(UnsignedInt identifier, UnsignedInt reason) = 0;
    };

};


#endif