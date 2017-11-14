#pragma once

#include "SCtrlEndpointDetectionHeartbeatExt1.h"
#include "SCtrlEndpointDetectionMessage.h"
#include <vector>

namespace smf
{
    class SCtrlEndpointDetectionHeartbeatExt2: public SCtrlEndpointDetectionHeartbeatExt1
    {
    public:

        SCtrlEndpointDetectionHeartbeatExt2(SCtrlEndpointDetectionHeartbeatExt2 * pHeartbeat);
        virtual ~SCtrlEndpointDetectionHeartbeatExt2(void);

        

        class FailureReason
        {
        public:
            unsigned int ReasonCode() const;
            SCtrlEndpointDetection::FailureSeverity Severity() const;
            FailureReason(unsigned int reasonCode, SCtrlEndpointDetection::FailureSeverity severity);
            virtual ~FailureReason();
        private:
            unsigned int reasonCode;
            SCtrlEndpointDetection::FailureSeverity severity;
        };

        //! \return a const vector of unsigned integers of error codes on the reasons
        //!         that causing the overall unhealthy.
        //! \note SCtrlEndpointDetectionHeartbeatExt2 is not thread-safe.
        virtual const smf::ConstantVector<FailureReason> & SystemFailureReasons() const;

    protected:
        SCtrlEndpointDetectionHeartbeatExt2(void);

    private:
        SCtrlEndpointDetectionHeartbeatExt2(const SCtrlEndpointDetectionHeartbeatExt2&);
        SCtrlEndpointDetectionHeartbeatExt2& operator =(const SCtrlEndpointDetectionHeartbeatExt2&);

        SCtrlEndpointDetectionHeartbeatExt2 * m_pHeartbeatExt2;
    };
}