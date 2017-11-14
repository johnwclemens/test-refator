
#ifndef SERVICECHANNELEXT1_H
#define SERVICECHANNELEXT1_H

#include "ServiceChannel.h"

namespace smf{
    class ServiceChannelExt1 : public ServiceChannel
    {
    public:
        ServiceChannelExt1() {} 
        virtual ~ServiceChannelExt1() {}

        virtual void SetConnectionKeepaliveTimeout(unsigned int timeoutMsec, 
                                                   unsigned int keepaliveIntervalMsec) = 0;
    };
}


#endif