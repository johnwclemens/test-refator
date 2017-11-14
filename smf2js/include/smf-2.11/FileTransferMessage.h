#ifndef FILETRANSFERMESSAGE_H
#define FILETRANSFERMESSAGE_H

namespace smf{

	struct DataHolder{
		const void* data;
		unsigned int dataSize;
	};

    class FileTransferMessage
    {
    public:
	    enum
	    {
		    FailureReasonSize = sizeof(unsigned short)
	    };

	    enum MessageType
	    {
			RequestHandle,
		    RequestPutChunk,			
		    RequestGetChunk,
			RequestFileList,

			ReportHandle,
			ReportSuccessfulPutChunk,			
			ReportSuccessfulGetChunk,
			ReportFileList,
			ReportFailure,

			RequestHandleWithCompressionFlag,

#ifdef WIN32
			RequestPutCompMemChunk,
			ReportSuccessfulPutCompMemChunk,
#endif

		    LastMessageType,
    		
		    FirstMessageType = RequestHandle 
	    };

        enum
        {
            NumberOfMessageTypes = LastMessageType - FirstMessageType
        };

	    virtual ~FileTransferMessage() {}

	    enum FailureReason
	    {
		    Success,
		    UnclassifiedFailure,
			InvalidFileFormat,			//!< this means the file format is invalid
										// Possible report operation(s): RequestPutFile, RequestGetFile, RequestFileList 

			InvalidFile,				//!< this means fail to find the remote requesting file
										// Possible report operation(s): RequestGetFile 

			FailAccessTemporaryFile,	//!< this means fail to access local temporary file
										// Should not happen except someone removed the temporary file 
										// while putting or getting file.
										// If the temporary file cannot be created at the start of the operation,
										// it throws an exception rather than reporting an error.
										// Possible report operation(s): RequestPutFile, RequestGetFile

			InvalidLocalFile,			//!< this means fail to write the local file when getting file
										// If the system failed to read the local file when putting file,
										// it throws an exception rather than reporting an error
										// Possible report operation(s): RequestGetFile

			InvalidDirectory,			//!< this means fail to find the remote requesting directory
										// Possible report operation(s): RequestFileList

			InvalidRootDirectory,		//!< this means the root dir name does not exist, please refer to server configuration
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile, RequestFileList

			FileNameTooLong,			//!< this means the length of mapped file path exists system limit in server side
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile, RequestFileList

			InvalidHandle,				//!< this means the handle is invalid, note: each handle can only use for put/get file once
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile

			FailCreateFile,				//!< this means fail to read/write from/to a required file
										// Possible reason: 
										// 1) put file to /root/dir/file but /root/dir is an existing file
										// 2) the file size is too large to be handled by FTR service
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile

		    CodingError,				//!< this means there is something wrong with the code
		    MissedMessage,				//!< this is originated at the client side 
		    ServerOverloaded,
		    SizeMismatch,
		    UnsupportedMessageType,
		    UnknownMessage,
		    TotalMessageSizeTooBig,
			InvalidVersion,

			CompressionFailure,			//!< this means fail to compress a file/a memory stream
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile
			DecompressionFailure			//!< this means fail to decompress a file/ a memory stream
										// Possible report operation(s): RequestPutFile, RequestPutMemory, RequestGetFile
#ifdef WIN32
			, MemoryAccessViolation       //!< this means fail to read the memory from the given memory segment
										// Possible report operation(s): RequestPutMemory																								
#endif
	    };

	    unsigned int static FileTransferIdentifier(){
		    return *(unsigned int*)"FTR\0";
	    }

	    static unsigned int Version()
	    {
		    return *(unsigned int *)"0001";
	    }

		static unsigned int ExtendedFileInfoVersion(){
			return *(unsigned int *)"0002";
		}

		static unsigned int FileCompressionVersion(){
			return *(unsigned int *)"0003";
		}

#ifdef WIN32
		static unsigned int MemoryCompressionVersion(){
			return *(unsigned int *)"0004";
		}
#endif
    };
}

#endif
