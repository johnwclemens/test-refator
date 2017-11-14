#ifndef FILETRANSFERSERVICERESPONSEHANDLER_H
#define FILETRANSFERSERVICERESPONSEHANDLER_H

#include "FileTransferServerFileNode.h"
#include <vector>

//! File Transfer Service - Response Handler
//! This is the interface file transfer client service uses to report success/failure etc
//! coming back from the server.
//! The client must provide a concrete class and pass that object pointer into 
//! the file transfer client services when it calls OpenRequestChannel
//!
//! Please look at enum FailureReason in FileTransferMessage.h to get the error codes
namespace smf {
	class FileTransferServiceResponseHandler
	{
	public:

		typedef std::vector<smf::FileTransferServerFileNode> FileNodes;

		//! \brief The outcome of smf::ParameterServiceRequestHandler::RequestHandle
		//! \param handle	This is the available handle that can be used. 
		//! \param id		This is the identifier you supplied in RequestHandle.
		virtual void ReportHandle(unsigned int handle, unsigned int id)=0;
		
		//! \brief The outcome of smf::ParameterServiceRequestHandler::RequestPutFile
		//!	The handle is invalidated and cannot use for another request.
		//! \param handle	This is the handle you supplied in RequestHandle. 
		//! \param id		This is the identifier you supplied in RequestHandle.
		virtual void ReportSuccessfulPutFile(unsigned int handle, unsigned int id)=0;
		
		//! \brief The outcome of smf::ParameterServiceRequestHandler::RequestGetFile
		//!	The handle is invalidated and cannot use for another request.
		//! \param handle	This is the handle you supplied in RequestHandle. 
		//! \param id		This is the identifier you supplied in RequestHandle.
		virtual void ReportSuccessfulGetFile(unsigned int handle, unsigned int id)=0;
		
		//! \brief The outcome of smf::ParameterServiceRequestHandler::RequestFileList
		//!	Only same level of files and directories are reported.
		//! \param fileNodes	The file list containing FileTransferServerFileNode objects.
		//! \param id			This is the identifier you supplied in RequestHandle.
		virtual void ReportFileList(const FileNodes& fileNodes, unsigned int id)=0;

		virtual void ReportFailure(unsigned short reason, unsigned int id) = 0;

		virtual ~FileTransferServiceResponseHandler() {}
	};
}

#endif
