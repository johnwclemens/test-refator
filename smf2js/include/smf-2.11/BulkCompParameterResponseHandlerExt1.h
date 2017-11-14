
#ifndef BULKCOMPPARAMETERRESPONSEHANDLEREXT1_H
#define BULKCOMPPARAMETERRESPONSEHANDLEREXT1_H

#include "ConstantVector.h"
#include "BulkCompParameterResponseHandler.h"

namespace smf{
	class BulkCompParameterResponseHandlerExt1 : public BulkCompParameterResponseHandler
	{
	public:

		//! \brief Callback from smf::BulkCompParameterRequestHandlerExt1::RequestArraySize(const Schema& schema, UnsignedInt identifier)
		//! \param schema	This is a list of parameters requested in RequestArraySize function
		//! \param sizes     Result committed array sizes returned 
		//! \param identifier	This is the identifier you supplied in RequestArraySize.    
		virtual void ReportArraySize(const Schema& schema, Records& sizes, UnsignedInt identifier) = 0;
    
		//! \brief Callback from smf::BulkCompParameterRequestHandlerExt1::RequestArrayCapacity(const Schema& schema, UnsignedInt identifier)
		//! \param schema	This is a list of parameters requested in RequestArrayCapacity function
		//! \param capacities	Result array capacities returned 
		//! \param identifier	This is the identifier you supplied in RequestArrayCapacity.  
		virtual void ReportArrayCapacity(const Schema& schema, Records& capacities, UnsignedInt identifier) = 0;    

		virtual ~BulkCompParameterResponseHandlerExt1() {}

	};
}
#endif
