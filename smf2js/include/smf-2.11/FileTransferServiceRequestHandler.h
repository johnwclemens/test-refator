#ifndef FILETRANSFERSERVICEREQUESTHANDLER_H
#define FILETRANSFERSERVICEREQUESTHANDLER_H

#include "Error.h"
#include <string>

//! File Transfer Service - Request Handler
//! This interface is for the remote client to make requests
//!

namespace smf {
	class FileTransferServiceRequestHandler
	{
	public:

		//Exceptions
		class SizeLimitExceedsAllocationLimit : public smf::Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details): smf::Error(details)
			{
			}
		};

		class CouldNotQueueItem : public smf::Error
		{
		public:
			CouldNotQueueItem(): smf::Error("Could not queue an item in the request service")
			{
			}
		};

		class CouldNotGetBuffer: public smf::Error
		{
		public:
			CouldNotGetBuffer(unsigned int size):
			smf::Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}
		};

		class ConnectionDropped: public smf::Error
		{
		public:
			ConnectionDropped():smf::Error("The connection to the server has been closed or dropped")
			{
			}
		};

		class MultipleOperation: public smf::Error
		{
		public:
			MultipleOperation():smf::Error("Multiple concurrent operations is not allowed.")
			{
			}
		};

		class InvalidLocalFile: public smf::Error
		{
		public:
			InvalidLocalFile(const char* file):smf::Error("Cannot read/write to the local file - ")
			{
				(*this) << file;
			}
		};

		class CompressionFailure: public smf::Error
		{
		public:
#ifdef WIN32
			CompressionFailure(const char* file):smf::Error("Fail to compress a file/memory - ")
#else
            CompressionFailure(const char* file):smf::Error("Fail to compress a file - ")
#endif
			{
				(*this) << file;
			}
		};

		class DecompressionFailure: public smf::Error
		{
		public:
#ifdef WIN32
			DecompressionFailure(const char* file):smf::Error("Fail to decompress a file/memory - ")
#else
            DecompressionFailure(const char* file):smf::Error("Fail to decompress a file - ")
#endif
			{
				(*this) << file;
			}
		};

		class FailAccessTemporaryFile: public smf::Error
		{
		public:
			FailAccessTemporaryFile(const char* file):smf::Error("Cannot read/write to the local temporary file - ")
			{
				(*this) << file;
			}
		};

		class FailAllocateMemory: public smf::Error
		{
		public:
			FailAllocateMemory():smf::Error("Fail to allocate memory for request handler.")
			{
			}
		};					

		//! \brief Deprecated. Please use RequestHandle(unsigned int id, bool isCompress).
		//! This function can be used to get the handle to be used for put/get file without compression.
		//! The handle will be invalidated after one file transfer.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportHandle or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandler::RequestHandle function is thread safe.
		virtual void RequestHandle(unsigned int id)=0;

		//! \brief This function can be used to get the handle to be used for put/get file, with an extra flag to determine compress the file or not before the transfer.
		//! The file will be decompressed automatically after the transfer.
		//! The handle will be invalidated after one file transfer.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \param isCompress Specify whether to compress the file or not before the transfer.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportHandle or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandler::RequestHandle function is thread safe.
		virtual void RequestHandle(unsigned int id, bool isCompress)=0;

		//! \brief This function can be used to upload a file to the server by handle.
		//! The handle will be invalidated after file transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandler::ReportHandle
		//! \param LocalFilePath	This is the local file path to be uploaded to server.
		//! \param ServerFilePath	This is the server file path to be stored in server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulPutFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandler::RequestPutFile function is thread safe.
		virtual void RequestPutFile(unsigned int handle, const std::string& LocalFilePath, const std::string& ServerFilePath, unsigned int id)=0;
		
		//! \brief This function can be used to download a file from the server by handle.
		//! The handle will be invalidated after file transfer is finished.
		//! \param handle	This is the handle reported to you by smf::FileTransferServiceResponseHandler::ReportHandle
		//! \param LocalFilePath	This is the local file path to be stored in your machine.
		//! \param ServerFilePath	This is the server file path to be downloaded from server.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportSuccessfulGetFile or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandler::RequestGetFile function is thread safe.
		virtual void RequestGetFile(unsigned int handle, const std::string& LocalFilePath, const std::string& ServerFilePath, unsigned int id)=0;
		
		//! \brief This function can be used to get the file and directory list in a specific directory in server.
		//! Requesting the root (i.e. "/") will output the available root directories.
		//! Only same level of files and directories will be outputed.
		//! \param ServerDirectoryPath	This is the server directory path to be searched.
		//! \param id	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \exception smf::Error	See FileTransferServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the operation should be reported through your implementation of 
		//! smf::FileTransferServiceResponseHandler::ReportFileList or smf::FileTransferServiceResponseHandler::ReportFailure.
		//! \note	The FileTransferServiceRequestHandler::RequestFileList function is thread safe.
		virtual void RequestFileList(const std::string& ServerDirectoryPath, unsigned int id)=0;

		//! \brief This function can be used to cancel the previous request so that a new request can be requested.
		//! A new handle has to be requested for new request.
		//! Nothing will happen if no request is processing.
		//! \note	The FileTransferServiceRequestHandler::CancelRequest function is thread safe.
		virtual void CancelRequest()=0;

		virtual bool IsConnected() = 0;

		virtual ~FileTransferServiceRequestHandler() {}
	};
}

#endif
