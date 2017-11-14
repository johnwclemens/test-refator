
#ifndef PSDSERVICEREQUESTHANDLER_H
#define PSDSERVICEREQUESTHANDLER_H

#include "PsdField.h"
#include "PsdHandle.h"
#include "PsdHandleValue.h"
#include "PsdFieldValue.h"
#include "PsdFieldHandle.h"
//#include "ServiceChannel.h"
#include "ParameterServiceResponseHandler.h"
#include "Warning.h"
#include "Error.h"
#include "Logger.h"
#include "Types.h"

#include <vector>

//! Psd Service - Request Handler
//! This interface is for the remote client to make requests for Values, Handles or updates
//! 

namespace smf{
	class ParameterServiceRequestHandler
	{
	public:
		typedef unsigned int Handle ;
		class LineTooBig:
			public smf::Warning
		{
		public:
			LineTooBig()
				: smf::Warning("A line exceeded the maximum size of message the server will handle")
			{
			}
		};

		class CouldNotGetBuffer:
		public smf::Error
		{
		public:
			CouldNotGetBuffer(unsigned int size):
			smf::Error("Could not get a message buffer from the request service - ")
			{
				(*this) << " size requested " << size;
			}

		};

		class ConnectionDropped:
		public smf::Error
		{
		public:
			ConnectionDropped():smf::Error("The connection to the server has been closed or dropped"){
			}

		};

		class SizeLimitExceedsAllocationLimit:
			public smf::Error
		{
		public:
			SizeLimitExceedsAllocationLimit(const char* details):
			smf::Error(details)
			{
				
			}
		};

		typedef std::vector<PsdField >Fields;
		typedef std::vector<PsdHandle >Handles;
		typedef std::vector<PsdFieldValue> FieldValues;
		typedef std::vector<PsdHandleValue> HandleValues;
		typedef std::vector<PsdField >Partitions;

		//! \brief Use this function to retrieve parameter values by name.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportValues function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandler::RequestValues function is thread safe.
		virtual void RequestValues(const Fields& fields, UnsignedInt identifier)=0;

		//! \brief Use this function to retrieve values for a list of parameter handles. Note, first you must retrieve valid handles for each parameter (see Retrieving Handles for Parameters).
		//! \param handles	This is a list of handles. You will need to create this list from the list of handles returned in smf::ParameterServiceResponseHandler::ReportHandles. 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \post The values will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportValues function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note The ParameterServiceRequestHandler::RequestValues function is thread safe
		virtual void RequestValues(const Handles& handles, UnsignedInt identifier )=0;

		//! \brief This function can be used to get the handles for a list of parameters.
		//! A handle directly maps through to a parameter at the server, 
		//! allowing the server to access the given parameter without having to search for it.
		//! \param fields	This is a list of parameter names.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the handles.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \post The handles will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportHandles function
		//! \exception smf::Error	See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandler::RequestHandles function is thread safe.
		virtual void RequestHandles(const Fields& fields, UnsignedInt identifier)=0;

		//! \brief Use this function to update a set of parameter values by name.
		//! Updates via this method are transactional in nature, 
		//! i.e. if one of the values in the update list cannot be committed for some reason, 
		//! all the updates in the list will be rejected. 
		//! Also, transactions are not allowed to cross partitions, 
		//! so all the updates in the list must be from the same partition.
		//! \param fieldValues	This is a list of parameter names and values that you wish to set. 
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \exception smf::Error	See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \post The outcome of the update operation should be reported through your implementation of 
		//! smf::ParameterServiceResponseHandler::ReportSuccessfulUpdate or smf::ParameterServiceResponseHandler::ReportFailedUpdate.
		//! note The ParameterServiceRequestHandler::UpdateValues function is thread safe.
		virtual void UpdateValues(const FieldValues& fieldValues, UnsignedInt identifier)=0;

		//! \brief Use this function to update a set of parameter values by handle. 
		//! Note, first you must retrieve valid handles for each parameter 
		//! (see Retrieving Handles for Parameters).
		//! Updates via this method are transactional in nature, 
		//! i.e. if one of the values in the update list cannot be committed for some reason, 
		//! all the updates in the list will be rejected. 
		//! Also, transactions are not allowed to cross partitions, 
		//! so all the updates in the list must be from the same partition.
		//! \param handleValues		This is a list of handles and values that you wish to set. 
		//! \param identifier		This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		//! \remark	Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \post The outcome of the update operation should be reported through your implementation of 
		//! smf::ParameterServiceResponseHandler::ReportSuccessfulUpdate or smf::ParameterServiceResponseHandler::ReportFailedUpdate 
		//! (see the Parameter Service sample in the SMF-SDK samples directory for an example implementation).
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note The ParameterServiceRequestHandler::UpdateValues function is thread safe.
		virtual void UpdateValues(const HandleValues& handleValues, UnsignedInt identifier)=0;
		
		virtual void RequestSchema(const Partitions& , UnsignedInt)=0;

		//! \brief Use this function to retrieve content of a metadata file with the given logical name and type.
		//! \param name		The logical name of the metadata.  The name should be considered to be the kind of metadata requested, and nothing specific such as a filename.  Details such as how the metadata is stored are properties of how SMF is configured, and should not be relied on by clients.
		//! \param type		the type (i.e. format) of the metadata file.
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \post The values will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportMetadata function, or the ReportMetadataError function when an error occurs.
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note The ParameterServiceRequestHandler::RequestMetadata function is thread safe
		virtual void RequestMetadata(const std::string &name, const std::string &type, UnsignedInt identifier)=0;
		virtual void RequestPartitions(UnsignedInt)=0;
		

		virtual bool IsConnected() = 0;

		virtual ~ParameterServiceRequestHandler() {}
		
	};
}

#endif