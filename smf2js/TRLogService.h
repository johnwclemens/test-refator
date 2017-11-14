#pragma once

#include <string>
#include "smf-2.11/LogServiceRequestHandler.h"
#include "LogResponseHandler.h"

namespace smf2js
{
	class TRLogService
	{
	private:
		TRLogService();
		~TRLogService();

	public:
		static TRLogService* GetInstance();
		void Init(const char* pLogFile, smf::LogEntry::Severity lvl);
		void Subscribe();
		void Unsubscribe();

		smf::Logger* GetLogger() { return _logger; }
		void LogMessage(smf::LogEntry::Severity lvl, std::string msg);

	private:
		static TRLogService* _instance;
		smf::LogServiceRequestHandler* _logRequestHandler;
		smf::Logger* _logger;
		LogResponseHandler* _logResponseHandler;
		smf::LogEntry::Severity _lvl;
	};
}
