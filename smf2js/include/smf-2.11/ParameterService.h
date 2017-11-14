
#ifndef PARAMETERSERVICEENTRYPOINTS_H
#define PARAMETERSERVICEENTRYPOINTS_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class ParameterServiceResourcePool;
	class ServiceBufferPool;
	class ParameterServiceRequestHandler;
	class ParameterServiceResponseHandler;
	class ParameterServiceRequestHandlerExt1;
	class ParameterServiceResponseHandlerExt1;
    class ParameterServiceRequestHandlerExt2;
    class ParameterServiceRequestHandlerExt3;
    class ParameterServiceResponseHandlerExt2;
	class ParameterServiceRequestHandlerExt4;
    class ParameterServiceResponseHandlerExt3;

	namespace ParameterService{
		

		const char* LibName();
		
		
		//! \brief This function will create a ParameterServiceRequestHandler which can be used to query and update parameter values from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ParameterServiceResponseHandler interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandler object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandler* OpenRequestChannel(
				ParameterServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger , 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief This function will create a ParameterServiceRequestHandlerExt1 which can be used to query and update parameter values from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ResizableParameterServiceResponseHandler interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt1 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt1.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt1* OpenRequestChannel(
				ParameterServiceResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger , 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief This function will create a ParameterServiceRequestHandlerExt2 which can be used to query (transactional or non-transactional) and update parameter values from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ResizableParameterServiceResponseHandler interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt1 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt2.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt2* OpenRequestChannelExt2(
				ParameterServiceResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger , 
				unsigned int queueSize = 0 //the default queue size will be used
				);


		//! \brief This function will create a ParameterServiceRequestHandlerExt3 which can be used for parameter subscription from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ParameterServiceResponseHandlerExt2 interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt1 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt3.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt3.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt3* OpenRequestChannelExt3(
				ParameterServiceResponseHandlerExt2* responseHandler,
				ServiceChannel* channel,  
				Logger* logger , 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief This function will create a ParameterServiceRequestHandlerExt4 which can be used for dynamic load/unload partition from the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ParameterServiceResponseHandlerExt3 interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt4 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt3.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt3.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt4* OpenRequestChannelExt4(
				ParameterServiceResponseHandlerExt3* responseHandler,
				ServiceChannel* channel,  
				Logger* logger , 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief You should call this function to close a smf::ParameterServiceRequestHandler once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this ParameterServiceRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::ParameterService::OpenRequestChannel function.
		//!	\remark						Include: ParameterService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				ParameterServiceRequestHandler* requestHandler
				);

		//! \brief You should call this function to close a smf::ParameterServiceRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this ParameterServiceRequestHandlerExt1. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::ParameterService::OpenRequestChannel function.
		//!	\remark						Include: ParameterService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				ParameterServiceRequestHandlerExt1* requestHandler
				);

		//! \brief You should call this function to close a smf::ParameterServiceRequestHandlerExt2 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this ParameterServiceRequestHandlerExt2. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::ParameterService::OpenRequestChannel function.
		//!	\remark						Include: ParameterService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				ParameterServiceRequestHandlerExt2* requestHandler
				);

		//! \brief You should call this function to close a smf::ParameterServiceRequestHandlerExt3 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this ParameterServiceRequestHandlerExt3. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::ParameterService::OpenRequestChannel function.
		//!	\remark						Include: ParameterService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				ParameterServiceRequestHandlerExt3* requestHandler
				);

		//! \brief You should call this function to close a smf::ParameterServiceRequestHandlerExt4 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this ParameterServiceRequestHandlerExt4. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler  created using the smf::ParameterService::OpenRequestChannel function.
		//!	\remark						Include: ParameterService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
				ServiceChannel* channel, 
				ParameterServiceRequestHandlerExt4* requestHandler
				);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::ParameterServiceResourcePool, which provide 
		//         shared resources for multiple Parameter Service. By using smf::ParameterServiceResourcePool, multiple
		//         Parameter Service will share the threads and buffers in the resource pool. You should only use
		//         smf::ParameterServiceResourcePool if you need to create large amount of Parameter Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::ParameterServiceResourcePool* CreateServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::ParameterServiceResourcePool* resPool);

		//! \brief This function will create a ParameterServiceRequestHandlerExt3 which can be used for parameter subscription from the SMF server.
		//! \param resPool		    Create via CreateServiceResourcePool
		//! \param responseHandler  You must provide an implementation of this.  Your implementation of the smf::ParameterServiceResponseHandlerExt2 interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt1 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt3.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt3.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt3* OpenRequestChannelExt3(
				smf::ParameterServiceResourcePool* resPool,
				ParameterServiceResponseHandlerExt2* responseHandler,
				ServiceChannel* channel,  
				Logger* logger
				);

		//! \brief This function will create a ParameterServiceRequestHandlerExt4 which can be used for dynamic load/unload partition from the SMF server.
		//! \param resPool		    Create via CreateServiceResourcePool
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::ParameterServiceResponseHandlerExt3 interface.
		//!							See the samples/PsdService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \return					A pointer to a Smf::ParameterServiceRequestHandlerExt4 object.
		//!	\remark					Include: ParameterService.h, ParameterServiceRequestHandlerExt3.h, Logger.h.
		//!	\post					Cleanup: You must call smf::ParameterService::CloseRequestChannel to cleanup (see Closing a Parameter Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in ParameterServiceRequestHandlerExt3.h.
		//! \note					This function is thread safe. 
		ParameterServiceRequestHandlerExt4* OpenRequestChannelExt4(
				smf::ParameterServiceResourcePool* resPool,
				ParameterServiceResponseHandlerExt3* responseHandler,
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