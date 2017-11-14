#ifndef SCTRLSERVICEENTRYPOINTS_H
#define SCTRLSERVICEENTRYPOINTS_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class SCtrlServiceRequestHandler;
	class SCtrlServiceRequestHandlerExt1;
	class SCtrlServiceResponseHandler;
	class SCtrlAppStatusRequestHandler;
	class SCtrlAppStatusResponseHandler;
	class SCtrlAppStatusRequestHandlerExt1;
	class SCtrlAppStatusResponseHandlerExt1;
#ifdef WIN32
	class SCtrlAppStatusRequestHandlerExt2;
	class SCtrlAppStatusResponseHandlerExt2;
#endif
	class SCtrlAppStatusResourcePool;
	class SCtrlServiceResourcePool;
	class ServiceBufferPool;

	namespace SCtrlService{
		

		const char* LibName();

		//! \brief This function will create a SCtrlServiceRequestHandler which can be used to create schedule, query schedule task and process status, and modify schedule from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::SCtrlServiceResponseHandler interface.
		//!							See the samples/SCtrlService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlServiceRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlServiceRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlServiceRequestHandler* OpenRequestChannel(
				SCtrlServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlAppStatusRequestHandler which can be used to register the process, publish heartbeat and update application health status
		//!	       This function is deprecated. You should use OpenAppStatusRequestChannelExt1 function instead.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandler* OpenAppStatusRequestChannel(
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlAppStatusRequestHandler which can be used to register the process, publish heartbeat and update application health status
		//!	       This function is deprecated. You should use OpenAppStatusRequestChannelExt1 function instead.
		//! \param responseHandler	You must provide an implementation of this.  Your implementation of the smf::SCtrlAppStatusResponseHandler interface.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandler* OpenAppStatusRequestChannel(
				SCtrlAppStatusResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt1 which can be used to register the process, publish heartbeat and update application health status
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt1 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt1 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt1.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt1* OpenAppStatusRequestChannelExt1(
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt1 which can be used to register the process, publish heartbeat and update application health status
		//! \param responseHandler	You must provide an implementation of this.  Your implementation of the smf::SCtrlAppStatusResponseHandlerExt1 interface.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt1 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt1 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt1.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt1* OpenAppStatusRequestChannelExt1(
				SCtrlAppStatusResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

#ifdef WIN32
		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt2 which can be used to register the process, publish heartbeat and update application health status
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt2 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt2 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt2.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt2* OpenAppStatusRequestChannelExt2(
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt2 which can be used to register the process, publish heartbeat and update application health status
		//! \param responseHandler	You must provide an implementation of this.  Your implementation of the smf::SCtrlAppStatusResponseHandlerExt2 interface.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt2 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt2 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt2.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt2* OpenAppStatusRequestChannelExt2(
				SCtrlAppStatusResponseHandlerExt2* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);
#endif

		//! \brief You should call this function to close a smf::SCtrlServiceRequestHandler once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this SCtrlServiceRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenSCtrlRequestChannel.
		//!								A request handler  created using the smf::SCtrlService::OpenRequestChannel function.
		//!	\remark						Include: SCtrlService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				SCtrlServiceRequestHandler* requestHandler
				);

		//! \brief You should call this function to close a smf::SCtrlAppStatusRequestHandler once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenAppStatusRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this SCtrlAppStatusRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenSCtrlAppStatusRequestChannel.
		//!								A request handler  created using the smf::SCtrlService::OpenAppStatusRequestChannel function.
		//!	\remark						Include: SCtrlService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseAppStatusRequestChannel(
				ServiceChannel* channel, 
				SCtrlAppStatusRequestHandler* requestHandler
				);

		//! \brief You should call this function to close a smf::SCtrlAppStatusRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenAppStatusRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this SCtrlAppStatusRequestHandlerExt1. 
		//! \param requestHandler		The request handler returned from OpenSCtrlAppStatusRequestChannel.
		//!								A request handler  created using the smf::SCtrlService::OpenAppStatusRequestChannelExt1 function.
		//!	\remark						Include: SCtrlService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseAppStatusRequestChannelExt1(
				ServiceChannel* channel, 
				SCtrlAppStatusRequestHandlerExt1* requestHandler
				);

