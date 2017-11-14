#ifndef SCTRL_ENDPOINT_DETECTION_FORWARDER_SERVICE_H
#define SCTRL_ENDPOINT_DETECTION_FORWARDER_SERVICE_H

namespace smf
{
	class ServiceChannel;
	class Logger;
	class SCtrlEndpointDetectionForwarderRequestHandler;
	class SCtrlEndpointDetectionForwarderResponseHandler;
	class SCtrlEndpointDetectionForwarderResourcePool;
	class ServiceBufferPool;

    namespace SCtrlService
    {
        smf::SCtrlEndpointDetectionForwarderRequestHandler * OpenSCtrlEndpointDetectionForwarderChannel(
            smf::SCtrlEndpointDetectionForwarderResponseHandler *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger,
            unsigned int queueSize = 0);

        void CloseSCtrlEndpointDetectionForwarderChannel(
            smf::ServiceChannel * serviceChannel,
            smf::SCtrlEndpointDetectionForwarderRequestHandler * requestHandler);

		smf::SCtrlEndpointDetectionForwarderResourcePool* CreateEndpointDetectionForwarderResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyEndpointDetectionForwarderResourcePool(smf::ServiceBufferPool* bufferPool, smf::SCtrlEndpointDetectionForwarderResourcePool* resPool);

		smf::SCtrlEndpointDetectionForwarderRequestHandler * OpenSCtrlEndpointDetectionForwarderChannel(
            smf::SCtrlEndpointDetectionForwarderResourcePool* resPool,
			smf::SCtrlEndpointDetectionForwarderResponseHandler *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger);
    };
};

#endif //SCTRL_ENDPOINT_DETECTION_FORWARDER_SERVICE_H
