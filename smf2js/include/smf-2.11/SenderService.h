
#ifndef SENDERSERVICE_H
#define SENDERSERVICE_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class RequestServiceRequestHandler;
    class RequestServiceRequestHandlerExt1;
	class RequestServiceResponseHandler;
    class RequestServiceResponseHandlerExt1;
	class RequestServiceResourcePool;
	class ServiceBufferPool;

	namespace SenderService{
		const char* LibName();

		//! \brief Opens a channel to the Sender service which can send arbitrary request messages to 
		//!	a receiver and receive response from it
		//! \param responseHandler	You must provide an implementation of this
		//! \param channel			Use smf::Client::Connect to get this
		//! \param logger           Can be 0, your own implementation of an smf::Logger or
		//!							a file logger (use smf::fileLogger function)
		//! \param queueSize		The default queue size will be used
		RequestServiceRequestHandler* OpenRequestChannel(
				RequestServiceResponseHandler* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief Opens a channel to the Sender service which can send arbitrary request messages to 
		//!	a receiver and receive response from it
		//! \param responseHandler	You must provide an implementation of this
		//! \param channel			Use smf::Client::Connect to get this
		//! \param logger           Can be 0, your own implementation of an smf::Logger or
		//!							a file logger (use smf::fileLogger function)
		//! \param queueSize		The default queue size will be used
		RequestServiceRequestHandlerExt1* OpenRequestChannelExt1(
				RequestServiceResponseHandlerExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief It closes the request channel
		//! \param channel           The same service channel that was passed in to OpenRequestChannel
		//! \param requestHandler	 The request handler returned from OpenRequestChannel
		void CloseRequestChannel(
				ServiceChannel* channel, 
				RequestServiceRequestHandler* requestHandler
				);

        //! \brief It closes the request channel
		//! \param channel           The same service channel that was passed in to OpenRequestChannel
		//! \param requestHandler	 The request handler returned from OpenRequestChannel
		void CloseRequestChannel(
				ServiceChannel* channel, 
				RequestServiceRequestHandlerExt1* requestHandler
				);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::RequestServiceResourcePool, which provide 
		//         shared resources for multiple Sender Service. By using smf::RequestServiceResourcePool, multiple
		//         Sender Service will share the threads and buffers in the resource pool. You should only use
		//         smf::RequestServiceResourcePool if you need to create large amount of Sender Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::RequestServiceResourcePool* CreateServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::RequestServiceResourcePool* resPool);

		//! \brief Opens a channel to the Sender service which can send arbitrary request messages to 
		//!	a receiver and receive response from it
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param responseHandler	You must provide an implementation of this
		//! \param channel			Use smf::Client::Connect to get this
		//! \param logger           Can be 0, your own implementation of an smf::Logger or
		//!							a file logger (use smf::fileLogger function)
		RequestServiceRequestHandler* OpenRequestChannel(
				smf::RequestServiceResourcePool* resPool,
				smf::RequestServiceResponseHandler *responseHandler,
				smf::ServiceChannel *channel,
				smf::Logger *logger);

		//! \brief Opens a channel to the Sender service which can send arbitrary request messages to 
		//!	a receiver and receive response from it
		//! \param resPool			Create via CreateServiceResourcePool
		//! \param responseHandler	You must provide an implementation of this
		//! \param channel			Use smf::Client::Connect to get this
		//! \param logger           Can be 0, your own implementation of an smf::Logger or
		//!							a file logger (use smf::fileLogger function)
		RequestServiceRequestHandlerExt1* OpenRequestChannelExt1(
				smf::RequestServiceResourcePool* resPool,
				smf::RequestServiceResponseHandlerExt1 *responseHandler,
				smf::ServiceChannel *channel,
				smf::Logger *logger);
#endif
        unsigned int SetChannelLimit(unsigned int limit);

		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);
	}
}
#endif