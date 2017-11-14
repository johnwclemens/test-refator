#ifndef SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_EXT1_H
#define SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_EXT1_H

#include "Types.h"
#include "SCtrlEndpointDetectionHeartbeat.h"
#include "SCtrlEndpointDetectionHeartbeatExt1.h"

namespace smf
{
    class SCtrlEndpointDetectionResponseHandlerExt1
    {
    public:

        SCtrlEndpointDetectionResponseHandlerExt1(void) { }

        virtual ~SCtrlEndpointDetectionResponseHandlerExt1(void) { }

    public:

        virtual void ReportSuccess(UnsignedInt identifier) = 0;

        virtual void ReportFailure(UnsignedInt identifier, UnsignedInt reason) = 0;

        virtual void ReportHeartbeat(const SCtrlEndpointDetectionHeartbeatExt1 & heartbeat) = 0;
    };

}

#endif
