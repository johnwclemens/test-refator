#ifdef WIN32

#ifndef FILETRANSFERSERVICEREQUESTHANDLEREXT2_H
#define FILETRANSFERSERVICEREQUESTHANDLEREXT2_H

#include "Error.h"
#include <string>

#include "FileTransferServiceRequestHandlerExt1.h"

#ifdef WIN32
	typedef unsigned __int64 UInteger64;
#else
	typedef unsigned long long UInteger64;
#endif

//! File Transfer Service - Request Handler 
//! This interface is for the remote client to make requests 
//!

namespace smf {
    class FileTransferProgress
    {         
    public:
        virtual UInteger64      GetEstimatedTotalDataSize() const = 0;
        virtual UInteger64      GetActualDataTransferSize() const = 0;

        virtual                 ~FileTransferProgress() {};
    };

	class FileTransferServiceRequestHandlerExt2 : public FileTransferServiceRequestHandlerExt1
	{    
	public:		

		//Old exceptions inherited from FileTransferServiceRequestHandlerExt1 class
		//Please refer to FileTransferServiceRequestHandlerExt1.h for definitions
		//class SizeLimitExceedsAllocationLimit 
		//class CouldNotQueueItem 		
		//class CouldNotGetBuffer
		//class ConnectionDropped
		//class MultipleOperation
		//class InvalidLocalFile
		//class CompressionFailure
		//class DecompressionFailure
		//class FailAccessTemporaryFile
		//class FailAllocateMemory
		//class NullPointerException
        //class MemoryAccessViolation
        //class SendingCompressedMemoryNotSupported
		//class SourceDataSizeTooLarge					

		//! \brief Deprecated. Please use RequestHandle(unsigned int id, bool isCompress).
		//! This function can be used to get the handle to be used for put/get file or put memory segments without compression.
		//! The handle will be invalidated after one file transfer.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportHandle or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestHandle function is thread safe.
		virtual void RequestHandle(unsigned int id)=0;

		//! \brief This function can be used to get the handle to be used for put/get file or put memory segments , with an extra flag to determine compress the file or not before the transfer.
		//! The file will be decompressed automatically after the transfer.
		//! The handle will be invalidated after one file transfer.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param isCompress Specify whether to compress the file or not before the transfer.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportHandle or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestHandle function is thread safe.
		virtual void RequestHandle(unsigned int id, bool isCompress)=0;

		//! \brief This function can be used to upload a file to the server by handle.
		//! The handle will be invalidated after file transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandlerExt1::ReportHandle
		//! \param LocalFilePath	This is the local file path to be uploaded to server.
		//! \param ServerFilePath	This is the server file path to be stored in server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulPutFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestPutFile function is thread safe.
		virtual void RequestPutFile(unsigned int handle, const std::string& LocalFilePath, const std::string& ServerFilePath, unsigned int id)=0;
		
		//! \brief This function can be used to download a file from the server by handle.
		//! The handle will be invalidated after file transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandlerExt1::ReportHandle
		//! \param LocalFilePath	This is the local file path to be stored in your machine.
		//! \param ServerFilePath	This is the server file path to be downloaded from server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulGetFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestGetFile function is thread safe.
		virtual void RequestGetFile(unsigned int handle, const std::string& LocalFilePath, const std::string& ServerFilePath, unsigned int id)=0;

        //! \brief This function can be used to download a file from the server by handle.
		//! The handle will be invalidated after file transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandlerExt1::ReportHandle
		//! \param LocalFilePath	This is the local file path to be stored in your machine.
		//! \param ServerFilePath	This is the server file path to be downloaded from server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
        //! \param Progress This is to store a variable which SMF will update to show the file transfer progress
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulGetFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestGetFile function is thread safe.
		virtual void RequestGetFile(unsigned int handle, const std::string& LocalFilePath, const std::string& ServerFilePath, smf::FileTransferProgress* Progress, unsigned int id)=0;
        
		//! \brief This function can be used to get the file and directory list in a specific directory in server.
		//! Requesting the root (i.e. "/") will output the available root directories.
		//! Only same level of files and directories will be outputed.
		//! \param ServerDirectoryPath	This is the server directory path to be searched.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportFileList or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestFileList function is thread safe.
		virtual void RequestFileList(const std::string& ServerDirectoryPath, unsigned int id)=0;

		//! \brief This function can be used to send the memory segment to a specific file in the server .
		//! The handle will be invalidated after memory transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandlerExt1::ReportHandle
		//! \param buffer 	This is the pointer to the memory segment required to sent to the server. 
		//!                 The pointer must remain valid throughout the transmission
		//! \param bufferSize 	This specifies the size in bytes of the memory segment. 
		//! \param ServerFilePath	This is the server file path to be stored in server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulPutFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandlerExt1::RequestPutMemory function is thread safe.		
		virtual void RequestPutMemory(unsigned int handle, const void* buffer, unsigned int bufferSize, 
										const std::string& ServerFilePath, unsigned int id)=0;

		//! \brief This function can be used to cancel the previous request so that a new request can be requested.
		//! A new handle has to be requested for new request.
		//! Nothing will happen if no request is processing.
		//! \note	The FileTransferServiceRequestHandlerExt1::CancelRequest function is thread safe.
		virtual void CancelRequest()=0;

		virtual bool IsConnected() = 0;		
	};
}

#endif

#endif