#ifndef UNSTAMPEDLOGENTRY_H
#define UNSTAMPEDLOGENTRY_H

#include "DateTimeEntry.h"
#include "LogEntry.h"
#include <string>
#include <vector>


namespace smf{
	class UnstampedLogEntryMsgLine;
	class LogEntry;
	class DateTimeEntry;

	class UnstampedLogEntry
	{
	public:
		UnstampedLogEntry();
		UnstampedLogEntry(	DateTimeEntry datetime,
							const smf::LogEntry& logEntry,
							const char *appName, 
							unsigned int pid, 
							unsigned int threadId);

		
		const DateTimeEntry &DateTime() const;
		std::string AppName() const;
		unsigned int ProcessId() const;
		unsigned int ThreadId() const;
		const LogEntry &LogMessage() const;

	private:
		DateTimeEntry dateTime;
		std::string appName;
		unsigned int pid;
		unsigned int tid;
		smf::LogEntry logEntry;

		UnstampedLogEntry(	unsigned int pid, 
							unsigned int threadId,
							smf::DateTimeEntry datetime,
							const char *appName
							);
		LogEntry& CoreLogEntry();

		friend class UnstampedLogEntryMsgLine;
		
	};
}
#endif
