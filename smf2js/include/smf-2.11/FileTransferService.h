#ifndef FILETRANSFERSERVICE_H
#define FILETRANSFERSERVICE_H

namespace smf{
	class Logger;
	class ServiceChannel;
	class FileTransferServiceRequestHandler;
#ifdef WIN32
	class FileTransferServiceRequestHandlerExt1;
    class FileTransferServiceRequestHandlerExt2;
    class FileTransferProgress;
#endif
	class FileTransferServiceResponseHandler;
	class FileTransferServiceResourcePool;
	class ServiceBufferPool;
	
	namespace FileTransferService {
	
#ifdef WIN32
		enum FtrPerformanceMode
		{
			CPUSaving = 0,
			HighPerformance
		};
#endif

		const char* LibName();
		
		//! \brief This function will create a FileTransferServiceRequestHandler which can be used to get/put files from/to the SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::FileTransferServiceResponseHandler interface.
		//!							See the samples/FileTransferService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size of 10 will be used.
		//! \param chunkSize		The chunk size that the file will be chopped to before uploading or downloading.
		//!							If you pass zero here the default chunk size of 5K will be used.
		//! \param tempDir			The temporary directory that the file chunks will be stored in. 
		//!                         If you pass empty string here the system default temporary directory will be used.		
		//! \return					A pointer to a Smf::FileTransferServiceRequestHandler object.
		//!	\remark					Include: FileTransferService.h, FileTransferServiceRequestHandler.h, Logger.h.
		//!	\post					Cleanup: You must call smf::FileTransferService::CloseRequestChannel to cleanup (see Closing a File Transfer Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
		//! \note					This function is thread safe. CPUSaving mode will be automatically applied if you call this function.
		FileTransferServiceRequestHandler* OpenRequestChannel(
			FileTransferServiceResponseHandler* responseHandler,
			ServiceChannel* channel,
			Logger* logger,
			unsigned int queueSize = 0,
			unsigned int chunkSize = 0,
			const char* tempDir = ""
			);

#ifdef WIN32
		//! \brief This function will create a FileTransferServiceRequestHandlerExt1 which can be used to get/put files from/to the SMF server and put memory segments into SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::FileTransferServiceResponseHandler interface.
		//!							See the samples/FileTransferService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size of 10 will be used.
		//! \param chunkSize		The chunk size that the file will be chopped to before uploading or downloading.
		//!							If you pass zero here the default chunk size of 5K will be used.
		//! \param tempDir			The temporary directory that the file chunks will be stored in. You can ignore this parameter if the handler are only used for memory transfer.
		//!                         If you pass empty string here the system default temporary directory will be used.
		//! \param performanceMode  This controls the performance of the transfer with respect to the CPU consumption. 
		//!							If it is set to "CPUSaving", the CPU consumption is lower but transaction is slower 
		//!							If it is set to "HighPerformance", the transaction is faster but CPU consumption is higher
		//!                         By default, CPU saving mode is applied.
		//! \return					A pointer to a Smf::FileTransferServiceRequestHandlerExt1 object.
		//!	\remark					Include: FileTransferService.h, FileTransferServiceRequestHandlerExt1.h, Logger.h.
		//!	\post					Cleanup: You must call smf::FileTransferService::CloseRequestChannelExt1 to cleanup (see Closing a File Transfer Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		FileTransferServiceRequestHandlerExt1* OpenRequestChannelExt1(
			FileTransferServiceResponseHandler* responseHandler,
			ServiceChannel* channel,
			Logger* logger,
			unsigned int queueSize = 0,
			unsigned int chunkSize = 0,
			const char* tempDir = "", 
			FtrPerformanceMode performanceMode = FtrPerformanceMode::CPUSaving
            );

