
#ifndef BULKPARAMETERREQUESTHANDLEREXT1_H
#define BULKPARAMETERREQUESTHANDLEREXT1_H


#include "BulkParameterRequestHandler.h"

//! Psd Bulk Service - Support transactional or non-transactional query
//! This interface is for the remote client to make requests for Values, Handles or updates
//! 

namespace smf{
	class BulkParameterRequestHandlerExt1 : public BulkParameterRequestHandler
	{
	public:

		//! \brief Use this function to retrieve parameter values.
		//! \param schema	This is a list of parameters to query values for.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: BulkParameterResponseHandler.h, BulkParameterRequestHandler.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::BulkParameterResponseHandler in the ReportRecords function
		//! \exception smf::Error See BulkParameterRequestHandler.h for more specific exceptions.
		virtual void RequestRecords(const Schema& schema, UnsignedInt identifier)=0;
		
		//! \brief Use this function to update parameter values.
		//! \param schema     This is a list of parameters that you want to set. 
		//! \param records     Consists of a row number and a row of values you want to update.  Each row of values should be in the same order as the fields defined in the schema list. 
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: BulkParameterResponseHandler.h, BulkParameterRequestHandler.h, Error.h
		virtual void UpdateValues(const Schema& schema, const Records& records, UnsignedInt identifier)=0;

        virtual bool IsConnected() = 0;
		
		//! \brief Use this function to retrieve parameter values. This API is compatible with the old server but the query will be processed with transaction.
		//! \param transactional	This is a flag to enable or disable transaction. Set as true to tell the API to use transactional query; or set as false to tell the API to use non-transactional query.
		//! \param schema	This is a list of parameters to query values for.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \remark Include: BulkParameterResponseHandler.h, BulkParameterRequestHandlerExt1.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::BulkParameterResponseHandler in the ReportRecords function
		//! \exception smf::Error See BulkParameterRequestHandlerExt1.h for more specific exceptions.
		virtual void RequestRecords(bool transactional, const Schema& schema, UnsignedInt identifier)=0;
		
		virtual ~BulkParameterRequestHandlerExt1() {}
		
	};
}

#endif