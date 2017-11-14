
#ifndef RECEIVERSERVICE_H
#define RECEIVERSERVICE_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class RequestServiceTransmitter;
    class RequestServiceTransmitterExt1;
	class RequestServiceReceiver;
    class RequestServiceReceiverExt1;
	class RequestServiceResourcePool;
	class ServiceBufferPool;

	namespace ReceiverService{
		const char* LibName();

		//! \brief Opens a channel to the Receiver service which can receive arbitrary request messages  
		//! through your implementation of request service handler
		//! \param responseHandler      You must provide an implementation of this
		//! \param channel              Use smf::Client::Connect to get this
		//! \param logger               Can be 0, your own implementation of an smf::Logger or
		//!								a file logger (use smf::fileLogger function)
		//! \param queueSize			The default queue size will be used
		RequestServiceTransmitter* OpenRequestChannel(
				RequestServiceReceiver* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

        //! \brief Opens a channel to the Receiver service which can receive arbitrary request messages  
		//! through your implementation of request service handler
		//! \param responseHandler      You must provide an implementation of this
		//! \param channel              Use smf::Client::Connect to get this
		//! \param logger               Can be 0, your own implementation of an smf::Logger or
		//!								a file logger (use smf::fileLogger function)
		//! \param queueSize			The default queue size will be used
		RequestServiceTransmitterExt1* OpenRequestChannelExt1(
				RequestServiceReceiverExt1* responseHandler,
				ServiceChannel* channel,  
				Logger* logger, 
				unsigned int queueSize = 0 //the default queue size will be used
				);

		//! \brief It closes the request chnanel
		//! \param channel            The same service channel that was passed in to OpenRequestChannel
		//! \param requestHandler     The request handler returned from OpenRequestChannel
		void CloseRequestChannel(
				ServiceChannel* channel, 
				RequestServiceTransmitter* requestHandler
				);

        		//! \brief It closes the request chnanel
		//! \param channel            The same service channel that was passed in to OpenRequestChannel
		//! \param requestHandler     The request handler returned from OpenRequestChannel
		void CloseRequestChannelExt1(
				ServiceChannel* channel, 
				RequestServiceTransmitterExt1* requestHandler
				);

#ifdef WIN32
		//! \brief You can call this to create an object of smf::RequestServiceResourcePool, which provide 
		//         shared resources for multiple Request Service. By using smf::RequestServiceResourcePool, multiple
		//         Request Service will share the threads and buffers in the resource pool. You should only use
		//         smf::RequestServiceResourcePool if you need to create large amount of Request Service.
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

		//! \brief Opens a channel to the Receiver service which can receive arbitrary request messages  
		//! through your implementation of request service handler
		//! \param resPool				Create via CreateServiceResourcePool
		//! \param responseHandler      You must provide an implementation of this
		//! \param channel              Use smf::Client::Connect to get this
		//! \param logger               Can be 0, your own implementation of an smf::Logger or
		//!								a file logger (use smf::fileLogger function)
		RequestServiceTransmitter* OpenRequestChannel(
				smf::RequestServiceResourcePool* resPool,
				smf::RequestServiceReceiver *responseHandler,
				smf::ServiceChannel *channel,
				smf::Logger *logger);

        
		//! \brief Opens a channel to the Receiver service which can receive arbitrary request messages  
		//! through your implementation of request service handler
		//! \param resPool				Create via CreateServiceResourcePool
		//! \param responseHandler      You must provide an implementation of this
		//! \param channel              Use smf::Client::Connect to get this
		//! \param logger               Can be 0, your own implementation of an smf::Logger or
		//!								a file logger (use smf::fileLogger function)
		RequestServiceTransmitterExt1* OpenRequestChannelExt1(
				smf::RequestServiceResourcePool* resPool,
				smf::RequestServiceReceiverExt1 *responseHandler,
				smf::ServiceChannel *channel,
				smf::Logger *logger);
#endif

        unsigned int SetChannelLimit(unsigned int limit);

		void SetQueueSleep(unsigned int);
	}
}
#endif
