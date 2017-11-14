
#ifndef PSDSERVICERREQUESTHANDLEREXT3_H
#define PSDSERVICERREQUESTHANDLEREXT3_H


#include "ParameterServiceRequestHandlerExt2.h"

//! Psd Service - Support parameter subscription
//! This interface is for the remote client to make requests for Values, Handles or updates
//! 

namespace smf{
	class ParameterServiceRequestHandlerExt3 : public ParameterServiceRequestHandlerExt2
	{
	public:
			
		class ServerNotSupportSubscription:
		public smf::Error
		{
		public:
			ServerNotSupportSubscription():smf::Error("SMF server does not support parameter subscription API"){
			}

		};

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
		//! \brief Use this function to retrieve the array committed size of parameter by name.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the committed sizes.
		//! \remark Include: ParameterServiceResponseHandlerExt1.h, ParameterServiceRequestHandlerExt1.h, Error.h.
		//! \post The array sizes will be reported back through your implementation of the smf::ParameterServiceResponseHandlerExt1 in the ReportArraySize function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandlerExt1::RequestArraySize function is thread safe.
		virtual void RequestArraySize(const Fields& fields, UnsignedInt identifier)=0;
		
   
		//! \brief Use this function to retrieve the array capacity of parameter by name.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the capacities.
		//! \remark Include: ParameterServiceResponseHandlerExt1.h, ParameterServiceRequestHandlerExt1.h, Error.h.
		//! \post The capacities will be reported back through your implementation of the smf::ParameterServiceResponseHandlerExt1 in the ReportArraCapacity function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandlerExt1::RequestArrayCapacity function is thread safe.
		virtual void RequestArrayCapacity(const Fields& fields, UnsignedInt identifier)=0;
    
		//! \brief Use this function to retrieve parameter values by name. This API is compatible with the old server but the query will be processed with transaction.
		//! \param transactional	This is a flag to enable or disable transaction. Set as true to tell the API to use transactional query; or set as false to tell the API to use non-transactional query.
		//! \param fields	This is a list of parameters to query values for. 
		//!					See Creating a Field List.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportValues function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note	The ParameterServiceRequestHandler::RequestValues function is thread safe.
		virtual void RequestValues(bool transactional, const Fields& fields, UnsignedInt identifier)=0;

		//! \brief Use this function to retrieve values for a list of parameter handles. Note, first you must retrieve valid handles for each parameter (see Retrieving Handles for Parameters). This API is compatible with the old server but the query will be processed with transaction.
		//! \param transactional	This is a flag to enable or disable transaction. Set as true to tell the API to use transactional query; or set as false to tell the API to use non-transactional query.
		//! \param handles	This is a list of handles. You will need to create this list from the list of handles returned in smf::ParameterServiceResponseHandler::ReportHandles. 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: ParameterServiceResponseHandler.h, ParameterServiceRequestHandler.h, Error.h
		//! \post The values will be reported back through your implementation of the smf::ParameterServiceResponseHandler in the ReportValues function
		//! \exception smf::Error See ParameterServiceRequestHandler.h for more specific exceptions.
		//! \note The ParameterServiceRequestHandler::RequestValues function is thread safe
		virtual void RequestValues(bool transactional, const Handles& handles, UnsignedInt identifier )=0;
		
		//! \brief To receive parameter update you must first subscribe to the parameter service.
		//! (see Opening a Parameter Service Request Channel for how to get a ParameterServiceRequestHandler)
		//! \param id			This is an identifier defined by the application. 
		//!						SMF does not use it; 
		//!						SMF will pass this back to you when reporting whether the subscription was accepted or not through your ParameterServiceResponseHandler implementation.
	    //! \param reportIntervalInSec	    This is a time internal in second to receive parameter update.
        //! \param fields   	This is a list of parameters to query values for. 
		//!				    	See Creating a Field List.
        //! \param compressFirst    This is a flag to enable or disable compression on the first snapshot image.
        //! \param compressSubSeq   This is a flag to enable or disable compression on the subsequence update image.
        //! \remark 				Include: ParameterServiceRequestHandler.h, ParameterServiceResponseHandler, Error.h
		//! \exception smf::Error	See ParameterServiceRequestHandler.h for a list of specific exceptions.
		//! \note					The subscribe function is thread safe.
		//! \post					Once successfully subscribed you will be sent all parameters update through your ParameterServiceResponseHandler implementation
		//!							through the smf::ParameterServiceResponseHandler::Report function
		virtual void Subscribe(UnsignedInt id, UnsignedInt reportIntervalInSec, const Fields& fields, bool compressFirst, bool compressSubSeq) = 0;
		virtual void Unsubscribe(UnsignedInt id) = 0;

		virtual ~ParameterServiceRequestHandlerExt3() {}
		
	};
}

#endif