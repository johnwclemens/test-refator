
#ifndef BULKCOMPPARAMETERREQUESTHANDLEREXT2_H
#define BULKCOMPPARAMETERREQUESTHANDLEREXT2_H

#include "BulkCompParameterRequestHandlerExt1.h"

#include <vector>

//! Psd Bulk Service with compression - Support transactional or non-transactional query
//! This interface is for the remote client to make requests for Values, Handles or updates on resizable array
//! 

namespace smf{
	class BulkCompParameterRequestHandlerExt2 : public BulkCompParameterRequestHandlerExt1
	{
	public:
     
		//! \brief Use this function to retrieve parameter values.
		//! \param schema	This is a list of parameters to query values for.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \param compress	This is a flag to enable or disable compression.
		//! \remark Include: BulkCompParameterResponseHandler.h, BulkCompParameterRequestHandler.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::BulkCompParameterResponseHandler in the ReportRecords function
		//! \exception smf::Error See BulkCompParameterRequestHandler.h for more specific exceptions.
		virtual void RequestRecords(const Schema& schema, UnsignedInt identifier, bool compress = false)=0;
		
		//! \brief Use this function to update parameter values.
		//! \param schema     This is a list of parameters that you want to set. 
		//! \param records     Consists of a row number and a row of values you want to update.  Each row of values should be in the same order as the fields defined in the schema list. 
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \param compress	This is a flag to enable or disable compression.
		//! \remark Include: BulkCompParameterResponseHandler.h, BulkCompParameterRequestHandler.h, Error.h
		virtual void UpdateValues(const Schema& schema, const Records& records, UnsignedInt identifier, bool compress = false)=0;

        virtual bool IsConnected() = 0;

		//! \brief Use this function to retrieve array committed size.
		//! \param schema	This is a list of parameters to query committed size.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the committed size.
		//! \param compress	This is a flag to enable or disable compression.
		//! \remark Include: BulkCompParameterResponseHandler.h, BulkCompParameterResponseHandlerExt1.h, BulkCompParameterRequestHandler.h, ulkCompParameterRequestHandlerExt1.h, Error.h.
		//! \post The committed sizes will be reported back through your implementation of the smf::BulkCompParameterResponseHandlerExt1 in the ReportCommittedSize function
		//! \exception smf::Error See BulkCompParameterRequestHandler.h for more specific exceptions.
		virtual void RequestArraySize(const Schema& schema, UnsignedInt identifier, bool compress = false) = 0;
		
		//! \brief Use this function to retrieve array capacity.
		//! \param schema	This is a list of parameters to query capacity.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the capacity.
		//! \param compress	This is a flag to enable or disable compression.
		//! \remark Include: BulkCompParameterResponseHandler.h, BulkCompParameterResponseHandlerExt1.h, BulkCompParameterRequestHandler.h, BulkCompParameterRequestHandlerExt1.h, Error.h.
		//! \post The capacity will be reported back through your implementation of the smf::BulkCompParameterResponseHandler in the ReportCapacity function
		//! \exception smf::Error See BulkCompParameterRequestHandler.h for more specific exceptions.
		virtual void RequestArrayCapacity(const Schema& schema, UnsignedInt identifier, bool compress = false) = 0;
      
    
		//! \brief Use this function to retrieve parameter values. This API is compatible with the old server but the query will be processed with transaction.
		//! \param transactional	This is a flag to enable or disable transaction. Set as true to tell the API to use transactional query; or set as false to tell the API to use non-transactional query.
		//! \param schema	This is a list of parameters to query values for.  Wildcard representation is allowed in parameter name.  
		//!					See Creating a schema.
		//! \param identifier	This is an identifier supplied by you, SMF will pass it back to you when reporting the values.
		//! \param compress	This is a flag to enable or disable compression.
		//! \remark Include: BulkCompParameterResponseHandler.h, BulkCompParameterRequestHandlerExt2.h, Error.h.
		//! \post The values will be reported back through your implementation of the smf::BulkCompParameterResponseHandler in the ReportRecords function
		//! \exception smf::Error See BulkCompParameterRequestHandlerExt2.h for more specific exceptions.
		virtual void RequestRecords(bool transactional, const Schema& schema, UnsignedInt identifier, bool compress = false)=0;
        

		virtual ~BulkCompParameterRequestHandlerExt2() {}
		
	};
}

#endif