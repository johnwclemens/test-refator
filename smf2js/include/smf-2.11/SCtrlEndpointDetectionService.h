#ifndef SCTRL_ENDPOINT_DETECTION_SERVICE_H
#define SCTRL_ENDPOINT_DETECTION_SERVICE_H
#include "SCtrlEndpointDetectionResponseHandler.h"
#include "SCtrlEndpointDetectionResponseHandlerExt1.h"
#include "SCtrlEndpointDetectionResponseHandlerExt2.h"

namespace smf
{
	class ServiceChannel;
	class Logger;
	class SCtrlEndpointDetectionRequestHandler;
	class SCtrlEndpointDetectionResourcePool;
	class ServiceBufferPool;

    namespace SCtrlService
    {
        //! \brief  This function will create a SCtrlEndpointDetectionRequestHandler 
        //!         which can be used to subscribe for the heartbeat messages.
		//! \param  responseHandler You must provide an implementation of this. Your
        //!                         implementation of the smf::SCtrlEndpointDetectionResponseHandler 
        //!                         interface, this response handler can receive all heartbeats,
        //!                         however, only heartbeat version 1 fields are available.
		//! \param  channel         Use smf::Client::Connect to get this. The ServiceChannel
        //!                         returned from the call to smf::Client::Connect. See 
        //!                         Opening an SMF service channel.
		//! \param  logger          Can be null, your own implementation of an smf::Logger or a 
        //!                         file logger (use smf::fileLogger function). A local file 
        //!                         logger return from a call to smf::InternalLogger. See 
        //!                         Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you
        //!                         may provide your own implementation of the Logger 
        //!                         interface instead.
		//! \param  queueSize       The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return                 A pointer to a Smf::SCtrlEndpointDetectionRequestHandler
        //!                         object.
		//!	\remark                 Include: SCtrlEndpointDetectionRequestHandler.h, Logger.h.
		//!	\post                   Cleanup: You must call smf::SCtrlService::CloseEndpointDetectionSubscriberChannel 
        //!                         to cleanup.
		//! \exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
		//! \note					This function is thread safe. 
        smf::SCtrlEndpointDetectionRequestHandler * OpenSCtrlEndpointDetectionRequestChannel(
            smf::SCtrlEndpointDetectionResponseHandler *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger,
            unsigned int queueSize = 0);

        //! \brief  This function will create a SCtrlEndpointDetectionRequestHandler 
        //!         which can be used to subscribe for the heartbeat messages.
		//! \param  responseHandler You must provide an implementation of this. Your
        //!                         implementation of the smf::SCtrlEndpointDetectionResponseHandlerExt1 
        //!                         interface, this response handler can receive all heartbeats,
        //!                         however, heartbeat version 1 and version 2 fields are 
        //!                         available.
		//! \param  channel         Use smf::Client::Connect to get this. The ServiceChannel
        //!                         returned from the call to smf::Client::Connect. See 
        //!                         Opening an SMF service channel.
		//! \param  logger          Can be null, your own implementation of an smf::Logger or a 
        //!                         file logger (use smf::fileLogger function). A local file 
        //!                         logger return from a call to smf::InternalLogger. See 
        //!                         Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you
        //!                         may provide your own implementation of the Logger 
        //!                         interface instead.
		//! \param  queueSize       The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return                 A pointer to a Smf::SCtrlEndpointDetectionRequestHandler
        //!                         object.
		//!	\remark                 Include: SCtrlEndpointDetectionRequestHandler.h, Logger.h.
		//!	\post                   Cleanup: You must call smf::SCtrlService::CloseEndpointDetectionSubscriberChannel 
        //!                         to cleanup.
		//! \exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
		//! \note					This function is thread safe. 
        smf::SCtrlEndpointDetectionRequestHandler * OpenSCtrlEndpointDetectionRequestChannelExt1(
            smf::SCtrlEndpointDetectionResponseHandlerExt1 *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger,
            unsigned int queueSize = 0);

        //! \brief  This function will create a SCtrlEndpointDetectionRequestHandler 
        //!         which can be used to subscribe for the heartbeat messages.
		//! \param  responseHandler You must provide an implementation of this. Your
        //!                         implementation of the smf::SCtrlEndpointDetectionResponseHandlerExt2 
        //!                         interface, this response handler can receive all heartbeats,
        //!                         however, heartbeat version 1, version 2 and version 3 fields are 
        //!                         available.
		//! \param  channel         Use smf::Client::Connect to get this. The ServiceChannel
        //!                         returned from the call to smf::Client::Connect. See 
        //!                         Opening an SMF service channel.
		//! \param  logger          Can be null, your own implementation of an smf::Logger or a 
        //!                         file logger (use smf::fileLogger function). A local file 
        //!                         logger return from a call to smf::InternalLogger. See 
        //!                         Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you
        //!                         may provide your own implementation of the Logger 
        //!                         interface instead.
		//! \param  queueSize       The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return                 A pointer to a Smf::SCtrlEndpointDetectionRequestHandler
        //!                         object.
		//!	\remark                 Include: SCtrlEndpointDetectionRequestHandler.h, Logger.h.
		//!	\post                   Cleanup: You must call smf::SCtrlService::CloseEndpointDetectionSubscriberChannel 
        //!                         to cleanup.
		//! \exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
		//! \note					This function is thread safe. 
        smf::SCtrlEndpointDetectionRequestHandler * OpenSCtrlEndpointDetectionRequestChannelExt2(
            smf::SCtrlEndpointDetectionResponseHandlerExt2 *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger,
            unsigned int queueSize = 0);


