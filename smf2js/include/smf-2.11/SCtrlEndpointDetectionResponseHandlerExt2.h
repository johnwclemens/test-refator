#ifndef SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_EXT2_H
#define SCTRL_ENDPOINT_DETECTION_RESPONSE_HANDLER_EXT2_H

#include "Types.h"
#include "SCtrlEndpointDetectionHeartbeat.h"
#include "SCtrlEndpointDetectionHeartbeatExt1.h"
#include "SCtrlEndpointDetectionHeartbeatExt2.h"

namespace smf
{
    class SCtrlEndpointDetectionResponseHandlerExt2
    {
    public:

        SCtrlEndpointDetectionResponseHandlerExt2(void) { }

        virtual ~SCtrlEndpointDetectionResponseHandlerExt2(void) { }

    public:

        virtual void ReportSuccess(UnsignedInt identifier) = 0;

        virtual void ReportFailure(UnsignedInt identifier, UnsignedInt reason) = 0;

        virtual void ReportHeartbeat(const SCtrlEndpointDetectionHeartbeatExt2 & heartbeat) = 0;
    };

}

#endif
