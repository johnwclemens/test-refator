
#ifndef BULKCOMPPARAMETERREQUESTHANDLER_H
#define BULKCOMPPARAMETERREQUESTHANDLER_H

#include "PsdField.h"
#include "PsdRecord.h"
#include "Warning.h"
#include "Error.h"
#include "Types.h"

#include <vector>

//! This interface is for the remote client to make requests for Values, Handles or updates
//! 

namespace smf{
	class BulkCompParameterRequestHandler
	{
	public:

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
		
		
		//! \brief The schema is a wildcard representation of each set of fields that 
		//! are being requested. E.g. a schema containing:
		//!	/Users/*/Name
		//!	/Users/*/ILA
		//! would return the values of Name and ILA for all elements of the Users group
		//!The schema  can contain different group names provided the group array sizes are 
		//! the same, e.g.:
		//!  /ChannelStats/*/Address
		//!  /Users/*/Name
		//!
		//! \note Restrictions: The wildcard can only appear in an index position and there 
		//! can only be a single wildcard per field name, e.g. the following are *illegal*:
		//!	/*
		//!	/Users/100/*
		//!	/Users/*/SubnetList/*
		//!
		typedef std::vector<PsdField >Schema;

		//! \brief A record represents a whole row as defined by the schema. If the schema contains
		//! three wildcard names the record must have three values in the same order as the
		//! schema
		//!
		//! Each record has a row number, so when sending updates it is not neccesary to send 
		//! every row,  only send those with changes.
		typedef std::vector<PsdRecord >Records;
		
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

		virtual ~BulkCompParameterRequestHandler() {}
		
	};
}

#endif