        //! \brief  You should call this function to close a smf::SCtrlEndpointDetectionRequestHandler 
        //!         once you have finished with it.
		//! \param  channel         The same service channel that was passed in to 
        //!                         OpenEndpointDetectionSubscriberChannel.	The smf::ServiceChannel 
        //!                         pointer used when opening this SCtrlEndpointDetectionRequestHandler. 
		//! \param  requestHandler  The request handler returned from OpenEndpointDetectionSubscriberChannel.
		//!	                        A request handler created using the 
        //!                         smf::SCtrlService::SCtrlEndpointDetectionRequestHandler function.
		//!	\remark					Include: SCtrlEndpointDetectionRequestHandler.h
		//!	\exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
        //! \note                   This function is thread safe.
        void CloseSCtrlEndpointDetectionRequestChannel(
            smf::ServiceChannel * serviceChannel,
            smf::SCtrlEndpointDetectionRequestHandler * requestHandler);

		//! \brief You can call this to create an object of smf::SCtrlEndpointDetectionResourcePool, which provide 
		//         shared resources for multiple SCtrl Endpoint Detection Service. By using smf::SCtrlEndpointDetectionResourcePool, multiple
		//         SCtrl Endpoint Detection Service will share the threads and buffers in the resource pool. You should only use
		//         smf::SCtrlEndpointDetectionResourcePool if you need to create large amount of SCtrl Endpoint Detection Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::SCtrlEndpointDetectionResourcePool* CreateEndpointDetectionResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyEndpointDetectionResourcePool(smf::ServiceBufferPool* bufferPool, smf::SCtrlEndpointDetectionResourcePool* resPool);

		//! \brief  This function will create a SCtrlEndpointDetectionRequestHandler 
        //!         which can be used to subscribe for the heartbeat messages.
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param  responseHandler You must provide an implementation of this. Your
        //!                         implementation of the smf::SCtrlEndpointDetectionResponseHandlerExt1 
        //!                         interface, this response handler can receive all heartbeats,
        //!                         however, heartbeat version 1 and version 2 fields are 
        //!                         available.
		//! \param  channel         Use smf::Client::Connect to get this. The ServiceChannel
        //!                         returned from the call to smf::Client::Connect. See 
        //!                         Opening an SMF service channel.
		//! \param  logger          Can be null, your own implementation of an smf::Logger or a 
        //!                         file logger (use smf::fileLogger function). A local file 
        //!                         logger return from a call to smf::InternalLogger. See 
        //!                         Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you
        //!                         may provide your own implementation of the Logger 
        //!                         interface instead.
		//! \return                 A pointer to a Smf::SCtrlEndpointDetectionRequestHandler
        //!                         object.
		//!	\remark                 Include: SCtrlEndpointDetectionRequestHandler.h, Logger.h.
		//!	\post                   Cleanup: You must call smf::SCtrlService::CloseEndpointDetectionSubscriberChannel 
        //!                         to cleanup.
		//! \exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
		//! \note					This function is thread safe. 
		smf::SCtrlEndpointDetectionRequestHandler * OpenSCtrlEndpointDetectionRequestChannelExt1(
			smf::SCtrlEndpointDetectionResourcePool* resPool,
            smf::SCtrlEndpointDetectionResponseHandlerExt1 *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger);

		//! \brief  This function will create a SCtrlEndpointDetectionRequestHandler 
        //!         which can be used to subscribe for the heartbeat messages.
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param  responseHandler You must provide an implementation of this. Your
        //!                         implementation of the smf::SCtrlEndpointDetectionResponseHandlerExt1 
        //!                         interface, this response handler can receive all heartbeats,
        //!                         however, heartbeat version 1 and version 2 fields are 
        //!                         available.
		//! \param  channel         Use smf::Client::Connect to get this. The ServiceChannel
        //!                         returned from the call to smf::Client::Connect. See 
        //!                         Opening an SMF service channel.
		//! \param  logger          Can be null, your own implementation of an smf::Logger or a 
        //!                         file logger (use smf::fileLogger function). A local file 
        //!                         logger return from a call to smf::InternalLogger. See 
        //!                         Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you
        //!                         may provide your own implementation of the Logger 
        //!                         interface instead.
		//! \return                 A pointer to a Smf::SCtrlEndpointDetectionRequestHandler
        //!                         object.
		//!	\remark                 Include: SCtrlEndpointDetectionRequestHandler.h, Logger.h.
		//!	\post                   Cleanup: You must call smf::SCtrlService::CloseEndpointDetectionSubscriberChannel 
        //!                         to cleanup.
		//! \exception smf::Error   You should at least catch smf::Error. Specific exceptions 
        //!                         that might be thrown are defined in SCtrlEndpointDetectionRequestHandler.h.
		//! \note					This function is thread safe. 
		smf::SCtrlEndpointDetectionRequestHandler * OpenSCtrlEndpointDetectionRequestChannelExt2(
			smf::SCtrlEndpointDetectionResourcePool* resPool,
            smf::SCtrlEndpointDetectionResponseHandlerExt2 *  responseHandler,
            smf::ServiceChannel * serviceChannel,
            smf::Logger * logger);

    };
};

#endif //SCTRL_ENDPOINT_DETECTION_SERVICE_H


