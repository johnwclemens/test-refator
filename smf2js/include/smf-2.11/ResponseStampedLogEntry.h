
#ifndef RESPONSESTAMPEDLOGENTRY_H
#define RESPONSESTAMPEDLOGENTRY_H

#include "StampedLogEntry.h"

namespace smf{
	//! The ResponseLogEntry class is not thread safe.
	class ResponseStampedLogEntry
	{
	public:
		ResponseStampedLogEntry(const StampedLogEntry &logEntry);

		unsigned int SeqNo() const;

		//! \return Return the date and time in GMT (to the nearest second) that 
		//!          the message was sent from the client and received at the server.
		//! \remark Include: LogServiceResponseHandler.h
		//! \note The ResponseLogEntry class is not thread safe.
		//! \post Use DateTimeEntry::DateAsText to retrieve a human readable date.  
		//!       See DateTimeEntry.h for other methods.
		const DateTimeEntry &ServerDateTime() const;

		//! \return Return the date and time in GMT (to the nearest second) that 
		//!          the message was sent from the client and received at the server.
		//! \remark Include: LogServiceResponseHandler.h
		//! \note The ResponseLogEntry class is not thread safe.
		//! \post Use DateTimeEntry::DateAsText to retrieve a human readable date.  
		//!       See DateTimeEntry.h for other methods.
		const DateTimeEntry &ClientDateTime() const;

		std::string AppName() const;

		//! \return The process ID of the application/thread that created this log message.
		//! \remark Include: LogServiceResponseHandler.h
		unsigned int ProcessId() const;

		//! \return The thread ID of the application/thread that created this log message.
		//! \remark Include: LogServiceResponseHandler.h
		//! \note The ResponseLogEntry class is not thread safe.
		unsigned int ThreadId() const;

		//! \brief This returns the severity of the message.
		//! See LogEntry.h in the SMF-SDK include directory for the definitions.
		//! \return Return the binary representation
		//! \remark Include: LogServiceResponseHandler.h
		//! \note The ResponseLogEntry class is not thread safe.
		LogEntry::Severity SeverityAsCode() const;

		//! \brief This returns the severity of the message.
		//! See LogEntry.h in the SMF-SDK include directory for the definitions.
		//! \return Returns a human readable representation.
		//! \remark Include: LogServiceResponseHandler.h
		//! \note The ResponseLogEntry class is not thread safe.
		std::string SeverityAsText() const;

		unsigned int MessageId() const;

		//! \brief This function returns the log message and any parameters.
		//! \note The ResponseLogEntry class is not thread safe.
		LogEntry::Messages Message() const;

		operator const StampedLogEntry() const;
		operator const UnstampedLogEntry() const;
		operator const LogEntry() const;

	private:
		const StampedLogEntry &logEntry;
	};
}
#endif
