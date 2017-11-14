#pragma once


#include "smf-2.11/BulkCompParameterResponseHandlerExt1.h"
#include "smf-2.11/Logger.h"

#include "Log.h"
#include "Locker.h"
#include "SectionLock.h"
#include "ThreadQueue.h"

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
	class BlkCompResponseHandler
		: public smf::BulkCompParameterResponseHandlerExt1
	{
	public:
		BlkCompResponseHandler() { }

		virtual void ReportRecords(Schema& schema, Records& records, UnsignedInt id)
		{
			smf::LogEntry::Severity lvl = smf::LogEntry::Informational;
			JsonHandler json;
			json.AddKeyValue("type", "psd-message");
			std::ostringstream log;

			for (Schema::const_iterator iter = schema.begin(); iter != schema.end(); iter++) {
				log << iter->FieldName() << "\n";
			}
			for (Records::const_iterator record = records.begin(); record != records.end(); record++) {
				log << "-----------------------\n"
					<< "Row number : " << (unsigned long)record->RowNumber() << "\n\n";
				char buf[4];
				itoa((unsigned long)record->RowNumber(), buf, 10);

				for (size_t i = 0; i < record->size(); i++) {
					const smf::PsdValue& value = (*record)[i];

					std::string fieldName = schema[i].FieldName();
					fieldName.replace(fieldName.find("*"), 1, buf);

					if (value.IsInteger()) {
						json.AddKeyValue(fieldName, (long)value.IntegerValue());
						log << fieldName << " (int) " << (long)value.IntegerValue() << "\n";
					}
					else if (value.IsString())
					{
						json.AddKeyValue(fieldName, value.StringValue());
						log << "(str) " << value.StringValue() << "\n";
					}
					else if (value.IsInteger64())
					{
						std::ostringstream oStr;
						oStr << value.Integer64Value();
						json.AddKeyValue(fieldName, oStr.str().c_str());
						log << "(int64) " << oStr.str().c_str() << "\n";
					}
					else if (value.IsDouble())
					{
						std::ostringstream oStr;
						oStr << value.DoubleValue();
						json.AddKeyValue(fieldName, oStr.str().c_str());
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

						json.AddKeyValue(fieldName, oStr.str().c_str());
						log << "(bin) " << oStr.str().c_str() << "\n";
					}
					else if (value.IsNull()) {
						lvl = smf::LogEntry::Critical;
						log << "(null)\n";
					}
				}
			}
			smf2js::TRLogService::GetInstance()->LogMessage(lvl, log.str());
			SmfResponseQueue.enqueue(json.Stringify());
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
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}

		// Callback of updating values
		virtual void ReportSuccessfulUpdate(UnsignedInt id)
		{
			std::ostringstream log;
			log << "Update (" << id << ") is completed succesfully.\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, log.str());
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
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}
		
		virtual void ReportFailure(unsigned short r)
		{
			std::ostringstream log;
			ErrorReason reason;
			log << reason.ReasonToString(r).c_str() << "\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}

		virtual void ReportArraySize(const Schema& schema, Records& sizes, UnsignedInt identifier) { }
		virtual void ReportArrayCapacity(const Schema& schema, Records& capacities, UnsignedInt identifier) { }

	private:
		// local log
	};

}