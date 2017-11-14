#pragma once

#include "smf-2.11/BulkParameterResponseHandler.h"
#include "smf-2.11/Logger.h"

#include "Log.h"
#include "Locker.h"
#include "SectionLock.h"
#include "ThreadQueue.h"

#include "ErrorReason.h"
#include "Common.h"
#include "TRLogService.h"
#include "ErrorReason.h"
#include "Locker.h"
#include "JsonHandler.h"

#include <map>
#include <string>
#include <sstream>

namespace smf2js
{
	class BlkResponseHandler
		: public smf::BulkParameterResponseHandler
	{
	public:
		BlkResponseHandler() { }

		virtual void ReportRecords(Schema& schema, Records& records, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportRecords begin (" << id << ")\n";

			log << "---- schema (" << (unsigned long)schema.size() << ") ----\n";
			for (Schema::const_iterator iter = schema.begin(); iter != schema.end(); iter++) {
				log << iter->FieldName() << "\n";
			}

			log << "---- records (" << (unsigned long)records.size() << ") ----\n";
			for (Records::const_iterator record = records.begin(); record != records.end(); record++) {
				log << "-----------------------\n"
					<< "Row number : " << (unsigned long)record->RowNumber() << "\n\n";

				for (size_t i = 0; i < record->size(); i++) {
					const smf::PsdValue& value = (*record)[i];

					if (value.IsInteger()) {
						log << "(int) " << (long)value.IntegerValue() << "\n";
					}
					else if (value.IsString())
					{
						log << "(str) " << value.StringValue() << "\n";
					}
					else if (value.IsInteger64())
					{
						std::ostringstream oStr;
						oStr << value.Integer64Value();
						log << "(int64) " << oStr.str().c_str() << "\n";
					}
					else if (value.IsDouble())
					{
						std::ostringstream oStr;
						oStr << value.DoubleValue();
						log << "(dbl) " << oStr.str().c_str() << "\n";
					}
					else if (value.IsBinary()) {
						std::ostringstream oStr;

						smf::BinaryHolder binVal = value.BinaryValue();
						const void* data = binVal.data;
						oStr << std::hex;
						oStr.fill('0');
						for (unsigned int cnt = 0; cnt < binVal.dataSize; cnt++) {
							oStr.width(2);
							oStr << (unsigned int)((unsigned char*)data)[cnt] << " ";
						}

						log << "(bin) " << oStr.str().c_str() << "\n";
					}
					else if (value.IsNull()) {
						log << "(null)\n";
					}
				}
			}
			log << "-----------------------\n";

			log << "ReportRecords end\n\n";
		}

		virtual void ReportFailedRequest(SchemaErrors& schemaError, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportFailedRequest begin (" << id << ")\n";
			ErrorReason reason;
			for (SchemaErrors::const_iterator iter = schemaError.begin(); iter != schemaError.end(); iter++) {
				log << iter->FieldName()
					<< " - "
					<< reason.ReasonToString(iter->FailureReason()).c_str()
					<< "\n";
			}
			log << "ReportFailedRequest end\n\n";
		}

		virtual void ReportSuccessfulUpdate(UnsignedInt id)
		{
			std::ostringstream log;
			log << "Update (" << id << ") is completed succesfully.\n\n";
		}

		virtual void ReportFailedUpdates(SchemaErrors& schemaError, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportFailedUpdates begin (" << id << ")\n";
			ErrorReason reason;
			for (SchemaErrors::const_iterator iter = schemaError.begin(); iter != schemaError.end(); iter++) {
				log << iter->FieldName()
					<< " - "
					<< reason.ReasonToString(iter->FailureReason()).c_str()
					<< "\n";
			}
			log << "ReportFailedUpdates end\n\n";
		}

		virtual void ReportFailure(unsigned short r)
		{
			std::ostringstream log;
			ErrorReason reason;
			log << reason.ReasonToString(r).c_str() << "\n";
		}

	private:
	};
}