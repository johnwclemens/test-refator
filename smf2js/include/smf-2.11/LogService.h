
#ifndef LOGSERVICEENTRYPOINTS_H
#define LOGSERVICEENTRYPOINTS_H


namespace smf{
	class Logger;
	class ServiceChannel;
	class LogServiceRequestHandler;
	class LogServiceRequestHandlerExt1;
	class LogServiceResponseHandler;
	class EventLogManagement;
	class LogServiceResourcePool;
	class ServiceBufferPool;
	
	namespace LogService{
		

		const char* LibName();

		//! \brief This function will create a LogServiceRequestHandler which can be used to send logs to the SMF server. 
		//!           It opens a channel to the Log service which can send and receive log messages to and from the SMF server
		//! \param responseHandler				You must provide an implementation of this. 
		//!										See the sample log application(located in the samples\Log_Service directory of the SMF-SDK) for an example of this
		//! \param channel						Use smf::Client::Connect to get this.  The ServiceChannel returned from the call to smf::Client::Connect.  See Opening An SMF Service Channel
		//! \param logger						can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function)
		//!										A local file logger return from a call to smf::InternalLogger. See Opening a Logger.  
		//!  									Note: you do not have to use the smf implementation; you may provide your own implementation of the Logger interface instead
		//! \param messageFilename				Currently this must be set to null, by default only free text msgs
		//! \param queueSize					The internal queue size for handling responses (in number of items).  If this is zero, the default value of 10 items will be used.
		//! \return 							A pointer to a smf::LogServiceRequestHandler object
		//! \remark 							Include: LogService.h, LogServiceRequestHandler.h, Logger.h
		//! \post 								Cleanup: You must call smf::LogService::CloseRequestChannel to cleanup (see Closing a Log Service Request Handler)
		//! \exception smf::Error				Specific exceptions that might be thrown are defined in LogServiceRequestHandler.h
		//! \note							This function is thread safe
		//! \see 							Sending and Receiving Log Messages
		LogServiceRequestHandler *OpenRequestChannel(
									smf::LogServiceResponseHandler *responseHandler,
									smf::ServiceChannel *channel,  // 
									smf::Logger *logger,					
									const char *messageFilename = 0,//by default only free text msgs
									unsigned int queueSize = 0);//default queue size will be used 

		//! \brief You should call this to close a smf::LogServiceRequestHandler once you have finished with it
		//! \param channel					The same service channel that was passed in to OpenRequestChannel
		//! \param requestHandler			The request handler returned from OpenRequestChannel
		//! \remark 						Include: LogService.h, Error.h
		//! \exception smf::Error			Specific exceptions that might be thrown are defined in LogServiceRequestHandler.h
		//! \note							This function is thread safe
		void CloseRequestChannel(	smf::ServiceChannel *channel, 
									smf::LogServiceRequestHandler *requestHandler);

		//! \brief This function will create a LogServiceRequestHandlerExt1 which can be used to send logs to the SMF server. 
		//!           It opens a channel to the Log service which can send and receive log messages to and from the SMF server
		//! \param responseHandler				You must provide an implementation of this. 
		//!										See the sample log application(located in the samples\Log_Service directory of the SMF-SDK) for an example of this
		//! \param channel						Use smf::Client::Connect to get this.  The ServiceChannel returned from the call to smf::Client::Connect.  See Opening An SMF Service Channel
		//! \param logger						can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function)
		//!										A local file logger return from a call to smf::InternalLogger. See Opening a Logger.  
		//!  									Note: you do not have to use the smf implementation; you may provide your own implementation of the Logger interface instead
		//! \param messageFilename				Currently this must be set to null, by default only free text msgs
		//! \param queueSize					The internal queue size for handling responses (in number of items).  If this is zero, the default value of 10 items will be used.
		//! \return 							A pointer to a smf::LogServiceRequestHandler object
		//! \remark 							Include: LogService.h, LogServiceRequestHandlerExt1.h, Logger.h
		//! \post 								Cleanup: You must call smf::LogService::CloseRequestChannelExt1 to cleanup (see Closing a Log Service Request Handler)
		//! \exception smf::Error				Specific exceptions that might be thrown are defined in LogServiceRequestHandlerExt1.h
		//! \note							This function is thread safe
		//! \see 							Sending and Receiving Log Messages
		LogServiceRequestHandlerExt1 *OpenRequestChannelExt1(
									smf::LogServiceResponseHandler *responseHandler,
									smf::ServiceChannel *channel,  // 
									smf::Logger *logger,					
									const char *messageFilename = 0,//by default only free text msgs
									unsigned int queueSize = 0);//default queue size will be used 

