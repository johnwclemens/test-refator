#pragma once

#include "./include/smf-2.11/LogMsg.h"
#include "./include/smf-2.11/Logger.h"
#include "SectionLock.h"

namespace smf2js
{
	class Log
	{
	public:
		virtual ~Log() {}

		Log();
		Log(smf::Logger* l, smf::Logger::Level level = smf::Logger::Default);

		virtual void set(smf::Logger* l, smf::Logger::Level lvl = smf::Logger::Default);
		virtual Log& operator << (long value);
		virtual Log& operator << (const char* msg);
		virtual Log& operator << (smf::LogMsg& msg);
		virtual Log&  begin(smf::Logger::Level lvl);
		virtual Log&  begin(void);

		virtual void end();

		void ExceptionHandler(const char* where);

	private:
		smf::Logger*        logger;
		smf::Logger::Level  level;
		smf::Logger::Level  defaultlevel;

		SectionLock lock;
	};
}

