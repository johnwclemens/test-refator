
#ifndef BULKPARAMETERSERVICEENTRYPOINTS_H
#define BULKPARAMETERSERVICEENTRYPOINTS_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class BulkParameterServiceResourcePool;
	class ServiceBufferPool;
	class BulkParameterRequestHandler;
	class BulkParameterResponseHandler;
	class BulkCompParameterRequestHandler;
	class BulkCompParameterResponseHandler;
	class BulkCompParameterRequestHandlerExt1;
	class BulkCompParameterResponseHandlerExt1;
    class BulkCompParameterRequestHandlerExt2;
    class BulkParameterRequestHandlerExt1;


	namespace BulkParameterService{
		

		const char* LibName();
		
		
		//! \brief Opens a channel to the bulk parameter service which can send and receive bulk parameter requests and updates to the smf server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkParameterResponseHandler interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize            The internal queue size for handling responses.
		//! \return		          A pointer to a Smf::BulkParameterRequestHandler object.
		//!	\remark		Include: BulkParameterService.h, BulkParameterRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkParameterRequestHandler* OpenRequestChannel(
				BulkParameterResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief Opens a channel to the bulk parameter service which can send and receive bulk parameter requests and updates to the smf server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkParameterResponseHandler interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize            The internal queue size for handling responses.
		//! \return		          A pointer to a Smf::BulkParameterRequestHandlerExt1 object.
		//!	\remark		Include: BulkParameterService.h, BulkParameterRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkParameterRequestHandlerExt1* OpenRequestChannelExt1(
				BulkParameterResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief Opens a channel to the bulk parameter service with compression support which can send and receive bulk parameter requests and updates to the smf server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkCompParameterResponseHandler interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize            The internal queue size for handling responses.
		//! \return		          A pointer to a Smf::BulkCompParameterRequestHandler object.
		//!	\remark		Include: BulkParameterService.h, BulkCompParameterRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkCompParameterRequestHandler* OpenRequestChannel(
				BulkCompParameterResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief Opens a channel to the bulk resizable parameter service with compression support which can send and receive bulk parameter requests and updates to the smf server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkCompParameterResponseHandlerExt1 interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize            The internal queue size for handling responses.
		//! \return		          A pointer to a Smf::BulkCompParameterRequestHandlerExt1 object.
		//!	\remark		Include: BulkParameterService.h, BulkCompParameterRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkCompParameterRequestHandlerExt1* OpenRequestChannel(
				BulkCompParameterResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief Opens a channel to the bulk resizable parameter service with compression and non-transactional query support which can send and receive bulk parameter requests and updates to the smf server
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkCompParameterResponseHandlerExt1 interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize            The internal queue size for handling responses.
		//! \return		          A pointer to a Smf::BulkCompParameterRequestHandlerExt2 object.
		//!	\remark		Include: BulkParameterService.h, BulkCompParameterRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkCompParameterRequestHandlerExt2* OpenRequestChannelExt2(
				BulkCompParameterResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief You should call this function to close a smf::BulkParameterRequestHandler once you have finished with it.
		//! \param channel  The same service channel that was passed in to OpenRequestChannel
		//!                        The smf::ServiceChannel pointer used when opening this BulkParameterRequestHandler. 
		//! \param requestHandler  The request handler returned from OpenRequestChannel
		//!                                     A request handler created using the smf::BulkParameterService::OpenRequestChannel function.
		//!	\remark						Include: BulkParameterService.h
		//! \exception smf::Error
		void CloseRequestChannel(
				ServiceChannel* channel, 
				BulkParameterRequestHandler* requestHandler
				);

		//! \brief You should call this function to close a smf::BulkParameterRequestHandlerExt1 once you have finished with it.
		//! \param channel  The same service channel that was passed in to OpenRequestChannel
		//!                        The smf::ServiceChannel pointer used when opening this BulkParameterRequestHandlerExt1. 
		//! \param requestHandler  The request handler returned from OpenRequestChannel
		//!                                     A request handler created using the smf::BulkParameterService::OpenRequestChannel function.
		//!	\remark						Include: BulkParameterService.h
		//! \exception smf::Error
		void CloseRequestChannel(
				ServiceChannel* channel, 
				BulkParameterRequestHandlerExt1* requestHandler
				);

		//! \brief You should call this function to close a smf::BulkCompParameterRequestHandler once you have finished with it.
		//! \param channel  The same service channel that was passed in to OpenRequestChannel
		//!                        The smf::ServiceChannel pointer used when opening this BulkCompParameterRequestHandler. 
		//! \param requestHandler  The request handler returned from OpenRequestChannel
		//!                                     A request handler created using the smf::BulkParameterService::OpenRequestChannel function.
		//!	\remark						Include: BulkParameterService.h
		//! \exception smf::Error
		void CloseRequestChannel(
				ServiceChannel* channel, 
				BulkCompParameterRequestHandler* requestHandler
				);

		//! \brief You should call this function to close a smf::BulkCompParameterRequestHandlerExt1 once you have finished with it.
		//! \param channel  The same service channel that was passed in to OpenRequestChannel
		//!                        The smf::ServiceChannel pointer used when opening this BulkCompParameterRequestHandlerExt1. 
		//! \param requestHandler  The request handler returned from OpenRequestChannel
		//!                                     A request handler created using the smf::BulkParameterService::OpenRequestChannel function.
		//!	\remark						Include: BulkParameterService.h
		//! \exception smf::Error
		void CloseRequestChannel(
				ServiceChannel* channel, 
				BulkCompParameterRequestHandlerExt1* requestHandler
				);

		//! \brief You should call this function to close a smf::BulkCompParameterRequestHandlerExt2 once you have finished with it.
		//! \param channel  The same service channel that was passed in to OpenRequestChannel
		//!                        The smf::ServiceChannel pointer used when opening this BulkCompParameterRequestHandlerExt2. 
		//! \param requestHandler  The request handler returned from OpenRequestChannel
		//!                                     A request handler created using the smf::BulkParameterService::OpenRequestChannel function.
		//!	\remark						Include: BulkParameterService.h
		//! \exception smf::Error
		void CloseRequestChannel(
				ServiceChannel* channel, 
				BulkCompParameterRequestHandlerExt2* requestHandler
				);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::BulkParameterServiceResourcePool, which provide 
		//         shared resources for multiple Bulk Parameter Service. By using smf::BulkParameterServiceResourcePool, multiple
		//         Bulk Parameter Service will share the threads and buffers in the resource pool. You should only use
		//         smf::BulkParameterServiceResourcePool if you need to create large amount of Bulk Parameter Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::BulkParameterServiceResourcePool* CreateServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::BulkParameterServiceResourcePool* resPool);

		//! \brief Opens a channel to the bulk resizable parameter service with compression and non-transactional query support which can send and receive bulk parameter requests and updates to the smf server
		//! \param resPool		Create via CreateServiceResourcePool
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::BulkCompParameterResponseHandlerExt1 interface.
		//!							See the samples/PsdBulk directory in the SMF-SDK for an example implementation.
		//! \param channel	          Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger		Can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function).  See Opening a Logger. 
		//!                                     Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return		          A pointer to a Smf::BulkCompParameterRequestHandlerExt2 object.
		//!	\remark		Include: BulkParameterService.h, BulkCompParameterRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::BulkParameterService::CloseRequestChannel to cleanup 
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in BulkParameterRequestHandler.h.
		BulkCompParameterRequestHandlerExt2* OpenRequestChannelExt2(
				smf::BulkParameterServiceResourcePool* resPool,
				BulkCompParameterResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger
				);
#endif
        
		unsigned int SetChannelLimit(unsigned int);

		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);
	}
}
#endif