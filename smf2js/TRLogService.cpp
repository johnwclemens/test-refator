#include <iostream>

#include "Common.h"
#include "TRLogService.h"

#include "smf-2.11/FileLoggerEntryPoint.h"
#include "smf-2.11/LogService.h"
#include "smf-2.11/Logger.h"

smf2js::TRLogService* smf2js::TRLogService::_instance;

smf2js::TRLogService::TRLogService()
{
}

smf2js::TRLogService::~TRLogService() { }

smf2js::TRLogService* smf2js::TRLogService::GetInstance()
{
	if (_instance == NULL)
		_instance = new smf2js::TRLogService();

	if (_instance == NULL)
		return NULL;

	return _instance;
}

void smf2js::TRLogService::Init(const char* pLogFile, smf::LogEntry::Severity lvl)
{
	//create the logger
	_logger = smf::InternalLogger(pLogFile, 10000000);
	_lvl = lvl;
}

void smf2js::TRLogService::Subscribe()
{
	_logResponseHandler = new LogResponseHandler(_logger);
	_logRequestHandler = smf::LogService::OpenRequestChannel(
		_logResponseHandler,
		smf2js::Common::Channel,
		_logger,
		0,
		300); // Note: You should configure your queue size 
			  // same as the maximum number of log messages 
			  // replayed by the server. Otherwises, some 
			  // historical log may be missed.
	Sleep(1000);

	// Subscribe to the log service to receive log messages
	_logRequestHandler->Subscribe(1);
}

void smf2js::TRLogService::Unsubscribe()
{
	_logRequestHandler->Unsubscribe(1);
}

void smf2js::TRLogService::LogMessage(smf::LogEntry::Severity lvl, std::string msg)
{
	if (lvl >= _lvl)
	{
		smf::LogEntry::Messages empty;
		smf::LogServiceRequestHandler::FreeFormatLogEntry entry(
			lvl,
			msg.c_str(),
			empty,
			true);
		_logRequestHandler->Record(0, entry);
	}
}
