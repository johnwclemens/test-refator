
#ifndef SCTRLENDPOINTDETECTIONMESSAGE_H_
#define SCTRLENDPOINTDETECTIONMESSAGE_H_

namespace smf
{
    namespace SCtrlEndpointDetection
    {
        enum FailureSeverity
        {
		    SeverityUnknown         = 0,
            SeverityReservedSlot1   = 1,
            SeverityReservedSlot2   = 2,
            SeverityWarning         = 3,
            SeverityReservedSlot4   = 4,
            SeverityReservedSlot5   = 5,
            SeverityCritical        = 6,
            SeverityReservedSlot7   = 7
        };
    }
}

#endif
