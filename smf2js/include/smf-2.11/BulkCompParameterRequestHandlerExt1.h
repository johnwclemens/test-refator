
#ifndef BULKCOMPPARAMETERREQUESTHANDLEREXT1_H
#define BULKCOMPPARAMETERREQUESTHANDLEREXT1_H

#include "BulkCompParameterRequestHandler.h"

#include <vector>

//! This interface is for the remote client to make requests for Values, Handles or updates on resizable array
//! 

namespace smf{
	class BulkCompParameterRequestHandlerExt1 : public BulkCompParameterRequestHandler
	{
	public:
        
    
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
        

		virtual ~BulkCompParameterRequestHandlerExt1() {}
		
	};
}

#endif