		//! \brief You should call this to close a smf::LogServiceRequestHandlerExt1 once you have finished with it
		//! \param channel					The same service channel that was passed in to OpenRequestChannelExt1
		//! \param requestHandler			The request handler returned from OpenRequestChannelExt1
		//! \remark 						Include: LogService.h, Error.h
		//! \exception smf::Error			Specific exceptions that might be thrown are defined in LogServiceRequestHandlerExt1.h
		//! \note							This function is thread safe
		void CloseRequestChannelExt1(	smf::ServiceChannel *channel, 
									smf::LogServiceRequestHandlerExt1 *requestHandler);


		//! \brief This function will create a EventLogManagement object which can be used to perform event log management in the SMF server. 
		//!           It opens a channel to the Event Log Management object which can manage event log message in the SMF server
		//! \param channel						Use smf::Client::Connect to get this.  The ServiceChannel returned from the call to smf::Client::Connect.  See Opening An SMF Service Channel
		//! \param logger						can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function)
		//!										A local file logger return from a call to smf::InternalLogger. See Opening a Logger.  
		//!  									Note: you do not have to use the smf implementation; you may provide your own implementation of the Logger interface instead
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size will be used.
		//! \return 							A pointer to a smf::EventLogManagement object
		//! \remark 							Include: LogService.h, EventLogManagement.h, Logger.h
		//! \post 								Cleanup: You must call smf::LogService::CloseEventLogManagement to cleanup (see Closing a Event Log Management)
		//! \exception smf::Error			Specific exceptions that might be thrown are defined in EventLogManagement.h
		//! \note							This function is thread safe
		//! \see 							Sending and Receiving Log Messages
		EventLogManagement *OpenEventLogManagement(
									smf::ServiceChannel *channel, 
									smf::Logger *logger,
									unsigned int queueSize = 0 // the default queue size will be used);
									);

		//! \brief You should call this function to close a smf::EventLogManagement object once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenEventLogManagement.
		//!								The smf::ServiceChannel pointer used when opening this EventLogManagement. 
		//! \param eventLogManagement		The event log management object returned from OpenEventLogManagement.
		//!								A event log management created using the smf::LogService::OpenEventLogManagement function.
		//!	\remark						Include: LogService.h	
		//! \note							This function is thread safe
		void CloseEventLogManagement(
				ServiceChannel* channel,
				EventLogManagement* eventLogManagement);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::LogServiceResourcePool, which provide 
		//         shared resources for multiple Log Service. By using smf::LogServiceResourcePool, multiple
		//         Log Service will share the threads and buffers in the resource pool. You should only use
		//         smf::LogServiceResourcePool if you need to create large amount of Log Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::LogServiceResourcePool* CreateServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::LogServiceResourcePool* resPool);

		//! \brief This function will create a LogServiceRequestHandlerExt1 which can be used to send logs to the SMF server. 
		//!           It opens a channel to the Log service which can send and receive log messages to and from the SMF server
		//! \param resPool						Create via CreateServiceResourcePool
		//! \param responseHandler				You must provide an implementation of this. 
		//!										See the sample log application(located in the samples\Log_Service directory of the SMF-SDK) for an example of this
		//! \param channel						Use smf::Client::Connect to get this.  The ServiceChannel returned from the call to smf::Client::Connect.  See Opening An SMF Service Channel
		//! \param logger						can be 0, your own implementation of an smf::Logger or a file logger (use smf::fileLogger function)
		//!										A local file logger return from a call to smf::InternalLogger. See Opening a Logger.  
		//!  									Note: you do not have to use the smf implementation; you may provide your own implementation of the Logger interface instead
		//! \param messageFilename				Currently this must be set to null, by default only free text msgs
		//! \return 							A pointer to a smf::LogServiceRequestHandler object
		//! \remark 							Include: LogService.h, LogServiceRequestHandlerExt1.h, Logger.h
		//! \post 								Cleanup: You must call smf::LogService::CloseRequestChannelExt1 to cleanup (see Closing a Log Service Request Handler)
		//! \exception smf::Error				Specific exceptions that might be thrown are defined in LogServiceRequestHandlerExt1.h
		//! \note							This function is thread safe
		//! \see 							Sending and Receiving Log Messages
		LogServiceRequestHandlerExt1 *OpenRequestChannelExt1(
				smf::LogServiceResourcePool* resPool,
				smf::LogServiceResponseHandler *responseHandler,
				smf::ServiceChannel *channel, 
				smf::Logger *logger,					
				const char *messageFilename = 0);//by default only free text msgs
#endif

		unsigned int SetChannelLimit(unsigned int limit);

		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);
	}
}
#endif