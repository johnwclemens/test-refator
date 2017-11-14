#ifndef SCtrlEndpointDetectionHeartbeatContainer_H
#define SCtrlEndpointDetectionHeartbeatContainer_H

#include "Types.h"

namespace smf {
    class SCtrlEndpointDetectionHeartbeatContainer
    {
    public:
        SCtrlEndpointDetectionHeartbeatContainer(unsigned int heartbeatSize, void * heartbeatBuffer, unsigned int ip);
        ~SCtrlEndpointDetectionHeartbeatContainer();
        const char * Buffer() const;
        UnsignedInt HeartbeatBufferSize() const;
        UnsignedInt TotalBufferSize() const;
    private:
        SCtrlEndpointDetectionHeartbeatContainer();
        SCtrlEndpointDetectionHeartbeatContainer( const SCtrlEndpointDetectionHeartbeatContainer &);
        SCtrlEndpointDetectionHeartbeatContainer& operator= (SCtrlEndpointDetectionHeartbeatContainer &);
    
    private:
        void * buffer;
        unsigned int heartbeatBufferSize;
        unsigned int totalBufferSize;
    };
};

#endif