		//! \brief This function will create a FileTransferServiceRequestHandlerExt2 which can be used to get/put files from/to the SMF server and put memory segments into SMF server.
		//! \param responseHandler You must provide an implementation of this.  Your implementation of the smf::FileTransferServiceResponseHandler interface.
		//!							See the samples/FileTransferService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param queueSize		The internal queue size for handling responses.
		//!							If you pass zero here the default queue size of 10 will be used.
		//! \param chunkSize		The chunk size that the file will be chopped to before uploading or downloading.
		//!							If you pass zero here the default chunk size of 5K will be used.
		//! \param tempDir			The temporary directory that the file chunks will be stored in. You can ignore this parameter if the handler are only used for memory transfer.
		//!                         If you pass empty string here the system default temporary directory will be used.
		//! \param performanceMode  This controls the performance of the transfer with respect to the CPU consumption. 
		//!							If it is set to "CPUSaving", the CPU consumption is lower but transaction is slower 
		//!							If it is set to "HighPerformance", the transaction is faster but CPU consumption is higher
		//!                         By default, CPU saving mode is applied.
		//! \return					A pointer to a Smf::FileTransferServiceRequestHandlerExt2 object.
		//!	\remark					Include: FileTransferService.h, FileTransferServiceRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::FileTransferService::CloseRequestChannelExt2 to cleanup (see Closing a File Transfer Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		FileTransferServiceRequestHandlerExt2* OpenRequestChannelExt2(
			FileTransferServiceResponseHandler* responseHandler,
			ServiceChannel* channel,
			Logger* logger,
			unsigned int queueSize = 0,
			unsigned int chunkSize = 0,
			const char* tempDir = "", 
			FtrPerformanceMode performanceMode = FtrPerformanceMode::CPUSaving
			);

        //! \brief                  This function will create a FileTransferProgress which can be used on RequestGetFile call via the Smf::FileTransferServiceRequestHandlerExt2 object.
        //! \param logger           Can be 0, your own implementation of an smf::Logger or a file logger.
        //! \return                 A pointer to a Smf::FileTransferProgress object.
        //! \remark                 Include: FileTransferService.h, FileTransferServiceRequestHandlerExt2.h, Logger.h.
        //! \post                   Cleanup: You must call smf::FileTransferService::DestroyFileTransferProgress to cleanup
        //! \exception              You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
        //! \note                   This function is thread safe
        smf::FileTransferProgress* CreateFileTransferProgress(
            Logger* logger
            );
#endif

		//! \brief You should call this function to close a smf::FileTransferServiceRequestHandler once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannel.
		//!								The smf::ServiceChannel pointer used when opening this FileTransferServiceRequestHandler. 
		//! \param requestHandler		The request handler returned from OpenRequestChannel.
		//!								A request handler created using the smf::FileTransferService::OpenRequestChannel function.
		//!	\remark						Include: FileTransferService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannel(
			ServiceChannel* channel,
			FileTransferServiceRequestHandler* requestHandler
			);
		
