#pragma once

#include "smf-2.11/logger.h"
#include "smf-2.11/ParameterServiceResponseHandlerExt1.h"

#include "Log.h"
#include "Locker.h"
#include "SectionLock.h"
#include "ThreadQueue.h"

#include <sstream>

#include "ArsResponseHandler.h"
#include "Common.h"
#include "TRLogService.h"
#include "ErrorReason.h"
#include "Locker.h"
#include "JsonHandler.h"


#include <map>
#include <string>
#include <sstream>

//static smf2js::SafeQueue<std::string> PsdResponseQueue;

namespace smf2js
{
	class PsdResponseHandler
		: public smf::ParameterServiceResponseHandlerExt1
	{
	public:
		PsdResponseHandler() { }
		~PsdResponseHandler() { }

		virtual void ReportValues(FieldValues& fieldValues, UnsignedInt id)
		{
			JsonHandler json;
			json.AddKeyValue("type", "psd-message");
			std::ostringstream log;
			log << "ReportValuesByName begin (" << id << ")\n";

			for (size_t i = 0; i < fieldValues.size(); i++)
			{
				if (fieldValues[i].IsString())
				{
					json.AddKeyValue(fieldValues[i].FieldName(), fieldValues[i].ValueStr());
					log << fieldValues[i].FieldName() << " = " << fieldValues[i].ValueStr() << "\n";
				}
				else if (fieldValues[i].IsInteger()) {
					json.AddKeyValue(fieldValues[i].FieldName(), (unsigned int)fieldValues[i].ValueInt());
					log << fieldValues[i].FieldName() << " = " << fieldValues[i].ValueInt() << "\n";
				}
				else if (fieldValues[i].IsInteger64()) {
					/* You should check it is a Integer64 before checking it is a binary */
					json.AddKeyValue(fieldValues[i].FieldName(), fieldValues[i].ValueInt64());
					std::ostringstream oss;
					oss << fieldValues[i].FieldName() << " = " << fieldValues[i].ValueInt64() << "\n";
					log << oss.str().c_str();
				}
				else if (fieldValues[i].IsDouble()) {
					/* You should check it is a Double before checking it is a binary */
					json.AddKeyValue(fieldValues[i].FieldName(), fieldValues[i].ValueDouble());
					std::ostringstream oss;
					oss << fieldValues[i].FieldName() << " = " << fieldValues[i].ValueDouble() << "\n";
					log << oss.str().c_str();
				}
				else if (fieldValues[i].IsBinary()) {
					std::string value = (char*)fieldValues[i].ValueBin().data;
					value = value.substr(0, fieldValues[i].ValueBin().dataSize);
					json.AddKeyValue(fieldValues[i].FieldName(), value);
					log << fieldValues[i].FieldName() << " = " << value.c_str() << "\n";
				}
				else {
					// error
					ErrorReason reason;
					log << "Query value failed: " << fieldValues[i].FieldName() << " - " << reason.ReasonToString(fieldValues[i].FailureReason()).c_str() << "\n";
				}
			}

			log << "ReportValuesByName end\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, log.str());
			SmfResponseQueue.enqueue(json.Stringify());
		}

		virtual void ReportValues(HandleValues& handleValues, UnsignedInt id)
		{
			smf::LogEntry::Severity lvl = smf::LogEntry::Informational;
			JsonHandler json;
			json.AddKeyValue("type", "psd-message");
			std::ostringstream log;
			log << "ReportValuesByHandle begin (" << id << ")\n";

			for (size_t i = 0; i < handleValues.size(); i++)
			{
				std::map<smf::ParameterServiceResponseHandler::Handle, std::string>::iterator iter;
				iter = handleName.find(handleValues[i].Identifier());

				if (iter != handleName.end())
				{
					if (handleValues[i].IsString())
					{
						json.AddKeyValue(iter->second.c_str(), handleValues[i].ValueStr());
						//log << iter->second.c_str() << " = " << handleValues[i].ValueStr() << "\n";
					}
					else if (handleValues[i].IsInteger()) {
						json.AddKeyValue(iter->second.c_str(), (unsigned int)handleValues[i].ValueInt());
						//log << iter->second.c_str() << " = " << handleValues[i].ValueInt() << "\n";
					}
					else if (handleValues[i].IsInteger64()) {
						/* You should check it is a Integer64 before checking it is a binary */
						json.AddKeyValue(iter->second.c_str(), handleValues[i].ValueInt64());
						//std::ostringstream oss;
						//oss << iter->second.c_str() << " = " << handleValues[i].ValueInt64() << "\n";
						//log << oss.str().c_str();
					}
					else if (handleValues[i].IsDouble()) {
						/* You should check it is a Double before checking it is a binary */
						json.AddKeyValue(iter->second.c_str(), handleValues[i].ValueDouble());
						//std::ostringstream oss;
						//oss << iter->second.c_str() << " = " << handleValues[i].ValueDouble() << "\n";
						//log << oss.str().c_str();
					}
					else if (handleValues[i].IsBinary()) {
						std::string value = (char*)handleValues[i].ValueBin().data;
						value = value.substr(0, handleValues[i].ValueBin().dataSize);
						json.AddKeyValue(iter->second.c_str(), value);
						log << iter->second.c_str() << " = " << value.c_str() << "\n";

					}
					else {
						// error
						lvl = smf::LogEntry::Critical;
						ErrorReason reason;
						log << "Query value failed: " << (*iter).second.c_str() << " - " << reason.ReasonToString(handleValues[i].FailureReason()).c_str() << "\n";
					}
				}
				else {
					// error
					lvl = smf::LogEntry::Critical;
					ErrorReason reason;
					log << " Unknown handle: " << handleValues[i].Identifier() << " - " << reason.ReasonToString(handleValues[i].FailureReason()).c_str() << "\n";
				}
			}

			log << "ReportValuesByHandle end\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(lvl, log.str());
			//if(lvl == smf::LogEntry::Critical)
				std::cout << log.str() << std::endl;
			SmfResponseQueue.enqueue(json.Stringify());
		}

		virtual void ReportHandles(FieldHandles& fieldHandles, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportHandlesByName begin (" << id << ")\n";

			for (size_t i = 0; i < fieldHandles.size(); i++)
			{
				if (fieldHandles[i].FailureReason() == smf::PsdMessage::Success) {
					log << fieldHandles[i].FieldName() << "\n";

					//get the handle
					handleName[fieldHandles[i].Handle()] = fieldHandles[i].FieldName();

					// protect this map as the main() thread will call FindHandle()
					Locker lock(&handleMapLock);
					nameHandle[fieldHandles[i].FieldName()] = fieldHandles[i].Handle();
					lock.Release();
				}
				else {
					// error
					ErrorReason reason;
					log << fieldHandles[i].FieldName() << " - " << reason.ReasonToString(fieldHandles[i].FailureReason()).c_str() << "\n";
				}
			}

			log << "ReportHandlesByName end\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, log.str());
		}

		virtual void ReportSuccessfulUpdate(UnsignedInt id)
		{
			std::ostringstream log;
			log << "Update (" << id << ") is completed succesfully.\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Informational, log.str());
		}

		virtual void ReportSchema(Schema&, UnsignedInt id) { }
		virtual void ReportPartitions(Partitions&, UnsignedInt id) { }
		virtual void ReportFailedUpdates(FieldValues& fieldValues, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportFailedUpdateByName begin (" << id << ")\n";
			ErrorReason reason;
			for (unsigned int i = 0; i < fieldValues.size(); i++)
			{
				log << " " << fieldValues[i].FieldName() << " - " << reason.ReasonToString(fieldValues[i].FailureReason()).c_str() << "\n";
			}
			log << "ReportFailedUpdateByName end\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}

		virtual void ReportFailedUpdates(HandleValues& handleValues, UnsignedInt id)
		{
			std::ostringstream log;
			log << "ReportFailedUpdateByHandle begin (" << id << ")\n";
			ErrorReason reason;
			for (unsigned int i = 0; i < handleValues.size(); i++)
			{
				std::map< smf::PsdFieldHandle::HandleType, std::string >::iterator iter;
				iter = handleName.find(handleValues[i].Identifier());

				if (iter != handleName.end())
				{
					log << " " << iter->second.c_str() << " - : " << reason.ReasonToString(handleValues[i].FailureReason()).c_str() << "\n";
				}
				else
				{
					log << " Unknown handle: " << handleValues[i].Identifier() << " - Failure code: " << handleValues[i].FailureReason() << "\n";
				}
			}
			log << "ReportFailedUpdateByHandle end\n\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}

		virtual void ReportFailure(unsigned short r)
		{
			std::ostringstream log;
			ErrorReason reason;
			log << reason.ReasonToString(r).c_str() << "\n";
			smf2js::TRLogService::GetInstance()->LogMessage(smf::LogEntry::Critical, log.str());
		}

		virtual void ReportArraySize(FieldSize& fieldSize, UnsignedInt identifier) { }
		virtual void ReportArrayCapacity(FieldCapacity& fieldCapacity, UnsignedInt identifier) { }

		smf::ParameterServiceResponseHandler::Handle FindHandle(const char* name)
		{
			// return 0 if the handle cannot be found
			smf::PsdFieldHandle::HandleType handle = 0;

			// num of times to retry until the handle has been reported by ReportHandle()
			const int numRetry = 10;

			Locker lock(&handleMapLock);
			std::map<std::string, smf::ParameterServiceResponseHandler::Handle>::iterator iter;
			iter = nameHandle.find(name);

			for (int retry = 0; retry < numRetry; retry++)
			{
				// found it, no need to retry
				if (iter != nameHandle.end())
				{
					handle = iter->second;
					break;
				}

				// release the lock so that ReportHandle() can add the handle to the map
				lock.Release();

				// retry after 1s
				Sleep(1000);

				lock.Acquire(&handleMapLock);
				iter = nameHandle.find(name);
			}
			lock.Release();

			return handle;
		}

	private:
		// map the handle to the field name
		// the Report...() functions use this to display the field name
		std::map<smf::ParameterServiceResponseHandler::Handle, std::string> handleName;

		// map the field name to the handle
		// FindHandle() use this to obtain the handle from field name
		std::map<std::string, smf::ParameterServiceResponseHandler::Handle> nameHandle;

		// to lock the nameHandle map
		SectionLock handleMapLock;

		//void AddToQueue(std::string msg)
		//{
		//	PsdResponseQueue.enqueue(msg);
		//}
	};

}
