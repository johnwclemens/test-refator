
#ifndef BULKPARAMETERRESPONSEHANDLER_H
#define BULKPARAMETERRESPONSEHANDLER_H

#include "ConstantVector.h"
#include "PsdRecord.h"
#include "PsdField.h"
#include "PsdFieldValue.h"
#include "Types.h"

namespace smf{
	class BulkParameterResponseHandler
	{
	public:
		// A ConstantVector should provide the read functionality of the vector
		// It is unsafe to change a vector (or string etc...) created on one side 
		// of a DLL boundary, from the other side - i.e. if the vector is allocated 
		// inside the DLL it should not be changed outside the DLL.
		typedef smf::ConstantVector<smf::PsdRecord> Records;
		typedef smf::ConstantVector<smf::PsdField> Schema;
        typedef smf::ConstantVector<smf::PsdFieldValue> SchemaErrors;

		//! \brief Callback from smf::BulkParameterServiceRequestHandler::RequestRecords(const Schema& schema, UnsignedInt identifier)
		//! \param schema	This is a list of parameters requested in RequestRecords function
		//! \param records     Result values returned 
		//! \param identifier	This is the identifier you supplied in RequestValues.
		virtual void ReportRecords(Schema& schema, Records& records, UnsignedInt identifier)=0;
		virtual void ReportFailedRequest(SchemaErrors&, UnsignedInt identifier)=0;
	
		//! \brief The outcome of the update values operation 
		//! \param identifier This is an identifier supplied by you, SMF will pass it back to you when reporting the outcome.
		virtual void ReportSuccessfulUpdate(UnsignedInt identifier)=0;
		virtual void ReportFailedUpdates(SchemaErrors&, UnsignedInt identifier) = 0;
		virtual void ReportFailure(unsigned short reason) = 0;

		virtual ~BulkParameterResponseHandler() {}
	};
}
#endif