#ifdef WIN32
		//! \brief You should call this function to close a smf::SCtrlAppStatusRequestHandlerExt2 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenAppStatusRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this SCtrlAppStatusRequestHandlerExt2. 
		//! \param requestHandler		The request handler returned from OpenSCtrlAppStatusRequestChannel.
		//!								A request handler  created using the smf::SCtrlService::OpenAppStatusRequestChannelExt2 function.
		//!	\remark						Include: SCtrlService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseAppStatusRequestChannelExt2(
				ServiceChannel* channel, 
				SCtrlAppStatusRequestHandlerExt2* requestHandler
				);

		//! \brief You can call this to create an object of smf::SCtrlAppStatusResourcePool, which provide 
		//         shared resources for multiple Sctrl App Status Service. By using smf::SCtrlAppStatusResourcePool, multiple
		//         Log Service will share the threads and buffers in the resource pool. You should only use
		//         smf::SCtrlAppStatusResourcePool if you need to create large amount of Sctrl App Status Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::SCtrlAppStatusResourcePool* CreateSCtrlAppStatusResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroySCtrlAppStatusResourcePool(smf::ServiceBufferPool* bufferPool, smf::SCtrlAppStatusResourcePool* resPool);

		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt2 which can be used to register the process, publish heartbeat and update application health status
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt2 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt2 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt2.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt2* OpenAppStatusRequestChannelExt2(
				smf::SCtrlAppStatusResourcePool* resPool,
				ServiceChannel* channel,  
				Logger* logger );

		//! \brief This function will create a SCtrlAppStatusRequestHandlerExt2 which can be used to register the process, publish heartbeat and update application health status
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param responseHandler	You must provide an implementation of this.  Your implementation of the smf::SCtrlAppStatusResponseHandlerExt2 interface.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return					A pointer to a Smf::SCtrlAppStatusRequestHandlerExt2 object.
		//!	\remark					Include: SCtrlService.h, SCtrlAppStatusRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseAppStatusRequestChannelExt2 to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlAppStatusRequestHandlerExt2.h.
		//! \note					This function is thread safe. 
		SCtrlAppStatusRequestHandlerExt2* OpenAppStatusRequestChannelExt2(
				smf::SCtrlAppStatusResourcePool* resPool,
				SCtrlAppStatusResponseHandlerExt2* responseHandler,
				ServiceChannel* channel,  
				Logger* logger
				);
        

		//! \brief You can call this to create an object of smf::SCtrlServiceResourcePool, which provide 
		//         shared resources for multiple SCtrl Service. By using smf::SCtrlServiceResourcePool, multiple
		//         SCtrl Service will share the threads and buffers in the resource pool. You should only use
		//         smf::SCtrlServiceResourcePool if you need to create large amount of SCtrl Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::SCtrlServiceResourcePool* CreateSCtrlServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroySCtrlServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::SCtrlServiceResourcePool* resPool);

		//! \brief This function will create a SCtrlServiceRequestHandler which can be used to create schedule, query schedule task and process status, and modify schedule from the SMF server.
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::SCtrlServiceResponseHandler interface.
		//!							See the samples/SCtrlService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return					A pointer to a Smf::SCtrlServiceRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlServiceRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlServiceRequestHandler* OpenRequestChannel(
				smf::SCtrlServiceResourcePool* resPool,
				SCtrlServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger
				);

		//! \brief This function will create a SCtrlServiceRequestHandlerExt1 which can be used to create schedule, query schedule task and process status, and modify schedule from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::SCtrlServiceResponseHandler interface.
		//!							See the samples/SCtrlService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::SCtrlServiceRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlServiceRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlServiceRequestHandlerExt1* OpenRequestChannelExt1(
				SCtrlServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 // the default queue size will be used
				);

		//! \brief This function will create a SCtrlServiceRequestHandlerExt1 which can be used to create schedule, query schedule task and process status, and modify schedule from the SMF server.
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::SCtrlServiceResponseHandler interface.
		//!							See the samples/SCtrlService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return					A pointer to a Smf::SCtrlServiceRequestHandler object.
		//!	\remark					Include: SCtrlService.h, SCtrlServiceRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::SCtrlService::CloseRequestChannel to cleanup.
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in SCtrlServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		SCtrlServiceRequestHandlerExt1* OpenRequestChannelExt1(
				smf::SCtrlServiceResourcePool* resPool,
				SCtrlServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger
				);

		//! \brief You should call this function to close a smf::SCtrlServiceRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this SCtrlServiceRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenSCtrlRequestChannelExt1.
		//!								A request handler  created using the smf::SCtrlService::OpenRequestChannelExt1 function.
		//!	\remark						Include: SCtrlService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannelExt1(
				ServiceChannel* channel, 
				SCtrlServiceRequestHandlerExt1* requestHandler
				);
#endif

		unsigned int SetServiceInternalArraySize(unsigned int);
		unsigned int SetAppStatusInternalArraySize(unsigned int);

		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);
	}
}
#endif
