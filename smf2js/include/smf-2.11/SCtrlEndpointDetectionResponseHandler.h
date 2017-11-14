#ifndef SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_H
#define SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_H

#include "Types.h"
#include "SCtrlEndpointDetectionHeartbeat.h"
#include "SCtrlEndpointDetectionHeartbeatExt1.h"

namespace smf
{

    class SCtrlEndpointDetectionResponseHandler
    {
    public:

        SCtrlEndpointDetectionResponseHandler(void) { }

        virtual ~SCtrlEndpointDetectionResponseHandler(void) { }

    public:

        virtual void ReportSuccess(UnsignedInt identifier) = 0;

        virtual void ReportFailure(UnsignedInt identifier, UnsignedInt reason) = 0;

        virtual void ReportHeartbeat(const SCtrlEndpointDetectionHeartbeat & heartbeat) = 0;
    };

};

#endif //SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_H