#ifdef WIN32
		//! \brief You should call this function to close a smf::FileTransferServiceRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannelExt1.
		//!								The smf::ServiceChannel pointer used when opening this FileTransferServiceRequestHandlerExt1. 
		//! \param requestHandler		The request handler returned from OpenRequestChannelExt1.
		//!								A request handler created using the smf::FileTransferService::OpenRequestChannelExt1 function.
		//!	\remark						Include: FileTransferService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannelExt1(
			ServiceChannel* channel,
			FileTransferServiceRequestHandlerExt1* requestHandler
			);

		//! \brief You should call this function to close a smf::FileTransferServiceRequestHandlerExt1 once you have finished with it.
		//! \param channel				The same service channel that was passed in to OpenRequestChannelExt2.
		//!								The smf::ServiceChannel pointer used when opening this FileTransferServiceRequestHandlerExt2. 
		//! \param requestHandler		The request handler returned from OpenRequestChannelExt2.
		//!								A request handler created using the smf::FileTransferService::OpenRequestChannelExt2 function.
		//!	\remark						Include: FileTransferService.h
		//!	\exception smf::Error
		//! \note						function is thread safe.
		void CloseRequestChannelExt2(
			ServiceChannel* channel,
			FileTransferServiceRequestHandlerExt2* requestHandler
			);

        //! \brief                      You should call this function to destroy a smf::FileTransferProgress object once you have finished with it.
        //! \param progress             Pointer to smf::FileTransferProgress object you would like to destroy        
        //! \remark                     Include: FileTransferService.h        
        //! \exception                  You should at least handle smf::Error
        //! \note                       This function is thread safe
        void DestroyFileTransferProgress(smf::FileTransferProgress*
            progress);

		//! \brief You can call this to create an object of smf::FileTransferServiceResourcePool, which provide 
		//         shared resources for multiple File Tranfer Service. By using smf::FileTransferServiceResourcePool, multiple
		//         File Tranfer Service will share the threads and buffers in the resource pool. You should only use
		//         smf::FileTransferServiceResourcePool if you need to create large amount of File Transfer Service.
		//! \param bufferPool created via CreateServiceBufferPool in SmfClient.h
		//! \param logger can be 0, your own implementation of an smf::Logger or an smf file logger (use smf::fileLogger)
		//! \param numProcessThreadAndQueue The number of threads to process the messages and number of input queues
		//                  If 0, default number is used.
		//! \param queueSize The size of each input queue
		//                  If 0, default number is used.
		//! \remark Include: SmfClient.h, Logger.h
		//! \note This function is thread safe.
		smf::FileTransferServiceResourcePool* CreateServiceResourcePool(
				smf::ServiceBufferPool* bufferPool,
				smf::Logger* logger,
				unsigned int numProcessThreadAndQueue = 0,
				unsigned int queueSize = 0);

		void DestroyServiceResourcePool(smf::ServiceBufferPool* bufferPool, smf::FileTransferServiceResourcePool* resPool);

		//! \brief This function will create a FileTransferServiceRequestHandlerExt1 which can be used to get/put files from/to the SMF server and put memory segments into SMF server.
        //! \param resPool          Provide the pointer of your smf::FileTransferServiceResourcePool pointer here
		//! \param responseHandler  You must provide an implementation of this.  Your implementation of the smf::FileTransferServiceResponseHandler interface.
		//!							See the samples/FileTransferService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param chunkSize		The chunk size that the file will be chopped to before uploading or downloading.
		//!							If you pass zero here the default chunk size of 5K will be used.
		//! \param tempDir			The temporary directory that the file chunks will be stored in. You can ignore this parameter if the handler are only used for memory transfer.
		//!                         If you pass empty string here the system default temporary directory will be used.
		//! \param performanceMode  This controls the performance of the transfer with respect to the CPU consumption. 
		//!							If it is set to "CPUSaving", the CPU consumption is lower but transaction is slower 
		//!							If it is set to "HighPerformance", the transaction is faster but CPU consumption is higher
		//!                         By default, CPU saving mode is applied.
		//! \return					A pointer to a Smf::FileTransferServiceRequestHandlerExt2 object.
		//!	\remark					Include: FileTransferService.h, FileTransferServiceRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::FileTransferService::CloseRequestChannelExt2 to cleanup (see Closing a File Transfer Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		FileTransferServiceRequestHandlerExt1* OpenRequestChannelExt1(
			smf::FileTransferServiceResourcePool* resPool,
			FileTransferServiceResponseHandler* responseHandler,
			ServiceChannel* channel,
			Logger* logger,
			unsigned int chunkSize = 0,
			const char* tempDir = "", 
			FtrPerformanceMode performanceMode = FtrPerformanceMode::CPUSaving
			);

		//! \brief This function will create a FileTransferServiceRequestHandlerExt2 which can be used to get/put files from/to the SMF server and put memory segments into SMF server.
        //! \param resPool          Provide the pointer of your smf::FileTransferServiceResourcePool pointer here
		//! \param responseHandler  You must provide an implementation of this.  Your implementation of the smf::FileTransferServiceResponseHandler interface.
		//!							See the samples/FileTransferService directory in the SMF-SDK for an example implementation.
		//! \param channel			Use smf::Client::Connect to get this
		//!							The ServiceChannel returned from the call to smf::Client::Connect. See Opening an SMF service channel.
		//! \param logger			Can be 0, your own implementation of an smf::Logger or a file logger 
		//!							(use smf::fileLogger function)
		//!							A local file logger return from a call to smf::InternalLogger. See Opening a Logger. 
		//!							Note: you do not have to use the SMF implementation; you may provide your own implementation of the Logger interface instead.
		//! \param chunkSize		The chunk size that the file will be chopped to before uploading or downloading.
		//!							If you pass zero here the default chunk size of 5K will be used.
		//! \param tempDir			The temporary directory that the file chunks will be stored in. You can ignore this parameter if the handler are only used for memory transfer.
		//!                         If you pass empty string here the system default temporary directory will be used.
		//! \param performanceMode  This controls the performance of the transfer with respect to the CPU consumption. 
		//!							If it is set to "CPUSaving", the CPU consumption is lower but transaction is slower 
		//!							If it is set to "HighPerformance", the transaction is faster but CPU consumption is higher
		//!                         By default, CPU saving mode is applied.
		//! \return					A pointer to a Smf::FileTransferServiceRequestHandlerExt2 object.
		//!	\remark					Include: FileTransferService.h, FileTransferServiceRequestHandlerExt2.h, Logger.h.
		//!	\post					Cleanup: You must call smf::FileTransferService::CloseRequestChannelExt2 to cleanup (see Closing a File Transfer Service Request Handler).
		//! \exception				You should at least catch smf::Error. Specific exceptions that might be thrown are defined in FileTransferServiceRequestHandler.h.
		//! \note					This function is thread safe. 
		FileTransferServiceRequestHandlerExt2* OpenRequestChannelExt2(
			smf::FileTransferServiceResourcePool* resPool,
			FileTransferServiceResponseHandler* responseHandler,
			ServiceChannel* channel,
			Logger* logger,
			unsigned int chunkSize = 0,
			const char* tempDir = "", 
			FtrPerformanceMode performanceMode = FtrPerformanceMode::CPUSaving
			);
#endif

		unsigned int SetChannelLimit(unsigned int);

		void SetQueueSleep(unsigned int);

		void SetReservedStackSize(unsigned int);

#ifdef WIN32
        unsigned int SetFileTransferProgressLimit(unsigned int);
#endif
	}
}

#endif